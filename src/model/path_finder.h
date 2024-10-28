#ifndef MODEL_PATH_FINDER_H_
#define MODEL_PATH_FINDER_H_

#include <queue>
#include <vector>

#include "model.h"

namespace s21 {
class PathFinder {
public:
  explicit PathFinder(const Maze &maze) : maze_{maze} {};
  ~PathFinder() = default;

private:
  bool isCollision(const Maze::Cell &current, const Maze::Cell &next);
  const Maze &maze_;
  std::queue<Maze::Cell> path_;
};
} // namespace s21
#endif // MODEL_PATH_FINDER_H_