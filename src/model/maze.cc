#include "maze.h"

#include <sys/types.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

namespace s21 {

void Maze::generate() {
  if (this->rows_ <= 0 || this->cols_ <= 0 || this->rows_ > MAX_MAZE_SIZE ||
      this->cols_ > 50) {
    throw std::out_of_range("Invalid maze size");
  }

  generateFirstLine();
  for (int i = 1; i < rows_ - 1; i++) {
    generateOtherLines();
  }
  generateLastLine();
}

void Maze::saveMazeInFile() {
  std::ofstream file;
  file.open("maze.txt");

  if (file.is_open()) {
    file << this->rows_ << " " << this->cols_ << std::endl;

    for (size_t i = 0; i < this->maze_.size(); i++) {
      for (size_t j = 0; j < this->maze_[0].size(); j++) {
        file << maze_[i][j].r_wall << " ";
      }
      file << std::endl;
    }
    file << std::endl;

    for (size_t i = 0; i < this->maze_.size(); i++) {
      for (size_t j = 0; j < this->maze_[0].size(); j++) {
        file << maze_[i][j].b_wall << " ";
      }
      file << std::endl;
    }
    file << std::endl;

    file.close();
  }
}

void Maze::loadMazeFromFile(const std::string &filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return;
  }

  file >> rows_ >> cols_;
  maze_.resize(rows_, std::vector<Cell>(cols_));

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      int wall;
      file >> wall;
      maze_[i][j].r_wall = (wall == 1);
    }
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      int wall;
      file >> wall;
      maze_[i][j].b_wall = (wall == 1);
    }
  }

  file.close();
}

void Maze::generateFirstLine() {
  std::vector<Cell> line(this->getWidth());
  this->assignUniqueSetToCells(line);
  this->setRightWall(line);
  this->setBottomWall(line);
  this->maze_.push_back(line);
}

void Maze::generateOtherLines() {
  std::vector<Cell> line(this->maze_.back());

  for (Cell &cell : line) {
    cell.r_wall = false;
    if (cell.b_wall == true) {
      cell.set = count_++;
    }
    cell.b_wall = false;
  }

  this->setRightWall(line);
  this->setBottomWall(line);

  this->maze_.push_back(line);
}

void Maze::generateLastLine() {
  std::vector<Cell> line(this->maze_.back());

  for (Cell &cell : line) {
    cell.r_wall = false;
    if (cell.b_wall == true) {
      cell.set = count_++;
    }
    cell.b_wall = false;
  }

  this->setRightWall(line);
  this->setBottomWall(line);

  for (size_t i = 0; i < line.size(); i++) {
    if (line[i].set != line[i + 1].set) {
      line[i].r_wall = false;
    }
    unionSets(line, line[i], line[i + 1]);
    line[i].b_wall = true;
  }
  line.back().r_wall = true;  // не по алгоритму, но Рамиль сказал что так
                              // классно
  this->maze_.push_back(line);
}

void Maze::assignUniqueSetToCells(std::vector<Cell> &line) {
  for (Cell &cell : line) {
    if (cell.set == 0) {
      cell.set = this->count_++;
    }
  }
}

void Maze::setRightWall(std::vector<Cell> &line) {
  for (size_t i = 0; i < line.size() - 1; i++) {
    if (trueOrFalseGenerator() == false) {
      if (line[i].set == line[i + 1].set) {
        line[i].r_wall = true;
      } else {
        unionSets(line, line[i], line[i + 1]);
      }
    } else {
      line[i].r_wall = true;
    }
  }
  line.back().r_wall = true;  // не по алгоритму, но Рамиль сказал что так
                              // классно
}

void Maze::setBottomWall(std::vector<Cell> &line) {
  for (Cell &cell : line) {
    if (trueOrFalseGenerator() == true) {
      if (countOfSetsWithoutBottomWall(line, cell.set) > 1) {
        cell.b_wall = true;
      }
    }
  }
}

int Maze::countCellInSet(std::vector<Cell> &line, int set) {
  int count = 0;
  for (Cell &cell : line) {
    if (cell.set == set) {
      count++;
    }
  }
  return count;
}

int Maze::countOfSetsWithoutBottomWall(std::vector<Cell> &line, int set) {
  int count = 0;
  for (Cell &cell : line) {
    if (cell.set == set && cell.b_wall == false) {
      count++;
    }
  }
  return count;
}

bool Maze::trueOrFalseGenerator() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution dis(0.5);
  return dis(gen);
}

void Maze::unionSets(std::vector<Cell> &line, Cell current, Cell next) {
  for (Cell &cell : line) {
    if (cell.set == next.set) {
      cell.set = current.set;
    }
  }
}

// void Maze::printSets() {
//   std::cout << std::endl;
//   std::cout << "-= SETS =-" << std::endl;
//   std::cout << std::endl;
//   for (size_t i = 0; i < this->maze_.size(); i++) {
//     for (size_t j = 0; j < this->maze_[0].size(); j++) {
//       std::cout << std::setw(3) << std::setfill('0') << maze_[i][j].set << "
//       ";
//     }
//     std::cout << std::endl;
//     std::cout << std::endl;
//   }
// }

}  // namespace s21