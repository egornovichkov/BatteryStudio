#include "mainwindow.h"
#include <QPainter>
#include "ui_mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow MainWindow;
    MainWindow.setWindowTitle("Battery Studio 0.0.0");
    MainWindow.show();
    return a.exec();
}
