#include "maze.h"
#include <cstddef>
#include <iostream>
#include <random>
#include <sys/types.h>
#include <vector>

namespace s21 {

Maze::Maze(uint rows, uint cols) : rows_(rows), cols_(cols), count_(1) {}

void Maze::generate() {
  generateFirstLine();
  for (size_t i = 1; i < rows_ - 1; i++) {
    generateOtherLines();
  }
  generateLastLine();
}

void Maze::generateFirstLine() {
  std::vector<Cell> line(this->getHeight());
  for (Cell &cell : line) {
    cell.set = count_++;
  }

  setRightWall(line);
  setBottomWall(line);
  this->maze_.push_back(line);
}

void Maze::generateOtherLines() {
  std::vector<Cell> line(this->maze_.back());

  for (Cell &cell : line) {
    if (cell.r_wall == true) {
      cell.r_wall = false;
    }
    if (cell.b_wall == true) {
      cell.set = count_++;
      cell.b_wall = false;
    }
  }
  setRightWall(line);
  setBottomWall(line);

  this->maze_.push_back(line);
}

void Maze::generateLastLine() {
  std::vector<Cell> line(this->maze_.back());

  for (size_t i = 0; i < line.size(); ++i) {
    line[i].b_wall = true;
    if (line[i].set != line[i + 1].set) {
      line[i].r_wall = false;
    }
    unionSets(line, line[i], line[i + 1]);
  }
  line.back().b_wall = true;
  line.back().r_wall = true;
  this->maze_.push_back(line);
}

void Maze::setRightWall(std::vector<Cell> &line) {
  for (size_t i = 0; i < line.size(); i++) {
    if (trueOrFalseGenerator() == true) {
      line[i].r_wall = true;
    } else {
      if (line[i].set == line[i + 1].set) {
        line[i].r_wall = true;
      } else {
        unionSets(line, line[i], line[i + 1]);
      }
    }
  }
  line.back().r_wall = true;
}

void Maze::setBottomWall(std::vector<Cell> &line) {
  for (size_t i = 0; i < line.size(); i++) {
    if (trueOrFalseGenerator() == true) {
      if (setWithoutBottomWall(line, line[i].set) > 1) {
        line[i].b_wall = true;
      }
    }
  }
}

int Maze::setWithoutBottomWall(std::vector<Cell> &line, uint set) {
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

void Maze::printMaze() {

  for (uint i = 0; i < this->maze_.size(); i++) {
    for (uint j = 0; j < this->maze_[0].size(); j++) {
      std::cout << maze_[i][j].r_wall << " " << maze_[i][j].b_wall << " "
                << maze_[i][j].set << " | ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }
}

void Maze::printLabirinth() {
  for (uint i = 0; i < this->rows_; i++) {
    for (uint j = 0; j < this->cols_; j++) {
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
    }
    std::cout << std::endl;
  }
}

} // namespace s21