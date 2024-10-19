#include "cli_view.h"

#include <ncurses.h>

#include <iostream>

namespace s21 {

void CliView::printLabirinth() {
  std::cout << std::endl;
  std::cout << "-= MAZE =-" << std::endl;
  std::cout << std::endl;

  Maze &maze = this->controller_.getMaze();
  for (size_t i = 0; i < maze.getMaze().size(); i++) {
    for (size_t j = 0; j < maze.getMaze()[0].size(); j++) {
      // if (i == 0 && j == 0) {
      //   for (int k = 0; k < maze.getWidth(); k++) {
      //     std::cout << "__";
      //   }
      //   std::cout << std::endl;
      // }
      // if (j == 0 || j == static_cast<size_t>(maze.getWidth())) {
      //   std::cout << "|";
      // }

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

void CliView::initCliGui() {
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  nodelay(stdscr, true);
  scrollok(stdscr, true);
  keypad(stdscr, true);
  start_color();

  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
}

}  // namespace s21