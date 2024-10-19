#include "maze.h"

#include <sys/types.h>

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

namespace s21 {

void Maze::generate() {
  generateFirstLine();
  for (int i = 1; i < rows_ - 1; i++) {
    generateOtherLines();
  }
  generateLastLine();
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
}

void Maze::setBottomWall(std::vector<Cell> &line) {
  for (Cell &cell : line) {
    if (trueOrFalseGenerator() == true) {
      if (countOfSetsWithoutBottomWall(line, cell.set) > 1 /*||
          countCellInSet(line, cell.set) > 1*/) {
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

void Maze::printSets() {
  std::cout << std::endl;
  std::cout << "-= SETS =-" << std::endl;
  std::cout << std::endl;
  for (size_t i = 0; i < this->maze_.size(); i++) {
    for (size_t j = 0; j < this->maze_[0].size(); j++) {
      std::cout << std::setw(3) << std::setfill('0') << maze_[i][j].set << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }
}

void Maze::printLabirinth() {
  std::cout << std::endl;
  std::cout << "-= MAZE =-" << std::endl;
  std::cout << std::endl;
  for (size_t i = 0; i < this->maze_.size(); i++) {
    for (size_t j = 0; j < this->maze_[0].size(); j++) {
      if (i == 0 && j == 0) {
        for (int k = 0; k < cols_ + 1; k++) {
          std::cout << "__";
        }
        std::cout << std::endl;
      }
      if (j == 0) {
        std::cout << "|";
      }

      if (maze_[i][j].r_wall == true && maze_[i][j].b_wall == false) {
        std::cout << " |";
      }
      if (maze_[i][j].b_wall == true && maze_[i][j].r_wall == false) {
        std::cout << "__";
      }
      if (maze_[i][j].b_wall == false && maze_[i][j].r_wall == false) {
        std::cout << "  ";
      }
      if (maze_[i][j].b_wall == true && maze_[i][j].r_wall == true) {
        std::cout << "_|";
      }
      if (j == maze_[0].size() - 1) {
        std::cout << "|";
      }
    }
    std::cout << std::endl;
  }
}

}  // namespace s21