#pragma once

#include <QPointer>
#include <QQuickItem>
#include <QQuickWidget>
#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtCore/QUrl>
#include <QtGui/QImage>
#include <QtQml/QJSValue>
#include <QtQuick/qtquickglobal.h>

#include <iostream>
#include <memory>

class QuickItemSnapShotPrivate;
class QSGLayer;

class QuickItemSnapShot final : public QObject {
  Q_OBJECT
  Q_DECLARE_PRIVATE(QuickItemSnapShot)
public:
  QuickItemSnapShot(QQuickWidget* widget = nullptr);
  ~QuickItemSnapShot() final = default;

  Q_INVOKABLE void
  grabToImage(QQuickItem* item, QString file_name, const QJSValue& callback);

signals:
  void ready();

private:
  void setup();
  void render();
  void save_to_file();

private:
  std::shared_ptr<QuickItemSnapShot> result_;
  QString file_name_;
};