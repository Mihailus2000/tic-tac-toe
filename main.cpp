#include "mainwindow.h"
#include <QApplication>

int MapSize = 3;
QString YOUR_ROLE = "E";

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  MainWindow w;
  w.show();



  // Обработка событий - основной цикл работы программы
  return a.exec();
}
