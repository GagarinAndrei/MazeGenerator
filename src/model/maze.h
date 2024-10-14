#ifndef MODEL_MAZE_H_
#define MODEL_MAZE_H_

#include <sys/types.h>
#include <vector>
#include <sys/types.h>

namespace s21 {

class Maze {

public:
  using MazeMatrix = std::vector<std::vector<uint>>;
  Maze(uint rows, uint cols);
  ~Maze() = default;

  uint getHeight() { return rows_; }
  uint getWidth() { return cols_; }
  uint getCell(int i, int j) { return maze_[i][j]; }
  MazeMatrix getRightWallMatrix() { return this->right_wall_matrix_; }

  void generate();

private:
  void setRightWall(std::vector<uint> &line);
  bool trueOrFalseGenerator();


  uint rows_;
  uint cols_;
  uint count_;

  MazeMatrix maze_;
  MazeMatrix right_wall_matrix_;
  MazeMatrix sets_matrix_;
};
} // namespace s21

#endif // MODEL_MAZE_H_