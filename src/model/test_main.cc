#include "maze.h"
#include <iostream>
#include <ostream>
#include <sys/_types/_uid_t.h>
#include <sys/types.h>

int main() {
  s21::Maze maze(4, 4);
  maze.generate();




  std::cout << std::endl;
  std::cout << "-= MAZE =-" << std::endl;
  maze.printMaze();
  std::cout << std::endl;
  maze.printLabirinth();

  return 0;
}