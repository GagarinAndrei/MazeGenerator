#include <sys/_types/_uid_t.h>
#include <sys/types.h>

#include "maze.h"

#define FIELD_HEIGHT 10
#define FIELD_WIDTH 10

int main() {
  s21::Maze maze(FIELD_HEIGHT, FIELD_WIDTH);
  maze.generate();

  // maze.printSets();
  maze.printLabirinth();
  return 0;
}