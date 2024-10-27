#include <charconv>
#include <cstring>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "../../controller/controller.h"
#include "../../model/model.h"
#include "cli_view.h"

int main(int argc, char *argv[]) {
  int height = 0;
  int width = 0;
  s21::Maze maze;
  s21::Controller controller(maze);
  s21::CliView cli(controller);

  switch (argc) {
    case 2:
      controller.getMaze().loadMazeFromFile(argv[1]);
      break;
    case 3: {
      auto result_height =
          std::from_chars(argv[1], argv[1] + std::strlen(argv[1]), height);
      if (result_height.ec != std::errc()) {
        throw std::runtime_error("Invalid height argument");
      }
      auto result_width =
          std::from_chars(argv[2], argv[2] + std::strlen(argv[2]), width);
      if (result_width.ec != std::errc()) {
        throw std::runtime_error("Invalid width argument");
      }
      maze.setSize(height, width);
      controller.generateMaze();
    } break;
    default:
      throw std::runtime_error(
          "Invalid arguments. Example: Maze_exe 5 5 or Maze_exe maze.txt");
  }

  cli.printLabirinth();

  // for (int i = 0; i < height; i++) {
  //   for (int j = 0; j < width; j++) {
  //     std::cout << maze.getMaze()[i][j].x << " " << maze.getMaze()[i][j].y
  //               << " | ";
  //   }
  //   std::cout << std::endl;
  // }

  return 0;
}
