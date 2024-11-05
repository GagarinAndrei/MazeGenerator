#include "cave_generator.h"

#include <iostream>
#include <random>
#include <thread>
#include <vector>

namespace s21 {
CaveGenerator::CaveGenerator(int height, int width) {
  if ((height <= 0 || width <= 0) &&
      (height > MAX_CAVE_SIZE || width > MAX_CAVE_SIZE)) {
    throw std::invalid_argument("Invalid cave size");
  }
  this->height_ = height;
  this->width_ = width;

  cave_.resize(height_);
  for (auto &row : cave_) {
    row.resize(width_);
  }
}

void CaveGenerator::generate(int height, int width) {
  // this->cleanCave();
  this->generateFirstGeneration();
  this->printCave();
  std::cout << "_______________________" << std::endl;
  while (!isGenerationFinished()) {
    this->generateNextGeneration();
    this->printCave();
    std::cout << "_______________________" << std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(400));
  }
}

bool CaveGenerator::initChanceGenerator() { return trueOrFalseGenerator(); }

int CaveGenerator::countLiveNeighbors(std::vector<std::vector<int>> cave, int x,
                                      int y) {
  int count = 0;
  int offsets[3] = {-1, 0, 1};

  for (int dy : offsets) {
    for (int dx : offsets) {
      if (dx == 0 && dy == 0) continue;

      int newX = x + dx;
      int newY = y + dy;

      if (newX >= 0 && newX < cave[0].size() && newY >= 0 &&
          newY < cave.size()) {
        count += cave[newY][newX] ? 1 : 0;
      }
    }
  }

  return count;
}

void CaveGenerator::generateFirstGeneration() {
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      cave_[i][j] = initChanceGenerator();
    }
  }
}

void CaveGenerator::generateNextGeneration() {
  std::vector<std::vector<int>> new_cave(cave_);
  prev_cave_ = cave_;
  for (int i = 0; i < new_cave.size(); i++) {
    for (int j = 0; j < new_cave[0].size(); j++) {
      if (new_cave[i][j] == false) {
        if (countLiveNeighbors(new_cave, j, i) > settings_.born_limits) {
          cave_[i][j] = true;
        }
      } else {
        if (countLiveNeighbors(new_cave, j, i) < settings_.death_limits) {
          cave_[i][j] = false;
        }
      }
    }
  }
}

bool CaveGenerator::isGenerationFinished() { return prev_cave_ == cave_; }

bool CaveGenerator::trueOrFalseGenerator() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution dis(settings_.init_chance);
  return dis(gen);
}

void CaveGenerator::cleanCave() {
  for (std::vector<int> &row : this->cave_) {
    row.clear();
  }
  this->cave_.clear();
}

void CaveGenerator::printCave() {
  for (std::vector<int> &row : this->cave_) {
    for (int &cell : row) {
      if (cell == true) {
        std::cout << " ";
      } else {
        std::cout << "X";
      }
    }
    std::cout << "|" << std::endl;
  }
}
}  // namespace s21
