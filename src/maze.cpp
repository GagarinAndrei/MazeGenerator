#include "maze.h"

game::Maze::Maze(int rows, int cols) : rows_(rows), cols_(cols) {}

int game::Maze::gr() { return std::rand() % 2; }

void game::Maze::createFirstRow() {
  std::vector<int> row(cols_);
  // Заполнение каждой ячейки уникальным множеством
  for (int& cell : row) {
    if (cell == 0) {
      cell = set_;
      set_ += (1 << 2);
    }
  }

  setRightWall(row);
  setBottomWall(row);

  maze_.push_back(row);
}

void game::Maze::createMiddleRows(int prevRow) {
  std::vector<int> row(maze_[prevRow]);

  for (int& cell : row) {
    cell &= ~RIGHT_WALL;
    if ((cell & BOTTOM_WALL) == BOTTOM_WALL) {
      cell = set_;
      set_ += (1 << 2);
      cell &= ~BOTTOM_WALL;
    }
  }

  setRightWall(row);
  setBottomWall(row);

  maze_.push_back(row);
}

void game::Maze::createLastRow(int prevRow) {
  std::vector<int> row(maze_[prevRow]);

  for (int& cell : row) {
    cell &= ~RIGHT_WALL;
    if ((cell & BOTTOM_WALL) == BOTTOM_WALL) {
      cell = set_;
      set_ += 4;
      cell &= ~BOTTOM_WALL;
    }
  }

  setRightWall(row);
  setBottomWall(row);

  for (int i = 0; i < cols_; i++) {
    if ((row[i] >> 2) != (row[i + 1] >> 2)) {
      row[i] &= ~RIGHT_WALL;
    }
    unionSets(row, row[i], row[i + 1]);
    row[i] |= BOTTOM_WALL;
  }

  maze_.push_back(row);
}

void game::Maze::setRightWall(std::vector<int>& row) {
  // Проставление правых стенок
  for (int i = 0; i < cols_ - 1;
       i++) {  // cols_ - 1, потому что у последней ячейки есть правая стенка
    int r = gr();
    if (r == 0) {
      if ((row[i] >> 2) == (row[i + 1] >> 2)) {
        row[i] |= RIGHT_WALL;
      } else {
        unionSets(row, row[i], row[i + 1]);
      }
    } else if (r == 1) {
      row[i] |= RIGHT_WALL;
    }
  }
}

void game::Maze::setBottomWall(std::vector<int>& row) {
  // Проставление нижних стенок
  for (int i = 0; i < cols_; i++) {
    int r = gr();
    if (r == 1) {
      if (cellsWithoutBottomWall(row, row[i]) > 1) {
        row[i] |= BOTTOM_WALL;
      }
    }
  }
}

void game::Maze::unionSets(std::vector<int>& row, int a, int b) {
  for (int& cell : row) {
    if ((cell >> 2) == (b >> 2)) {
      cell &= TWO_WALL;
      cell |= (a & ~TWO_WALL);
    }
  }
}

int game::Maze::cellsWithoutBottomWall(std::vector<int>& row, int set) {
  int count = 0;
  for (int& cell : row) {
    if (((cell >> 2) == (set >> 2)) && ((cell & BOTTOM_WALL) != BOTTOM_WALL)) {
      count++;
    }
  }
  return count;
}

void game::Maze::clearSets() {
  for (std::vector<int>& row : maze_) {
    for (int& cell : row) {
      cell &= (RIGHT_WALL | BOTTOM_WALL);
    }
  }
}

void game::Maze::generate() {
  srand(unsigned(time(0)));
  createFirstRow();
  for (int i = 0; i < rows_ - 2; i++) {
    createMiddleRows(i);
  }
  createLastRow(rows_ - 2);
  clearSets();
}

void game::Maze::setSize(int rows, int cols) {
  this->rows_ = rows;
  this->cols_ = cols;
}

void game::Maze::printMaze() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i == 0 && j == 0) {
        for (int k = 0; k < cols_ + 1; k++) {
          std::cout << "__";
        }
        std::cout << std::endl;
      }
      if (j == 0) {
        std::cout << "|";
      }

      if (maze_[i][j] == 0) {
        std::cout << "  ";
      } else if (maze_[i][j] == 1) {
        std::cout << " |";
      } else if (maze_[i][j] == 2) {
        std::cout << "__";
      } else if (maze_[i][j] == 3) {
        std::cout << "_|";
      }

      if (j == cols_ - 1) {
        std::cout << "|";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

std::vector<std::vector<int>> game::Maze::getMaze() { return this->maze_; }
