#include "model.h"

#include <sys/types.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <unordered_map>
#include <vector>

namespace s21 {

void Maze::generate() {
  cleanMaze();
  cleanPath();
  if (this->rows_ <= 0 || this->cols_ <= 0 || this->rows_ > MAX_MAZE_SIZE ||
      this->cols_ > 50) {
    throw std::out_of_range("Invalid maze size");
  }

  generateFirstLine();
  for (int i = 1; i < rows_ - 1; i++) {
    int x = 0;
    generateOtherLines();
    for (Cell &cell : maze_[i]) {
      cell.position.x = x++;
      cell.position.y = i;
    }
  }
  generateLastLine();
  emit generated();
}

void Maze::saveMazeInFile(const std::string &filename) {
  std::ofstream file;
  file.open(filename);

  if (file.is_open()) {
    file << this->rows_ << " " << this->cols_ << std::endl;

    for (size_t i = 0; i < this->maze_.size(); i++) {
      for (size_t j = 0; j < this->maze_[0].size(); j++) {
        file << maze_[i][j].r_wall << " ";
      }
      file << std::endl;
    }
    file << std::endl;

    for (size_t i = 0; i < this->maze_.size(); i++) {
      for (size_t j = 0; j < this->maze_[0].size(); j++) {
        file << maze_[i][j].b_wall << " ";
      }
      file << std::endl;
    }
    file << std::endl;

    file.close();
  }
}

void Maze::loadMazeFromFile(const std::string &filename) {
  cleanMaze();
  std::ifstream file(filename);

  if (!file.is_open()) {
    // std::cerr << "Failed to open file: " << filename << std::endl;
    // return;
    throw std::runtime_error("Failed to open file");
  }

  file >> rows_ >> cols_;
  maze_.resize(rows_, std::vector<Cell>(cols_));

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      int wall;
      file >> wall;
      maze_[i][j].r_wall = (wall == 1);
    }
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      int wall;
      file >> wall;
      maze_[i][j].b_wall = (wall == 1);
    }
  }

  file.close();
}

void Maze::generateFirstLine() {
  std::vector<Cell> line(this->getWidth());
  this->assignUniqueSetToCells(line);
  this->setRightWall(line);
  this->setBottomWall(line);
  int x = 0;
  for (Cell &cell : line) {
    cell.position.x = x++;
  }
  this->maze_.push_back(line);
}

void Maze::generateOtherLines() {
  std::vector<Cell> line(this->maze_.back());

  for (Cell &cell : line) {
    cell.r_wall = false;
    if (cell.b_wall == true) {
      cell.set = count_++;
    }
    cell.b_wall = false;
  }

  this->setRightWall(line);
  this->setBottomWall(line);

  this->maze_.push_back(line);
}

void Maze::generateLastLine() {
  std::vector<Cell> line(this->maze_.back());
  int x = 0;

  for (Cell &cell : line) {
    cell.r_wall = false;
    if (cell.b_wall == true) {
      cell.set = count_++;
    }
    cell.b_wall = false;
  }

  this->setRightWall(line);
  this->setBottomWall(line);

  for (size_t i = 0; i < line.size(); i++) {
    if (line[i].set != line[i + 1].set) {
      line[i].r_wall = false;
    }
    unionSets(line, line[i], line[i + 1]);
    line[i].b_wall = true;
    line[i].position.x = x++;
    line[i].position.y = this->rows_ - 1;
  }
  line.back().r_wall = true;
  this->maze_.push_back(line);
}

void Maze::cleanMaze() {
  for (auto &line : this->maze_) {
    line.clear();
  }
  this->maze_.clear();
}

void Maze::cleanPath() { this->path_.clear(); }

void Maze::assignUniqueSetToCells(std::vector<Cell> &line) {
  for (Cell &cell : line) {
    if (cell.set == 0) {
      cell.set = this->count_++;
    }
  }
}

void Maze::setRightWall(std::vector<Cell> &line) {
  for (size_t i = 0; i < line.size() - 1; i++) {
    if (trueOrFalseGenerator() == false) {
      if (line[i].set == line[i + 1].set) {
        line[i].r_wall = true;
      } else {
        unionSets(line, line[i], line[i + 1]);
      }
    } else {
      line[i].r_wall = true;
    }
  }
  line.back().r_wall = true;
}

void Maze::setBottomWall(std::vector<Cell> &line) {
  for (Cell &cell : line) {
    if (trueOrFalseGenerator() == true) {
      if (countOfSetsWithoutBottomWall(line, cell.set) > 1) {
        cell.b_wall = true;
      }
    }
  }
}

int Maze::countCellInSet(std::vector<Cell> &line, int set) {
  int count = 0;
  for (Cell &cell : line) {
    if (cell.set == set) {
      count++;
    }
  }
  return count;
}

int Maze::countOfSetsWithoutBottomWall(std::vector<Cell> &line, int set) {
  int count = 0;
  for (Cell &cell : line) {
    if (cell.set == set && cell.b_wall == false) {
      count++;
    }
  }
  return count;
}

bool Maze::trueOrFalseGenerator() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution dis(0.5);
  return dis(gen);
}

void Maze::unionSets(std::vector<Cell> &line, Cell current, Cell next) {
  for (Cell &cell : line) {
    if (cell.set == next.set) {
      cell.set = current.set;
    }
  }
}

// 8=================================================================э
std::vector<Maze::Position> Maze::getNeighbors(const Position &pos) {
  std::vector<Position> neighbors;
  int rows = maze_.size();
  int cols = maze_[0].size();

  // Проверка соседа сверху
  if (pos.y > 0 && !maze_[pos.y - 1][pos.x].b_wall) {
    neighbors.push_back({pos.x, pos.y - 1});
  }
  // Проверка соседа снизу
  if (pos.y < rows - 1 && !maze_[pos.y][pos.x].b_wall) {
    neighbors.push_back({pos.x, pos.y + 1});
  }
  // Проверка соседа слева
  if (pos.x > 0 && !maze_[pos.y][pos.x - 1].r_wall) {
    neighbors.push_back({pos.x - 1, pos.y});
  }
  // Проверка соседа справа
  if (pos.x < cols - 1 && !maze_[pos.y][pos.x].r_wall) {
    neighbors.push_back({pos.x + 1, pos.y});
  }

  return neighbors;
}

bool Maze::isTargetReached(const Position &current, const Position &target) {
  return current.x == target.x && current.y == target.y;
}

bool Maze::isThereParent(const Position &current) {
  return current.x != -1 && current.y != -1;
}

void Maze::findPath(const Position &start, const Position &target) {
  this->cleanPath();
  std::queue<Position> frontier;
  frontier.push(start);

  std::unordered_map<Position, Position, struct PositionHash> came_from;
  came_from[start] = {-1, -1};

  while (!frontier.empty()) {
    Position current = frontier.front();
    frontier.pop();

    if (isTargetReached(current, target)) {
      break;
    }

    for (const Position &next : getNeighbors(current)) {
      if (came_from.find(next) == came_from.end()) {
        frontier.push(next);
        came_from[next] = current;
      }
    }
  }
  Position current = target;

  while (current != start) {
    this->path_.push_back(current);
    current = came_from[current];
  }
  this->path_.push_back(start);
}
// 8=================================================================э

}  // namespace s21