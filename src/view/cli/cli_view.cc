#include "cli_view.h"

#include <ncurses.h>

#include <iostream>

namespace s21 {

void CliView::printLabirinth() {
  std::cout << std::endl;
  std::cout << "-= MAZE =-" << std::endl;
  std::cout << std::endl;

  Maze &maze = this->controller_.getMaze();
  for (int i = 0; i < maze.getHeight(); i++) {
    for (int j = 0; j < maze.getWidth(); j++) {
      if (i == 0 && j == 0) {
        for (int k = 0; k < maze.getWidth(); k++) {
          std::cout << "__";
        }
        std::cout << std::endl;
      }
      if (j == 0) {
        std::cout << "|";
      }

      if (maze.getMaze()[i][j].r_wall == true &&
          maze.getMaze()[i][j].b_wall == false) {
        std::cout << " |";
      }
      if (maze.getMaze()[i][j].b_wall == true &&
          maze.getMaze()[i][j].r_wall == false) {
        std::cout << "__";
      }
      if (maze.getMaze()[i][j].b_wall == false &&
          maze.getMaze()[i][j].r_wall == false) {
        std::cout << "  ";
      }
      if (maze.getMaze()[i][j].b_wall == true &&
          maze.getMaze()[i][j].r_wall == true) {
        std::cout << "_|";
      }
    }
    std::cout << std::endl;
  }
}
}  // namespace s21