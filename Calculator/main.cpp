#include <QApplication>

#include "CalcScreen/calcwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  nex::CalcWindow w;
  w.show();
  return a.exec();
}
