#include "cave_generator.h"

#include <fstream>
#include <iostream>
#include <random>
#include <vector>

namespace s21 {
void CaveGenerator::resizeCave(int height, int width) {
  this->cave_.resize(height_);
  for (auto &row : cave_) {
    row.resize(width_);
  }
}

void CaveGenerator::generate() {
  this->generateFirstGeneration();
  while (!isGenerationFinished()) {
    this->generateNextGeneration();
  }
}

void CaveGenerator::saveCaveInFile(const std::string &filename) {
  std::ofstream file;
  file.open(filename);

  if (file.is_open()) {
    file << this->height_ << " " << this->width_ << std::endl;

    for (size_t i = 0; i < this->cave_.size(); i++) {
      for (size_t j = 0; j < this->cave_[0].size(); j++) {
        file << cave_[i][j] << " ";
      }
      file << std::endl;
    }
    file.close();
  }
}

void CaveGenerator::loadCaveFromFile(const std::string &filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file");
  }

  file >> height_ >> width_;
  this->resizeCave(height_, width_);

  for (int i = 0; i < this->height_; ++i) {
    for (int j = 0; j < this->width_; ++j) {
      int wall;
      file >> wall;
      cave_[i][j] = (wall == 1);
    }
  }

  file.close();
}

void CaveGenerator::setSettings(Settings settings) {
  this->settings_ = settings;
  this->height_ = settings.height;
  this->width_ = settings.width;
  this->resizeCave(this->height_, this->width_);
}

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
      cave_[i][j] = trueOrFalseGenerator();
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

// void CaveGenerator::printCave() {
//   for (std::vector<int> &row : this->cave_) {
//     for (int &cell : row) {
//       if (cell == true) {
//         std::cout << " ";
//       } else {
//         std::cout << "X";
//       }
//     }
//     std::cout << "|" << std::endl;
//   }
// }
}  // namespace s21
