#ifndef MODEL_MAZE_H_
#define MODEL_MAZE_H_

#include <sys/types.h>
#include <vector>

namespace s21 {

class Maze {

public:
  typedef struct {
    bool r_wall;
    bool b_wall;
    uint set;
  } Cell;

  using Matrix = std::vector<std::vector<Cell>>;

  Maze(uint rows, uint cols);
  ~Maze() = default;

  uint getHeight() { return rows_; }
  uint getWidth() { return cols_; }
  Cell getCell(int i, int j) { return maze_[i][j]; }

  void generate();
  void printMaze();
  void printLabirinth();

private:
  void generateFirstLine();
  void generateOtherLines();
  void generateLastLine();

  void setRightWall(std::vector<Cell> &line);
  void setBottomWall(std::vector<Cell> &line);

  int setWithoutBottomWall(std::vector<Cell> &line, uint set);

  bool trueOrFalseGenerator();
  void unionSets(std::vector<Cell> &line, Cell current, Cell next);

  uint rows_;
  uint cols_;
  uint count_ = 1;

  Matrix maze_;
};
} // namespace s21

#endif // MODEL_MAZE_H_