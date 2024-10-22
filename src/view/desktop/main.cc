#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "../../controller/controller.h"
#include "../../model/maze.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  s21::Maze maze;
  s21::Controller controller(maze);

  engine.rootContext()->setContextProperty("Controller", &controller);

  //  qmlRegisterType<s21::Controller>("ControllerModule", 1, 0, "Controller");
  const QUrl url("qrc:/path/main.qml");  // ссылка на файл qml
  //  engine.load(url);                      // загружаем файл qml

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);
  return app.exec();
}
