#include "maze.h"
#include <iostream>
#include <ostream>
#include <sys/_types/_uid_t.h>
#include <sys/types.h>

void printMaze(s21::Maze *maze) {

  for (uint i = 0; i < maze->getHeight(); i++) {
    for (uint j = 0; j < maze->getWidth(); j++) {
      std::cout << maze->getCell(i, j);
    }
    std::cout << std::endl;
  }
}

void printMatrix(s21::Maze::MazeMatrix matrix) {
  for (uint i = 0; i < matrix.size(); i++) {
    for (uint j = 0; j < matrix[0].size(); j++) {
      std::cout << matrix[i][j];
    }
    std::cout << std::endl;
  }
}

int main() {

  s21::Maze maze(4, 4);
  maze.generate();

  std::cout << std::endl;
  std::cout << "-= MAZE =-" << std::endl;
  printMaze(&maze);
  std::cout << std::endl;

  std::cout << "-= R_WALL MATRIX =-" << std::endl;
  printMatrix(maze.getRightWallMatrix());
  std::cout << std::endl;


  return 0;
}