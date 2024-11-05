#include <gtest/gtest.h>

#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

#include "../model/cave_generator.h"
#include "../model/model.h"

// TEST(generate_test, test_1) {
//   s21::Maze maze;
//   maze.setSize(5, 5);
//   EXPECT_NO_THROW(maze.generate());
// }

// TEST(generate_test, test_2) {
//   s21::Maze maze;
//   EXPECT_THROW(maze.generate(), std::out_of_range);
// }

// TEST(generate_test, test_3) {
//   std::string filename = "maze_test.txt";
//   s21::Maze maze;

//   EXPECT_THROW(maze.loadMazeFromFile(filename), std::runtime_error);
// }

// TEST(save_test, test_1) {
//   std::string filename = "maze_test.txt";
//   s21::Maze maze;
//   maze.setSize(3, 3);
//   maze.generate();
//   maze.saveMazeInFile(filename);

//   ASSERT_TRUE(std::filesystem::exists(filename));
// }

// TEST(load_test, test_1) {
//   std::string filename = "maze_test.txt";
//   s21::Maze maze;

//   ASSERT_TRUE(std::filesystem::exists(filename));
//   std::filesystem::remove(filename);
// }

// TEST(path_finder_test, test_1) {
//   s21::Maze maze;
//   s21::Maze::Position start = {0, 0};
//   s21::Maze::Position target = {3, 0};

//   maze.loadMazeFromFile("maze.txt");
//   maze.findPath(start, target);
//   std::vector<s21::Maze::Position> expected_path = {
//       {3, 0}, {2, 0}, {1, 0}, {0, 0}};

//   EXPECT_EQ(maze.getPath(), expected_path);
// }

// TEST(path_finder_test, test_2) {
//   s21::Maze maze;
//   s21::Maze::Position start = {0, 0};
//   s21::Maze::Position target = {3, 0};

//   maze.loadMazeFromFile("maze.txt");
//   maze.findPath(start, target);
//   std::vector<s21::Maze::Position> expected_path = {
//       {3, 0}, {2, 0}, {1, 0}, {0, 0}};

//   EXPECT_EQ(maze.getPath(), expected_path);
// }

// TEST(path_finder_test, test_3) {
//   s21::Maze maze;
//   s21::Maze::Position start = {0, 0};
//   s21::Maze::Position target = {3, 3};

//   maze.loadMazeFromFile("maze.txt");
//   maze.findPath(start, target);
//   std::vector<s21::Maze::Position> expected_path = {
//       {3, 3}, {2, 3}, {2, 2}, {3, 2}, {3, 1}, {3, 0}, {2, 0}, {1, 0}, {0,
//       0}};

//   EXPECT_EQ(maze.getPath(), expected_path);
// }

TEST(cave_print, test_1) {
  int height = 50;
  int width = 50;
  double probability = 0.6;
  int born_limits = 5;
  int death_limits = 4;
  s21::CaveGenerator cave(height, width);
  cave.setSettings({height, width, probability, born_limits, death_limits});
  cave.generate(cave.getSettings().height, cave.getSettings().width);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}