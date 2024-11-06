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
  Maze::Position start_pos = {start.x(), start.y()};
  Maze::Position targe_pos = {target.x(), target.y()};
  controller_.findPath(start_pos, targe_pos);
  emit this->mazeDataChanged();
}

// Функция для преобразования Position в QVariantMap
QVariant positionToVariantMap(const Maze::Position &pos) {
  QVariantMap variant_map;
  variant_map["x"] = pos.x;
  variant_map["y"] = pos.y;
  return variant_map;
}

void DesktopView::saveMazeInFile(const QString &filePath) {
  std::string file_path_std = filePath.toStdString();
  this->controller_.saveMazeInFile(file_path_std);
}

void DesktopView::loadMazeFromFile(const QString &filePath) {
  std::string file_path_std = filePath.toStdString();
  this->controller_.loadMazeFromFile(file_path_std);
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

void DesktopView::generateCave() {
  controller_.generateCave();
  emit this->caveDataChanged();
}

void DesktopView::saveCaveInFile(const QString &filePath) {
  std::string file_path_std = filePath.toStdString();
  this->controller_.saveCaveInFile(file_path_std);
}

void DesktopView::loadCaveFromFile(const QString &filePath) {
  std::string file_path_std = filePath.toStdString();
  this->controller_.loadCaveFromFile(file_path_std);
  emit this->mazeDataChanged();
}

QVariantList DesktopView::getCaveData() const {
  QVariantList cave_data;
  auto cave = controller_.getCave().getCave();
  for (const auto &row : cave) {
    QVariantList row_data;
    for (const auto &cell : row) {
      QVariantMap cell_data;
      cell_data["block"] = cell;
      row_data.append(cell_data);
    }
    cave_data.append(row_data);
  }
  return cave_data;
}

}  // namespace s21