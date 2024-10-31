#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_
#define MAX_MAZE_SIZE 50

#include <string>
#include <vector>
namespace s21 {

class Maze {
 public:
  typedef struct Position {
    int x;
    int y;
    bool operator==(const Position &other) const {
      return this->x == other.x && this->y == other.y;
    }
    bool operator!=(const Position &other) const { return !(*this == other); }
  } Position;

  struct PositionHash {
    std::size_t operator()(const Position &position) const {
      return std::hash<int>()(position.x) ^ (std::hash<int>()(position.y) << 1);
    }
  };

  typedef struct Cell {
    bool r_wall = false;
    bool b_wall = false;
    int set = 0;
    Position position;
  } Cell;

  using Matrix = std::vector<std::vector<Cell>>;

  Maze() {};
  ~Maze() = default;

  void generate();
  void saveMazeInFile(const std::string &filename);
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

  // TODO: Потом перенети эти функции в класс PathFinder
  inline std::vector<Position> &getPath() { return this->path_; };
  std::vector<Position> getNeighbors(const Position &pos);
  void findPath(const Position &start, const Position &target);
  bool isTargetReached(const Position &current, const Position &target);
  bool isThereParent(const Position &current);
  // Потом перенети эти функции в класс PathFinder

 private:
  void generateFirstLine();
  void generateOtherLines();
  void generateLastLine();

  void cleanMaze();
  void cleanPath();


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
  std::vector<Position> path_;
};
}  // namespace s21

#endif  // MODEL_MODEL_H_