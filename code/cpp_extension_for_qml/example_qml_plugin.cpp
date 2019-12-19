#include "example_qml_plugin.h"

void example_qml_plugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("TimeModule"));
    qmlRegisterType<TimeModel>(uri, 1, 0, "Time");
}
