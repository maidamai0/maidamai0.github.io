# Qt meta object system

## source tree

1. test.h is a typical header file in qt frame work, which contains a class inherit from QObject and has some qt specific key word.
2. text.hpp is the [msvc preprocessor](https://docs.microsoft.com/en-us/cpp/build/reference/p-preprocess-to-a-file?view=vs-2019) generated class after removing un-necessary things.
3. moc_test.cpp is the [moc](https://doc.qt.io/qt-5/moc.html) result.

## Reference

[How Qt Signals and Slots Work](https://woboq.com/blog/how-qt-signals-slots-work.html)