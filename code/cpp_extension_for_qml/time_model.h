#include <QObject>

class TimeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int hour READ hour NOTIFY hourChanged)
    Q_PROPERTY(int minute READ minute NOTIFY minuteChanged)

signals:
    void hourChanged();
    void minuteChanged();

public:
    int hour();
    int minute();

private:
    int hour_ = 17;
    int minute_ = 30;
};
