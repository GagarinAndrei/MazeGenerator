#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url("qrc:/path/main.qml");  // ссылка на файл qml
  engine.load(url);                      // загружаем файл qml
  return app.exec();
}