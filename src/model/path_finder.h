#ifndef MODEL_PATH_FINDER_H_
#define MODEL_PATH_FINDER_H_

#include <vector>

#include "model.h"

namespace s21 {
class PathFinder {
 public:
  explicit PathFinder(const Maze &maze) : maze_{maze} {};
  ~PathFinder() = default;

 private:
  const Maze &maze_;
  std::vector<Maze::Cell> path_;

  bool isColision(const Maze::Cell &current, const Maze::Cell &next);
};
}  // namespace s21
#endif  // MODEL_PATH_FINDER_H_