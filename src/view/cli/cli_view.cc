#include "cli_view.h"

#include <cstddef>
#include <ncurses.h>

#include <iostream>

namespace s21 {

// void CliView::printLabirinth() {
  // std::cout << std::endl;
  // std::cout << "-= MAZE =-" << std::endl;
  // std::cout << std::endl;

  // Maze &maze = this->controller_.getMaze();
  // for (size_t i = 0; i < maze.getMaze().size(); i++) {
  //   for (size_t j = 0; j < maze.getMaze()[0].size(); j++) {
  //     // if (i == 0 && j == 0) {
  //     //   for (int k = 0; k < maze.getWidth(); k++) {
  //     //     std::cout << "__";
  //     //   }
  //     //   std::cout << std::endl;
  //     // }
  //     // if (j == 0 || j == static_cast<size_t>(maze.getWidth())) {
  //     //   std::cout << "|";
  //     // }

  //     if (maze.getMaze()[i][j].r_wall == true &&
  //         maze.getMaze()[i][j].b_wall == false) {
  //       std::cout << " |";
  //     }
  //     if (maze.getMaze()[i][j].b_wall == true &&
  //         maze.getMaze()[i][j].r_wall == false) {
  //       std::cout << "__";
  //     }
  //     if (maze.getMaze()[i][j].b_wall == false &&
  //         maze.getMaze()[i][j].r_wall == false) {
  //       std::cout << "[]";
  //     }
  //     if (maze.getMaze()[i][j].b_wall == true &&
  //         maze.getMaze()[i][j].r_wall == true) {
  //       std::cout << "_|";
  //     }
  //   }
  //   std::cout << std::endl;
  // }

 void CliView::printLabirinth() {
    initscr();  // Инициализация ncurses
    noecho();   // Отключение отображения вводимых символов
    curs_set(0);  // Скрытие курсора

    mvprintw(0, 0, "-= MAZE =-");  // Вывод заголовка

    Maze &maze = this->controller_.getMaze();
    int height = maze.getMaze().size();
    int width = maze.getMaze()[0].size();

    // Начальные координаты для вывода лабиринта
    int start_y = 2;

    // Нарисовать границу вокруг лабиринта
    WINDOW *win = newwin(height * 2 + 1, width * 2 + 1, start_y, 0);
    box(win, 0, 0); // Рисуем рамку вокруг окна

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Отрисовка нижней стены
            if (maze.getMaze()[i][j].b_wall) {
                mvwprintw(win, i * 2 + 1, j * 2 + 1, "__"); // Нижняя стена
            } else {
                mvwprintw(win, i * 2 + 1, j * 2 + 1, "  "); // Пустое место
            }

            // Отрисовка правой стены
            if (maze.getMaze()[i][j].r_wall) {
                mvwprintw(win, i * 2, j * 2 + 2, "|"); // Правая стена
            }

            // Отрисовка ячейки
            if (!maze.getMaze()[i][j].b_wall && !maze.getMaze()[i][j].r_wall) {
                mvwprintw(win, i * 2, j * 2 + 1, "[]"); // Ячейка без стен
            } else if (maze.getMaze()[i][j].b_wall && maze.getMaze()[i][j].r_wall) {
                mvwprintw(win, i * 2, j * 2 + 1, "_|"); // Ячейка с обеими стенами
            }
        }
        // Обработка правой границы для каждой строки
        mvwprintw(win, i * 2 + 1, width * 2 - 1, "|"); // Правая граница
    }

    wrefresh(win); // Обновление окна с лабиринтом

    refresh();   // Обновление экрана
    getch();     // Ожидание ввода пользователя
    delwin(win); // Удаление окна перед завершением работы ncurses
    endwin();    // Завершение работы ncurses
}


void CliView::initCliGui() {
  // initscr();
  // curs_set(0);
  // cbreak();
  // noecho();
  // nodelay(stdscr, true);
  // scrollok(stdscr, true);
  // keypad(stdscr, true);
  // start_color();

  // init_pair(1, COLOR_GREEN, COLOR_GREEN);
  // init_pair(2, COLOR_WHITE, COLOR_BLACK);
}

}  // namespace s21