#include "desktop_view.h"

#include <qvariant.h>

#include <vector>

namespace s21 {
void DesktopView::generateMaze() {
  controller_.generateMaze();
  emit this->mazeDataChanged();
}

void DesktopView::findPath(const QVariant &start, const QVariant &target) {
  Maze::Position startPos = start.value<Maze::Position>();
  Maze::Position targetPos = target.value<Maze::Position>();

  controller_.findPath(startPos, targetPos);
  emit this->mazeDataChanged();
}

// Функция для преобразования Position в QVariantMap
QVariantMap positionToVariantMap(const Maze::Position &pos) {
  QVariantMap variantMap;
  variantMap["x"] = pos.x;
  variantMap["y"] = pos.y;
  return variantMap;
}

// Функция для преобразования std::vector<Position> в QVariantList
QVariantList DesktopView::vectorToVariantList() {
  QVariantList variantList;
  const std::vector<Maze::Position>& vec = controller_.getMaze().getPath();
  std::transform(
      vec.begin(), vec.end(), std::back_inserter(variantList),
      [](const Maze::Position &pos) { return positionToVariantMap(pos); });
  return variantList;
}

// QVariantList DesktopView::getPath() const {
//     QVariantList path;
//     const std::vector<Maze::Position>& mazePath =
//     controller_.getMaze().getPath(); for (const auto& pos : mazePath) {
//         path.append(QVariant::fromValue(pos));
//     }
//         qDebug() << "getPath:" << path;  // Добавьте это для отладки
//         std::vector<Maze::Position> &path_test =
//         controller_.getMaze().getPath(); for (auto item : path_test) {
//         qDebug() << "path_: x = " << item.x << " - y = " << item.y ;  //
//         Добавьте это для отладки
//         }
//     return path;
// }

void DesktopView::saveMazeInFile(const QString &filePath) {
  std::string filePathStd = filePath.toStdString();
  qDebug() << "Saving maze to file:" << filePath;
  this->controller_.saveMazeInFile(filePathStd);
}

void DesktopView::loadMazeFromFile(const QString &filePath) {
  std::string filePathStd = filePath.toStdString();
  this->controller_.loadMazeFromFile(filePathStd);
  emit this->mazeDataChanged();
}

QVariant DesktopView::getMazeData() const {
  QVariantList mazeData;
  auto maze = controller_.getMaze().getMaze();
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
  return mazeData;
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