#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "../../model/maze.h"
#include "../../model/model.h"
#include "desktop_view.h"
int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  qmlRegisterType<s21::Maze>("com.example.maze", 1, 0, "Maze");

  QQmlApplicationEngine engine;

  s21::Maze maze;
  s21::Controller controller(maze);
  s21::DesktopView view(controller);

  engine.rootContext()->setContextProperty("View", &view);

  const QUrl url("qrc:/path/main.qml");  // ссылка на файл qml

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);
  return app.exec();
}
