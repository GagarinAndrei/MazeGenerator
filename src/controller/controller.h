#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <qdebug.h>
#include <qlogging.h>
#include <qtmetamacros.h>
#include <qvariant.h>

#include "../model/maze.h"
#include "qobject.h"
// #include "qtmetamacros.h"

namespace s21 {

class Controller : public QObject {
  Q_OBJECT

  Q_PROPERTY(QVariant mazeData READ getMazeData NOTIFY mazeDataChanged)
  Q_PROPERTY(
      int mazeHeight READ getHeight WRITE setHeight NOTIFY mazeHeightChanged)
  Q_PROPERTY(
      int mazeWidth READ getWidth WRITE setWidth NOTIFY mazeHeightChanged)
 public:
  explicit Controller(Maze &maze, QObject *parent = nullptr)
      : QObject{parent}, maze_{maze} {}
  ~Controller() {}

  inline Maze &getMaze() { return this->maze_; }

  QVariant getMazeData() const;
  inline int getHeight() { return this->maze_.getHeight(); }
  inline int getWidth() { return this->maze_.getWidth(); }
  inline void setHeight(int height) {
    this->maze_.setHeight(height);
    emit mazeHeightChanged();
    qDebug() << "height: " << maze_.getHeight();
  }
  inline void setWidth(int width) {
    this->maze_.setWidth(width);
    emit mazeWidthChanged();
    qDebug() << "width: " << maze_.getWidth();
  }

  Q_INVOKABLE void generateMaze();
  Q_INVOKABLE void saveMazeInFile();
  Q_INVOKABLE void loadMazeFromFile(const std::string &filename);

  Q_INVOKABLE void printLabirinth();  // for debug

 signals:
  void mazeDataChanged();
  void mazeHeightChanged();
  void mazeWidthChanged();

 private:
  Maze &maze_;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_
