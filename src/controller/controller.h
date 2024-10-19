#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "../model/maze.h"

namespace s21 {

class Controller {
 public:
  Controller(Maze &maze) : maze_{maze} {}
  ~Controller() {}

  inline Maze &getMaze() { return this->maze_; }

  void generateMaze();
  void saveMazeInFile();
  void loadMazeFromFile(const std::string &filename);

 private:
  Maze &maze_;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_