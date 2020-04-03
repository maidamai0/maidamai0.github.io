#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQuickWidgets/QQuickWidget>
#include <qquickview.h>

auto main(int argc, char* argv[]) -> int {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication app(argc, argv);

  // QQuickWidget* q = new QQuickWidget;
  // q->setResizeMode(QQuickWidget::SizeRootObjectToView);
  // q->setSource(
  //   QUrl("file:///D:/open_source_project/maidamai0.github.io/code/grab_"
  //        "image_in_qml/main.qml"));
  // q->show();

  // QQuickView* q = new QQuickView;
  // q->setResizeMode(QQuickView::SizeRootObjectToView);
  // q->setSource(QUrl("file:///D:/open_source_project/maidamai0.github.io/code/"
  //                   "grab_image_in_qml/main.qml"));

  // QWidget* container = QWidget::createWindowContainer(q);
  // container->show();

  QQmlApplicationEngine engine;
  const QUrl url(
    QStringLiteral("file:///D:/open_source_project/maidamai0.github.io/code/"
                   "grab_image_in_qml/main.qml"));
  QObject::connect(
    &engine, &QQmlApplicationEngine::objectCreated, &app,
    [url](QObject* obj, const QUrl& objUrl) {
      if (!obj && url == objUrl)
        QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}