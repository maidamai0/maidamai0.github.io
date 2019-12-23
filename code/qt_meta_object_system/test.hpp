#pragma once

#include <QObject>

class UserModel : public QObject
{
public:
  __pragma(warning(push)) static const QMetaObject staticMetaObject;
  virtual const QMetaObject *metaObject() const;
  virtual void *qt_metacast(const char *);
  virtual int qt_metacall(QMetaObject::Call, int, void **);
  static inline QString tr(const char *s, const char *c = nullptr, int n = -1) { return staticMetaObject.tr(s, c, n); }
  static inline QString trUtf8(const char *s, const char *c = nullptr, int n = -1) { return staticMetaObject.tr(s, c, n); }

private:
  static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **);
  __pragma(warning(pop)) struct QPrivateSignal
  {
  };

public:
  int name() const;

public:
  void signIn();
  void onNameChanged(int value);

public:
  void login(bool success);

private:
  void on_client_finished(int error);
};
