#ifndef VIEW_DESKTOP_VIEW_H_
#define VIEW_DESKTOP_VIEW_H_

#include <qtmetamacros.h>
#include <qvariant.h>

#include "../../controller/controller.h"
#include "qobject.h"

namespace s21 {

class DesktopView : public QObject {
  Q_OBJECT

  Q_PROPERTY(QVariant mazeData READ getMazeData NOTIFY mazeDataChanged)
  Q_PROPERTY(
      int mazeHeight READ getHeight WRITE setHeight NOTIFY mazeHeightChanged)
  Q_PROPERTY(
      int mazeWidth READ getWidth WRITE setWidth NOTIFY mazeHeightChanged)

 public:
  DesktopView(Controller &controller, QObject *parent = nullptr)
      : QObject{parent}, controller_{controller}, mazeHeight_{}, mazeWidth_{} {
        };
  ~DesktopView() = default;

  Q_INVOKABLE QVariant getMazeData() const;
  Q_INVOKABLE void generateMaze();
  Q_INVOKABLE void findPath(const QVariant &start, const QVariant &target);
  Q_INVOKABLE void printLabirinth();  // for debug

  inline Maze &getMaze() { return this->controller_.getMaze(); }
  // Q_INVOKABLE QVariantList getPath() const;
  Q_INVOKABLE QVariantList vectorToVariantList();

  Q_INVOKABLE int getHeight() { return this->controller_.getHeight(); }
  Q_INVOKABLE int getWidth() { return this->controller_.getWidth(); }

  inline void setHeight(int height) {
    this->controller_.setHeight(height);
    this->mazeHeight_ = height;
    emit mazeHeightChanged();
  }
  inline void setWidth(int width) {
    this->controller_.setWidth(width);
    this->mazeWidth_ = width;
    emit mazeWidthChanged();
  }

 public slots:
  void saveMazeInFile(const QString &filePath);
  void loadMazeFromFile(const QString &filePath);

 signals:
  void mazeDataChanged();
  void mazeHeightChanged();
  void mazeWidthChanged();

 private:
  Controller &controller_;
  int mazeHeight_;
  int mazeWidth_;
};

}  // namespace s21
#endif  // VIEW_DESKTOP_VIEW_H_