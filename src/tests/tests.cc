#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../model/cave_generator.h"
#include "../model/model.h"

TEST(generate_test, test_1) {
  s21::Maze maze;
  maze.setSize(5, 5);
  EXPECT_NO_THROW(maze.generate());
}

TEST(generate_test, test_2) {
  s21::Maze maze;
  EXPECT_THROW(maze.generate(), std::out_of_range);
}

TEST(generate_test, test_3) {
  std::string filename = "maze_test.txt";
  s21::Maze maze;

  EXPECT_THROW(maze.loadMazeFromFile(filename), std::runtime_error);
}

TEST(save_test, test_1) {
  std::string filename = "maze_test.txt";
  s21::Maze maze;
  maze.setSize(3, 3);
  maze.generate();
  maze.saveMazeInFile(filename);

  ASSERT_TRUE(std::filesystem::exists(filename));
}

TEST(load_test, test_1) {
  std::string filename = "maze_test.txt";
  s21::Maze maze;

  ASSERT_TRUE(std::filesystem::exists(filename));
  std::filesystem::remove(filename);
}

TEST(path_finder_test, test_1) {
  s21::Maze maze;
  s21::Maze::Position start = {0, 0};
  s21::Maze::Position target = {3, 0};

  maze.loadMazeFromFile("maze.txt");
  maze.findPath(start, target);
  std::vector<s21::Maze::Position> expected_path = {
      {3, 0}, {2, 0}, {1, 0}, {0, 0}};

  EXPECT_EQ(maze.getPath(), expected_path);
}

TEST(path_finder_test, test_2) {
  s21::Maze maze;
  s21::Maze::Position start = {0, 0};
  s21::Maze::Position target = {3, 0};

  maze.loadMazeFromFile("maze.txt");
  maze.findPath(start, target);
  std::vector<s21::Maze::Position> expected_path = {
      {3, 0}, {2, 0}, {1, 0}, {0, 0}};

  EXPECT_EQ(maze.getPath(), expected_path);
}

TEST(path_finder_test, test_3) {
  s21::Maze maze;
  s21::Maze::Position start = {0, 0};
  s21::Maze::Position target = {3, 3};

  maze.loadMazeFromFile("maze.txt");
  maze.findPath(start, target);
  std::vector<s21::Maze::Position> expected_path = {
      {3, 3}, {2, 3}, {2, 2}, {3, 2}, {3, 1}, {3, 0}, {2, 0}, {1, 0}, {0, 0}};

  EXPECT_EQ(maze.getPath(), expected_path);
}

TEST(cave_generator_test, test_2) {
  s21::CaveGenerator caveGenerator;
  caveGenerator.setSettings({50, 50, 0.6, 5, 4});
  caveGenerator.generate();
  std::vector<std::vector<int>> caveData = caveGenerator.getCave();

  EXPECT_FALSE(caveData.empty());

  for (const auto& row : caveData) {
    EXPECT_EQ(row.size(), caveData[0].size());
  }

  bool hasWall = false;
  bool hasEmpty = false;
  for (const auto& row : caveData) {
    for (const auto& cell : row) {
      if (cell) {
        hasWall = true;
      } else {
        hasEmpty = true;
      }
    }
  }
  EXPECT_TRUE(hasWall);
  EXPECT_TRUE(hasEmpty);
}
TEST(cave_generator_test, test_3) {
  s21::CaveGenerator caveGenerator;
  caveGenerator.setSettings({50, 50, 0.6, 5, 4});
  caveGenerator.generate();
  std::string filename = "test_cave.txt";

  caveGenerator.saveCaveInFile(filename);

  ASSERT_TRUE(std::filesystem::exists(filename));

  std::ifstream file(filename);
  ASSERT_TRUE(file.is_open());

  int height, width;
  file >> height >> width;
  ASSERT_EQ(height, caveGenerator.getHeight());
  ASSERT_EQ(width, caveGenerator.getWidth());

  std::vector<std::vector<int>> caveData(height, std::vector<int>(width));
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      int wall;
      file >> wall;
      caveData[i][j] = (wall == 1);
    }
  }

  std::vector<std::vector<int>> originalCaveData = caveGenerator.getCave();
  ASSERT_EQ(caveData, originalCaveData);

  file.close();

  std::filesystem::remove(filename);
}

TEST(cave_generator_test, test_4) {
  s21::CaveGenerator caveGenerator;
  caveGenerator.setSettings({50, 50, 0.6, 5, 4});
  caveGenerator.generate();
  std::string filename = "test_cave.txt";

  caveGenerator.saveCaveInFile(filename);

  s21::CaveGenerator loadedCaveGenerator;

  loadedCaveGenerator.loadCaveFromFile(filename);

  std::vector<std::vector<int>> originalCaveData = caveGenerator.getCave();
  std::vector<std::vector<int>> loadedCaveData = loadedCaveGenerator.getCave();
  ASSERT_EQ(originalCaveData, loadedCaveData);

  std::filesystem::remove(filename);
}

TEST(cave_print, test_1) {
  int height = 50;
  int width = 50;
  double probability = 0.6;
  int born_limits = 5;
  int death_limits = 4;
  s21::CaveGenerator cave;
  cave.setSettings({width, height, probability, born_limits, death_limits});
  cave.generate();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}