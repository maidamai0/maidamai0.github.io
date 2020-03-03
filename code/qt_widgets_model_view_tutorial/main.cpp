#include <QApplication>
#include <QTableView>

#include "model.h"

auto main(int argc, char** argv) -> int {
  QApplication app(argc, argv);
  QTableView table;
  Model model;
  table.setModel(&model);
  table.show();

  return QApplication::exec();
}