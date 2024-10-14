#include "maze.h"
#include <iostream>
#include <random>
#include <sys/types.h>
#include <vector>

namespace s21 {

Maze::Maze(uint rows, uint cols)
    : rows_(rows), cols_(cols), count_(0),
      maze_(rows, std::vector<uint>(cols, 0)) {}

void Maze::generate() {
  std::vector<uint> line(cols_, 0);

  for (uint i = 0; i < this->cols_; ++i) {
    line[i] = this->count_++;
    std::cout << line[i] << " ";
  }
}

void Maze::setRightWall(std::vector<uint> &line) {

  for (uint i = 0; i < line.size(); ++i) {
    if (trueOrFalseGenerator()) {
      line[i] = true;
    } else {
      if (line[i] == line[i + 1]) {
        line[i] = true;
      } else {
        
      }
    }
  }
}

bool Maze::trueOrFalseGenerator() {
  std::random_device rd; // Используем для получения начального значения (seed)
  std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)
  std::bernoulli_distribution dis(0.5);
  return dis(gen);
}

} // namespace s21