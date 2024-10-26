#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  explicit Controller(Maze &maze) : maze_{maze} {}
  ~Controller() {}

  inline Maze &getMaze() { return this->maze_; }
  inline int getHeight() { return this->maze_.getHeight(); }
  inline int getWidth() { return this->maze_.getWidth(); }
  inline void setHeight(int height) { this->maze_.setHeight(height); }
  inline void setWidth(int width) { this->maze_.setWidth(width); }
  inline void saveMazeInFile(const std::string &filePath) {
    this->maze_.saveMazeInFile(filePath);
  };
  inline void loadMazeFromFile(const std::string &filePath) {
    this->maze_.loadMazeFromFile(filePath);
  };
  inline void generateMaze() { this->maze_.generate(); };

 private:
  Maze &maze_;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_
