#include "maze.h"
#include <iostream>
#include <ostream>
#include <sys/_types/_uid_t.h>
#include <sys/types.h>

#define FIELD_HEIGHT 5
#define FIELD_WIDTH 5

int main() {

  s21::Maze maze(FIELD_HEIGHT, FIELD_WIDTH);
  maze.generate();

  // printField(maze);

  std::cout << std::endl;
  std::cout << "-= MAZE =-" << std::endl;
  maze.printMaze();
  std::cout << std::endl;
  maze.printLabirinth();
  return 0;
}