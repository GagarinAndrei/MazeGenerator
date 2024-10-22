#ifndef MODEL_MAZE_H_
#define MODEL_MAZE_H_
#define MAX_MAZE_SIZE 50

#include <string>
#include <vector>
namespace s21 {

class Maze {
 public:
  typedef struct Cell {
    bool r_wall = false;
    bool b_wall = false;
    int set = 0;
  } Cell;
  using Matrix = std::vector<std::vector<Cell>>;

  Maze(){};
  ~Maze() = default;

  void generate();
  void saveMazeInFile();
  void loadMazeFromFile(const std::string &filename);

  void setSize(int rows, int cols) {
    this->rows_ = rows;
    this->cols_ = cols;
  };

  inline int getHeight() { return rows_; }
  inline int getWidth() { return cols_; }
  inline void setHeight(int height) { this->rows_ = height; };
  inline void setWidth(int width) { this->cols_ = width; };
  inline Matrix &getMaze() { return this->maze_; };
  inline Cell getCell(int i, int j) { return maze_[i][j]; }

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