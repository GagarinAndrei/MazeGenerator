#include "controller.h"

namespace s21 {

void Controller::generateMaze() {
  this->maze_.generate();
  emit this->mazeDataChanged();
}
void Controller::saveMazeInFile() { this->maze_.saveMazeInFile(); }
void Controller::loadMazeFromFile(const std::string &filename) {
  this->maze_.loadMazeFromFile(filename);
}

QVariant Controller::getMazeData() const {
  // QVariantList mazeData;
  // for (const auto &row : maze_.getMaze()) {
  //   QVariantList rowData;
  //   for (const auto &cell : row) {
  //     QVariantMap cellData;
  //     cellData["r_wall"] = cell.r_wall;
  //     cellData["b_wall"] = cell.b_wall;
  //     rowData.append(cellData);
  //   }
  //   mazeData.append(rowData);
  // }
  // qDebug() << "Maze Data from getMazeData:" << mazeData;  // for debug

  // return mazeData;
  QVariantList mazeData;
  auto maze = maze_.getMaze();
  qDebug() << "Maze size:" << maze.size();  // for debug
  for (const auto &row : maze) {
    QVariantList rowData;
    for (const auto &cell : row) {
      QVariantMap cellData;
      cellData["r_wall"] = cell.r_wall;
      cellData["b_wall"] = cell.b_wall;
      rowData.append(cellData);
    }
    mazeData.append(rowData);
  }
  qDebug() << "Maze Data:" << mazeData;  // for debug
  return mazeData;
}

void Controller::printLabirinth() {
  qDebug() << "-= MAZE =-";

  Maze &maze = this->getMaze();
  int height = maze.getHeight();
  int width = maze.getWidth();

  for (int i = 0; i < height; ++i) {
    QString row;
    row += "|";  // Левая граница

    for (int j = 0; j < width; ++j) {
      if (maze.getMaze()[i][j].r_wall && maze.getMaze()[i][j].b_wall) {
        row += "_|";
      } else if (maze.getMaze()[i][j].r_wall) {
        row += " |";
      } else if (maze.getMaze()[i][j].b_wall) {
        row += "__";
      } else {
        row += "  ";
      }
    }
    qDebug() << row;
  }
}
}  // namespace s21
