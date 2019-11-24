---
layout: post
---

# Overview of QML language

In this post, I tryed to make a clear framewok of QML language howerver, this post is far from completed, I will update this post when I have new things.

Qt QML module is provides the QML engine and language infrastructure.
Qt QML provides two API:

* QML API: for creating user interface
* C++ API: for extending QML applications with c++ code.

Qt Quick module is the standard library for writing for QML applications,Providing all the basic types for creating user interfaces with QML.

Qt Quick Control module provides a set of controls can be used to build complete interface in Qt Quick.

## Debug tools

### Test

### qmlscene

### QML import path

Parent directory of *qmldir* file.

* QML2_IMPORT_PATH environment variable

* QML_IMPORT_TRACE environment variable
* QML_IMPORT_PATH qmake keyword, used in qtcreator

[QML Import Path](https://doc.qt.io/qt-5/qtqml-syntax-imports.html#qml-import-path)

[Debugging QML Applications](https://doc.qt.io/qt-5/qtquick-debugging.html)

## syntax

### Scope and name resolution

## Type system

## elements

* Visual elements has a geometry on the screen, Item is the base.
* non-visual elements provides some functionality.
* [Item](https://doc.qt.io/qt-5/qml-qtquick-item.html)

* QtQuick
  * Rectangle
  * MouseArea
  * Image
  * Text
  * [Canvas](https://doc.qt.io/qt-5/qml-qtquick-canvas.html)
  * Grid
  * Column
  * Row
* [QtQuick.layouts](https://doc.qt.io/qt-5/qtquicklayouts-overview.html)
  * GridLayout
  * ColumnLayout
  * RowLayout
  * StackLayout
* [QtQuick.Controls](https://doc.qt.io/qt-5/qml-qtquick-controls2-control.html)
  * Controls

## user defined elements

* Component

* C++?

## layout

## Controls

Control is the base type of all items in QtQuick.Control.

[Qml Control Type](https://doc.qt.io/qt-5/qml-qtquick-controls2-control.html)

### Manual/Fixed position

### Anchor

### Positioners

### Layout

## Model and views

## State and

model is datas,delegate is responsible visualization for every data, view is like a container to put those UIs.

Qt has predefined views and models, you can create any UI to serve as a delegate.

```cpp
 for data : datas {
    element = delegate(data) // visualize data
    view.add(element)
 }
 ```

Most of the time, you may want to create your own delegates and use predefined models and views.

### Model

* role, can be accessed directly or through model.[role_name]
* modelData role
* index role

#### QML predefined model

ListModel

#### Use C++ Model

* QList<QObject*>, access with model.model.ModelDta[.property]
* QStringList, access with model.modelData

[Using C++ Models with Qt Quick Views](https://doc.qt.io/qt-5/qtquick-modelviewsdata-cppmodels.html#qobjectlist-based-model)

### Repeater

Repeater can be seen as a very basic view, it creates elements according to model and delegate.However, repeater does't arrange elements it created, and ofen used with Layout/Positioner,the parent of the created elements is repeater's parent.Delegate of repeater must be a Item-based.

delegate is the default property of repeater.

model of repeater can be many types including Models in QML, different type expose different property to delegate.

* model object
* number

## interact with c++

[Define QML types from c++](https://doc.qt.io/qt-5/qtqml-cppintegration-definetypes.html)

## Scene graph

## Frame graph

## 3D

## Multi-threads

QML/Js engine is single thread?
[WorkerScript](https://doc.qt.io/qt-5/qml-qtqml-workerscript.html)

## Reference

* [Qt Quick](https://doc-snapshots.qt.io/qt5-dev/qtquick-index.html#)
* [Qt Quick Controls](https://doc.qt.io/qt-5/qtquickcontrols-index.html)
* [Scope and name resolution](https://doc.qt.io/qt-5/qtqml-documents-scope.html)
* [Qt QML base type](https://doc-snapshots.qt.io/qt5-dev/qtqml-qmlmodule.html)
* [Use Case - Positioners and Layouts In QML](https://doc.qt.io/qt-5/qtquick-usecase-layouts.html)
* [Important Concepts In Qt Quick - Positioning](https://doc.qt.io/qt-5/qtquick-positioning-topic.html)
* [Models and Views in Qt Quick](https://doc-snapshots.qt.io/qt5-dev/qtquick-modelviewsdata-modelview.html)