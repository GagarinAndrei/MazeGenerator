#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>
#include <vector>

namespace game {

#define RIGHT_WALL 1
#define BOTTOM_WALL 2
#define TWO_WALL 3

class Maze {
 public:
  Maze() {};
  Maze(int rows, int cols);
  ~Maze() = default;

  void generate();
  void setSize(int rows, int cols);
  void printMaze();

  std::vector<std::vector<int>> getMaze();

 private:
  int set_ = 4;
  int rows_;
  int cols_;
  std::vector<std::vector<int>> maze_;

  int gr();
  void createFirstRow();
  void createMiddleRows(int prevRow);
  void createLastRow(int prevRow);

  void setRightWall(std::vector<int>& row);
  void setBottomWall(std::vector<int>& row);
  void unionSets(std::vector<int>& row, int a, int b);
  int cellsWithoutBottomWall(std::vector<int>& row, int set);

  void clearSets();

};  // class Maze
}  // namespace game

#endif