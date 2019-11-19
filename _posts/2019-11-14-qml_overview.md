---
layout: post
---

# Overview of QML language

Qt QML module is provides the QML engine and language infrastructure.
Qt QML provides two API:

* QML API: for creating user interface
* C++ API: for extending QML applications with c++ code.

Qt Quick module is the standard library for writing for QML applications,Providing all the basic types for creating user interfaces with QML.

Qt Quick Control module provides a set of controls can be used to build complete interface in Qt Quick.

## syntax

### Scope and name resolution

## Type system

## elements

* Visual elements has a geometry on the screen, Item is the base.
* non-visual elements provides some functionality.

## user defined elements

* Component

* C++?

## layout

### Manual/Fixed position

### Anchor

### Positioners

### Layout

## Model and views

model is datas,delegate is responsible visualization for every data, view is like a container to put those UIs.

Qt has predefined views and models, you can create any UI to serve as a delegate.

``` pseudo code
 for data : datas {
    element = delegate(data) // visualize data
    view.add(element)
 }
 ```

Most of the time, you may want to create your own delegates and use predefined models and views.

### Model

* role, can be accessed directly or through model.[role_name]
* modelData
* index

## interact with c++

[Define QML types from c++](https://doc.qt.io/qt-5/qtqml-cppintegration-definetypes.html)

## Scene graph

## Reference

* [Qt Quick](https://doc-snapshots.qt.io/qt5-dev/qtquick-index.html#)
* [Qt Quick Controls](https://doc.qt.io/qt-5/qtquickcontrols-index.html)
* [Scope and name resolution](https://doc.qt.io/qt-5/qtqml-documents-scope.html)
* [Qt QML base type](https://doc-snapshots.qt.io/qt5-dev/qtqml-qmlmodule.html)
* [Use Case - Positioners and Layouts In QML](https://doc.qt.io/qt-5/qtquick-usecase-layouts.html)
* [Important Concepts In Qt Quick - Positioning](https://doc.qt.io/qt-5/qtquick-positioning-topic.html)
* [Models and Views in Qt Quick](https://doc-snapshots.qt.io/qt5-dev/qtquick-modelviewsdata-modelview.html)