#include "controller.h"

namespace s21 {

void Controller::generateMaze() { this->maze_.generate(); }
void Controller::saveMazeInFile() { this->maze_.saveMazeInFile(); }
void Controller::loadMazeFromFile(const std::string &filename) {
  this->maze_.loadMazeFromFile(filename);
}
}  // namespace s21