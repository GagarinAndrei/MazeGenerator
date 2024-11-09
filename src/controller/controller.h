#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "../model/cave_generator.h"
#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  explicit Controller(Maze &maze, CaveGenerator &cave_generator)
      : maze_{maze}, cave_generator_{cave_generator} {}
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
  inline void findPath(const Maze::Position &start,
                       const Maze::Position &target) {
    this->maze_.findPath(start, target);
  };

  inline CaveGenerator &getCave() { return this->cave_generator_; }
  inline int getHeightCave() { return this->cave_generator_.getHeight(); }
  inline int getWidthCave() { return this->cave_generator_.getWidth(); }
  inline void setHeightCave(int height) {
    this->cave_generator_.setHeight(height);
  }
  inline void setWidthCave(int width) { this->cave_generator_.setWidth(width); }
  inline void setSettings(const CaveGenerator::Settings &settings) {
    this->cave_generator_.setSettings(settings);
  }
  inline void saveCaveInFile(const std::string &filePath) {
    this->cave_generator_.saveCaveInFile(filePath);
  };
  inline void loadCaveFromFile(const std::string &filePath) {
    this->cave_generator_.loadCaveFromFile(filePath);
  };
  inline void generateCave() {
    this->cave_generator_.resizeCave(this->getCave().getHeight(),
                                     this->getCave().getWidth());
    this->cave_generator_.generate();
  };

  inline CaveGenerator::Settings &getSettings() {
    return this->cave_generator_.getSettings();
  }

 private:
  Maze &maze_;
  CaveGenerator &cave_generator_;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_
