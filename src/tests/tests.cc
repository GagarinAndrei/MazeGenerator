#include "../model/model.h"
#include <gtest/gtest.h>
#include <vector>

TEST(path_finder_test, test_1) {
  s21::Maze maze;
  s21::Maze::Position start = {0, 0};
  s21::Maze::Position target = {2, 0};

  // s21::Maze::Matrix mazez = {{{false, false, 0, {0, 0}},
  //                             {true, false, 0, {1, 0}},
  //                             {false, false, 0, {2, 0}}},
  //                            {{false, false, 0, {0, 1}},
  //                             {false, true, 0, {1, 1}},
  //                             {false, false, 0, {2, 1}}},
  //                            {{false, false, 0, {0, 2}},
  //                             {false, false, 0, {1, 2}},
  //                             {false, false, 0, {2, 2}}}};

  // s21::Maze::Position start = {0, 0};
  // s21::Maze::Position target = {2, 2};

  maze.loadMazeFromFile("maze.txt");
      maze.findPath(maze.getMaze(), start, target);
  std::vector<s21::Maze::Position> expected_path = {
      {0, 0},
      {1, 0},
      {2, 0},
      {3, 0}
  };

  EXPECT_EQ(maze.getPath(), expected_path);
  // controller.userInput(START, false);
  // controller.updateCurrentState();
  // EXPECT_EQ(model.getState(), s21::GAME_MOVING);
  // controller.userInput(PAUSE, false);
  // EXPECT_EQ(model.getState(), s21::GAME_MOVING);
  // controller.updateCurrentState();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}