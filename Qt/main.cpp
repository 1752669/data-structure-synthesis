#include <QGraphicsView>
#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <QGraphicsItem>
#include "Circles.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "MainWindow.h"
void deleteAt(int index);
//窗口显示
int main(int argc, char **argv) {
   QApplication app(argc, argv);
   MainWindow window;
   window.show();
   return QApplication::exec();
}

