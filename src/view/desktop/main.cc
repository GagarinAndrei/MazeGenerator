#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "desktop_view.h"
#include "../../model/model.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  s21::Maze maze;
  s21::Controller controller(maze);
  s21::DesktopView view(controller);

  // engine.rootContext()->setContextProperty("Controller", &controller);
  engine.rootContext()->setContextProperty("View", &view);

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
