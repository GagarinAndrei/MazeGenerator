#ifndef VIEW_DESKTOP_VIEW_H_
#define VIEW_DESKTOP_VIEW_H_

#include <qpoint.h>
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

  Q_PROPERTY(QVariant caveData READ getCaveData NOTIFY caveDataChanged)
  Q_PROPERTY(int caveHeight READ getHeightCave WRITE setHeightCave NOTIFY
                 caveHeightChanged)
  Q_PROPERTY(int caveWidth READ getWidthCave WRITE setWidthCave NOTIFY
                 caveHeightChanged)

  // Q_PROPERTY(CaveGenerator::Settings initChance READ getInitChance WRITE
  //                setInitChance NOTIFY initChanceChanged)

 public:
  DesktopView(Controller &controller, QObject *parent = nullptr)
      : QObject{parent},
        controller_{controller},
        mazeHeight_{},
        mazeWidth_{},
        caveHeight_{},
        caveWidth_{} {};
  ~DesktopView() = default;

  Q_INVOKABLE QVariantList getMazeData() const;
  Q_INVOKABLE void generateMaze();
  Q_INVOKABLE void findPath(const QPoint &start, const QPoint &target);
  Q_INVOKABLE QVariantList vectorToVariantList() const;
  Q_INVOKABLE int getHeight() { return this->controller_.getHeight(); }
  Q_INVOKABLE int getWidth() { return this->controller_.getWidth(); }

  Q_INVOKABLE QVariantList getCaveData() const;
  Q_INVOKABLE void generateCave();
  Q_INVOKABLE int getHeightCave() { return this->controller_.getHeightCave(); }
  Q_INVOKABLE int getWidthCave() { return this->controller_.getWidthCave(); }

  // Q_INVOKABLE int getSettings() { return this->controller_.getSSettings(); }

  inline CaveGenerator &getCave() { return this->controller_.getCave(); }

  inline void setHeightCave(int height) {
    this->controller_.setHeightCave(height);
    this->caveWidth_ = height;
    emit caveHeightChanged();
  }

  inline void setWidthCave(int width) {
    this->controller_.setWidthCave(width);
    this->mazeWidth_ = width;
    emit caveWidthChanged();
  }

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

  // inline void setBornLimits(int born_limits) {
  //   this->controller_.setBornLimits(born_limits);
  //   emit bornLimitsChanged();
  // }

  // inline void setLifeLimits(int life_limits) {
  //   this->controller_.setLifeLimits(life_limits);
  //   emit lifeLimitsChanged();
  // }

  // inline void setInitChance(double init_chance) {
  //   this->controller_.setInitChance(init_chance);
  //   emit initChanceChanged();
  // }

 public slots:
  void saveMazeInFile(const QString &filePath);
  void loadMazeFromFile(const QString &filePath);
  void saveCaveInFile(const QString &filePath);
  void loadCaveFromFile(const QString &filePath);

  void setInitChance(double value) {
    this->controller_.getSettings().init_chance = value;
  }

  void setBornLimits(int value) {
    this->controller_.getSettings().born_limits = value;
  }

  void setLifeLimits(int value) {
    this->controller_.getSettings().death_limits = value;
  }

 signals:
  void mazeDataChanged();
  void mazeHeightChanged();
  void mazeWidthChanged();
  void caveDataChanged();
  void caveHeightChanged();
  void caveWidthChanged();
  void initChanceChanged();
  void bornLimitsChanged();
  void lifeLimitsChanged();

 private:
  Controller &controller_;
  int mazeHeight_;
  int mazeWidth_;
  int caveHeight_;
  int caveWidth_;
};

}  // namespace s21
#endif  // VIEW_DESKTOP_VIEW_H_