TEMPLATE = lib
CONFIG += qt plugin
QT += qml

DESTDIR = $$PWD/TimeModule
TARGET = example_qml_plugin

HEADERS += $$files("*.h", true)
SOURCES += $$files("*.cpp", true)

OTHER_FILES += $$files("*.md", true)
OTHER_FILES += $$files("*.qml", true)
OTHER_FILES += qmldir
