#include "desktop_view.h"

#include <qdebug.h>
#include <qlogging.h>
#include <qpoint.h>
#include <qvariant.h>

#include <vector>

namespace s21 {
void DesktopView::generateMaze() {
  controller_.generateMaze();
  emit this->mazeDataChanged();
}

void DesktopView::findPath(const QPoint &start, const QPoint &target) {
  Maze::Position startPos = {start.x(), start.y()};
  Maze::Position targetPos = {target.x(), target.y()};
  controller_.findPath(startPos, targetPos);
  emit this->mazeDataChanged();
}

// Функция для преобразования Position в QVariantMap
QVariant positionToVariantMap(const Maze::Position &pos) {
  QVariantMap variantMap;
  variantMap["x"] = pos.x;
  variantMap["y"] = pos.y;
  return variantMap;
}

void DesktopView::saveMazeInFile(const QString &filePath) {
  std::string filePathStd = filePath.toStdString();
  this->controller_.saveMazeInFile(filePathStd);
}

void DesktopView::loadMazeFromFile(const QString &filePath) {
  std::string filePathStd = filePath.toStdString();
  this->controller_.loadMazeFromFile(filePathStd);
  emit this->mazeDataChanged();
}

// Функция для преобразования std::vector<Position> в QVariantList
QVariantList DesktopView::vectorToVariantList() const {
  QVariantList path;
  auto path_data = controller_.getMaze().getPath();

  for (const auto &cell : path_data) {
    QVariantMap cell_data;
    cell_data["x"] = cell.x;
    cell_data["y"] = cell.y;
    path.append(cell_data);
  }
  return path;
}

QVariantList DesktopView::getMazeData() const {
  QVariantList maze_data;
  auto maze = controller_.getMaze().getMaze();
  for (const auto &row : maze) {
    QVariantList row_data;
    for (const auto &cell : row) {
      QVariantMap cell_data;
      cell_data["r_wall"] = cell.r_wall;
      cell_data["b_wall"] = cell.b_wall;
      row_data.append(cell_data);
    }
    maze_data.append(row_data);
  }
  return maze_data;
}

void DesktopView::printLabirinth() {
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