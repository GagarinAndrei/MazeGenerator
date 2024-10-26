#include "desktop_view.h"

namespace s21 {
void DesktopView::generateMaze() {
  controller_.generateMaze();
  emit this->mazeDataChanged();
}

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