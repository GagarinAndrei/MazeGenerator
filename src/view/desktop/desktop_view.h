#ifndef VIEW_DESKTOP_VIEW_H_
#define VIEW_DESKTOP_VIEW_H_

#include <qlogging.h>
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

  // Q_PROPERTY(CaveGenerator::Settings caveSettings /*READ getCaveSettings*/
  // WRITE
  //                setCaveSettings NOTIFY caveSettingsChanged)

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

  // Q_INVOKABLE CaveGenerator::Settings& getCaveSettings() { return
  // this->controller_.getSettings(); }

  inline CaveGenerator &getCave() { return this->controller_.getCave(); }

  inline void setHeightCave(int height) {
    this->controller_.setHeightCave(height);
    this->controller_.getSettings().height = height;
    this->caveWidth_ = height;
    emit caveHeightChanged();
  }

  inline void setWidthCave(int width) {
    this->controller_.setWidthCave(width);
    this->controller_.getSettings().width = width;
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

  // inline void setCaveSettings(const CaveGenerator::Settings &settings) {
  //   this->controller_.setSettings(settings);
  //   emit caveDataChanged();
  // }

  Q_INVOKABLE inline void setBornLimits(int value) {
    this->controller_.getSettings().born_limits = value;
    qDebug() << this->controller_.getSettings().born_limits;
  }

  Q_INVOKABLE inline void setLifeLimits(int value) {
    this->controller_.getSettings().death_limits = value;
    qDebug() << this->controller_.getSettings().death_limits;
  }
  Q_INVOKABLE inline void setInitChance(double value) {
    this->controller_.getSettings().init_chance = value;
    qDebug() << this->controller_.getSettings().init_chance;
  }

 public slots:
  void saveMazeInFile(const QString &filePath);
  void loadMazeFromFile(const QString &filePath);
  void saveCaveInFile(const QString &filePath);
  void loadCaveFromFile(const QString &filePath);

 signals:
  void mazeDataChanged();
  void mazeHeightChanged();
  void mazeWidthChanged();
  void caveDataChanged();
  void caveHeightChanged();
  void caveWidthChanged();

 private:
  Controller &controller_;
  int mazeHeight_;
  int mazeWidth_;
  int caveHeight_;
  int caveWidth_;
};

}  // namespace s21
#endif  // VIEW_DESKTOP_VIEW_H_