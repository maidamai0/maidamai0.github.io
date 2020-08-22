#include "qreport.h"

#include <QApplication>

#ifndef ASSETS_PATH
#  define ASSETS_PATH ""
#endif

auto main(int argc, char** argv) -> int {
  QApplication app(argc, argv); // QImage need this
  QReport report;
  report.MakePDFReport(ASSETS_PATH);
}