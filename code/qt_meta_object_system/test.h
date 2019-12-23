#pragma once

#include <QObject>

class UserModel : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int name READ name WRITE setName NOTIFY onNameChanged)

public:
  int name() const;

signals:
  void signIn();
  void onNameChanged(int value);

public:
  void login(bool success);

private slots:
  void on_client_finished(int error);
};