---
layout: post
---

# Overview of QML language

In this post, I want to make a clear framewok of QML language howerver, this post is far from completed, I will update this post when I have new things.

Qt QML module is provides the QML engine and language infrastructure.
Qt QML provides two API:

* [QML API](https://doc.qt.io/qt-5/qtqml-qmlmodule.html): for creating user interface
* [C++ API](https://doc.qt.io/qt-5/qtqml-module.html): for extending QML applications with c++ code.

Qt Quick module is the standard library for writing for QML applications,Providing all the basic types for creating user interfaces with QML.

Qt Quick Control module provides a set of controls can be used to build complete interface in Qt Quick.

## Debug tools

### Test

### qmlscene

[Debugging QML Applications](https://doc.qt.io/qt-5/qtquick-debugging.html)

## syntax

### Import

1. [Import a directory](https://doc.qt.io/qt-5/qtqml-syntax-directoryimports.html)
   1. A local directoy, all qml files, no js files.
   2. A local directoy with a **qmldir** file, types specified in the qmldir file, may have js files.
   3. A remote directoy with a **qmldir** file, types specified in the qmldir file.
   4. Import to a namespace, import a directory dont create a namespace by default, but you can create one with **import dir as namespace**
2. [Import a module/plugin](https://doc.qt.io/qt-5/qtqml-modules-topic.html)
   1. Modules can be [c++ plugins](https://doc.qt.io/qt-5/qqmlextensionplugin.html) or QML documents.
   2. Module is defined and exported by a qmldir file.
   3. Module's name is a namespace.
   4. Module may contains QML types, js resources and c++ plugins, all thie file must in the same directory
   5. [Identified modules](https://doc.qt.io/qt-5/qtqml-modules-identifiedmodules.html)
   6. A module requires at leat one type registered to be considered valid.
   7. Provide type information to qtcretor with **qmltypes** file
3. Import path
   1. Directories contain a module definition qmldir file.
   2. **QML2_IMPORT_PATH** can be set to a list of import path which will be used by any QML application
   3. **QML_IMPORT_PATH** qmake keyword, used in qtcreator
   4. **QML_IMPORT_TRACE** environment variable, if set to **1**, import path will be recoreded in log.

### Scope and name resolution

## Type system

1. [Object Type](https://doc.qt.io/qt-5/qtqml-typesystem-objecttypes.html)
   1. Made from c++
   2. Made form qml

## elements

// TODO create a online inherits diagram

* Visual elements has a geometry on the screen, Item is the base.
* non-visual elements provides some functionality.
* [Item](https://doc.qt.io/qt-5/qml-qtquick-item.html)
* [Component](https://doc.qt.io/qt-5/qml-qtqml-component.html)
  * A seprate qml file
  * A Component type in a qml file.

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
  * [Layout](https://doc.qt.io/qt-5/qml-qtquick-layouts-layout.html)
  * GridLayout
  * ColumnLayout
  * RowLayout
  * StackLayout

  **Note**: A layout is responsible for its children's geometry. You should therefore not specify width, height, x, y or any other properties that might influence those properties (such as anchors) on those items. Otherwise there would be a conflict of interest, and the result is undefined. This is also the case if the child item is a layout. Therefore, only layouts with no parent layout can have anchors.fill: parent.
  
* [QtQuick.Controls](https://doc.qt.io/qt-5/qtquick-controls2-qmlmodule.html)
  * [Action](https://doc.qt.io/qt-5/qml-qtquick-controls2-action.html)
  * [ActionGroup](https://doc.qt.io/qt-5/qml-qtquick-controls2-actiongroup.html)
  * [ApplicationWindow](https://doc.qt.io/qt-5/qml-qtquick-controls2-applicationwindow.html)
  * [ButtonGroup](https://doc.qt.io/qt-5/qml-qtquick-controls2-buttongroup.html)
  * [Controls]((https://doc.qt.io/qt-5/qml-qtquick-controls2-control.html))
    * [AbstractButton](https://doc.qt.io/qt-5/qml-qtquick-controls2-abstractbutton.html)
      * Button
        * RoundButton
        * ToolButton
      * CheckBox
      * DelayButton
      * ItemDelegate
        * CheckDelegate
        * RadioDelegate
        * SwipeDelegate
        * SwitchDelegate
      * MenuBarItem
      * RadioButton
      * Switch
      * TabButton
      * ScrollBar
      * ScrollIndicator
    * [BusyIndicator](https://doc.qt.io/qt-5/qml-qtquick-controls2-busyindicator.html)
    * Combobox
    * Dial
    * MenuSeparator
    * Pane
      * Frame
        * GroupBox
      * Page
      * ScrollView
      * ToolBar
    * PageIndicator
    * ProgressBar
    * RangeSlider
    * Slider
    * SpinBox
    * SplitView
    * StackView
    * ToolSeparator
    * Tumbler
  * [Container](https://doc.qt.io/qt-5/qml-qtquick-controls2-container.html)
    * DialogButtonBox
    * MenuBar
    * SwipeView
    * TabBar
  * Label
  * [Popup](https://doc.qt.io/qt-5/qml-qtquick-controls2-popup.html)
    * Dialog
    * ToolTip
    * Menu
    * Drawer
  * Splithandle
  * [TextArea](https://doc.qt.io/qt-5/qml-qtquick-controls2-textarea.html)
  * TextField
* QtQuick.Window
  * [Window](https://doc.qt.io/qt-5/qml-qtquick-window-window.html)

## user defined elements

* Component

* C++?

## layout

QtQuick.Layouts

* Alignment
* Resizable
* Size constraints
* Spacing

More about item size.

* Item
  * width
  * height
  * implicitWidth, will be used if width is not specified
  * implicitHeight, will be used if height is not specified.
* Layouts
  * Layout.minimumWidth
  * Layout.prefferedHeight
  * Layout.MaxmumWidth

* If Layout.fillWidth/Height set to false, Layout.prefferedWidth/Height will be used; if set to true, width/height is between [min, max]
* The implicitWidth/Height depends on its contents.
* Image and Text has readonly implicitWidth/Height.

Flow

## Controls

Control is the base type of all items in QtQuick.Control.

[Qml Control Type](https://doc.qt.io/qt-5/qml-qtquick-controls2-control.html)

### Manual/Fixed position

### Anchor

### Positioners

### Layout

## State and transtision

## [Model and views](https://doc.qt.io/qt-5/qtquick-modelviewsdata-modelview.html)

model is datas,delegate is responsible visualization for every data, view is like a container to put those UIs.

```cpp
 for data : datas {
    element = delegate(data) // visualize data
    view.add(element)
 }
 ```

Qt has predefined views and models, you can create any UI to serve as a delegate.Most of the time, you may want to create your own delegates and use predefined models and views.

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

### Views

* ListView
* GridView
* PathView

### Repeater

Repeater can be seen as a very basic view, it creates elements according to model and delegate.However, a repeater does't arrange elements it created, and ofen used with Layout/Positioner to do the arrange job.

1. **delegate** is the default property of repeater.
2. The parent of the created elements is the repeater's parent.
3. Delegate of repeater must be a Item-based.
4. All items in repeater have an attached property **index**
5. **model** of repeater can be many types including Models in QML, different type expose different property to delegate.
    1. model object
    2. number

## Interact with c++

* C++ -> QML: c++ code serve as model and do heavy logic
   1. Register c++ class/object to qml engine
   2. Create a plugin with c++
* QML -> C++: Load a qml file to c++ code.
   1. Load with QQmlComponent->load a qml file as a c++ object.
   2. Load with QQuickView/QQuickView.QQuickWidget is a convinient wrapper of QQuickWindow.

[Overview of QML and C++ integration](https://doc.qt.io/qt-5/qtqml-cppintegration-overview.html)

[Interacting with QML Objects from C++](https://doc.qt.io/qt-5/qtqml-cppintegration-interactqmlfromcpp.html)

[Define QML types from c++](https://doc.qt.io/qt-5/qtqml-cppintegration-definetypes.html)

[Creating c++ plugins for QML](https://doc.qt.io/qt-5/qtqml-modules-cppplugins.html)

## Type conversion between QML and C++

[Type conversion between QML and C++](https://doc.qt.io/qt-5/qtqml-cppintegration-data.html)

## [Graphics View Framewok](https://doc.qt.io/qt-5/graphicsview.html)

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