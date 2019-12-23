#pragma once

#include <QObject>

class UserModel : public QObject {
  Q_OBJECT
  Q_PROPERTY(int name READ name WRITE setName NOTIFY onNameChanged)

 public:
   void  signIn();

 public :
  void login(bool success);

 private :
  void on_client_finished(int error);
};