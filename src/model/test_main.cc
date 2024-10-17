#include <sys/_types/_uid_t.h>
#include <sys/types.h>

#include <iostream>
#include <ostream>

#include "maze.h"

#define FIELD_HEIGHT 10
#define FIELD_WIDTH 20

int main() {
  s21::Maze maze(FIELD_HEIGHT, FIELD_WIDTH);
  maze.generate();

  // printField(maze);

  std::cout << std::endl;
  std::cout << "-= SETS =-" << std::endl;
  maze.printSets();
  std::cout << std::endl;
  std::cout << "-= MAZE =-" << std::endl;
  maze.printLabirinth();
  return 0;
}