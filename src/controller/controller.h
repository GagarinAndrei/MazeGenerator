#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "../model/model.h"
// #include "qtmetamacros.h"

namespace s21 {

class Controller {

public:
  explicit Controller(Maze &maze) : maze_{maze} {}
  ~Controller() {}

  inline Maze &getMaze() { return this->maze_; }
  inline int getHeight() { return this->maze_.getHeight(); }
  inline int getWidth() { return this->maze_.getWidth(); }
  inline void setHeight(int height) {
    this->maze_.setHeight(height);
    // emit mazeHeightChanged();
  }
  inline void setWidth(int width) {
    this->maze_.setWidth(width);
    // emit mazeWidthChanged();
  }
  inline void saveMazeInFile(const std::string &filePath) {
    this->maze_.saveMazeInFile(filePath);
  };
  inline void loadMazeFromFile(const std::string &filePath) {
    this->maze_.loadMazeFromFile(filePath);
  };
  inline void generateMaze() { this->maze_.generate(); };
  // Q_INVOKABLE void printLabirinth(); // for debug

  // signals:
  //   void mazeDataChanged();
  //   void mazeHeightChanged();
  //   void mazeWidthChanged();

  // public slots:
  // void saveMazeInFile(const QString &filePath);
  //   void loadMazeFromFile(const QString &filePath);

private:
  Maze &maze_;
};
} // namespace s21

#endif // CONTROLLER_CONTROLLER_H_
