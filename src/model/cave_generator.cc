#include "cave_generator.h"

#include <vector>

namespace s21 {
CaveGenerator::CaveGenerator(int height, int width) {
  if ((height <= 0 || width <= 0) &&
      (height > MAX_CAVE_SIZE || width > MAX_CAVE_SIZE)) {
    throw std::invalid_argument("Invalid cave size");
  }
  this->height_ = height;
  this->width_ = width;
}

void CaveGenerator::generate(int width, int height) { this->cleanCave(); }

void CaveGenerator::generateFirstGeneration() {}

void CaveGenerator::cleanCave() {
  for (std::vector<int> &row : this->cave_) {
    row.clear();
  }
  this->cave_.clear();
}

}  // namespace s21
