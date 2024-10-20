#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QObject>

#include "../../model/maze.h"
int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  qmlRegisterType<s21::Maze>("com.example.maze", 1, 0, "Maze");
  
  QQmlApplicationEngine engine;
  const QUrl url("qrc:/path/main.qml");  // ссылка на файл qml
  engine.load(url);                      // загружаем файл qml
  return app.exec();
}