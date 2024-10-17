#ifndef MODEL_MAZE_H_
#define MODEL_MAZE_H_

#include <vector>

namespace s21 {
typedef struct Cell {
  bool r_wall = false;
  bool b_wall = false;
  int set = 0;
} Cell;

using Matrix = std::vector<std::vector<Cell>>;

class Maze {
 public:
  Maze(int rows, int cols) : rows_(rows), cols_(cols){};
  ~Maze() = default;

  int getHeight() { return rows_; }
  int getWidth() { return cols_; }
  Matrix &getMaze() { return this->maze_; };
  Cell getCell(int i, int j) { return maze_[i][j]; }

  void generate();
  void printSets();
  void printLabirinth();

 private:
  void generateFirstLine();
  void generateOtherLines();
  void generateLastLine();

  void assignUniqueSetToCells(std::vector<Cell> &line);

  void setRightWall(std::vector<Cell> &line);
  void setBottomWall(std::vector<Cell> &line);

  int countCellInSet(std::vector<Cell> &line, int set);
  int countOfSetsWithoutBottomWall(std::vector<Cell> &line, int set);

  bool trueOrFalseGenerator();
  void unionSets(std::vector<Cell> &line, Cell current, Cell next);

  int rows_;
  int cols_;
  int count_ = 1;

  Matrix maze_;
};
}  // namespace s21

#endif  // MODEL_MAZE_H_