#include "mainwindow.h"
#include <QPainter>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow MainWindow;
    MainWindow.setWindowTitle("Battery Studio 0.0.0");
    MainWindow.setWindowState(Qt::WindowMaximized);
    MainWindow.show();
    return a.exec();
}
