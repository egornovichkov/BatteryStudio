#include "mainwindow.h"
#include "titlebar.h"
#include <QPainter>

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    // MainWindow *MW = new MainWindow();
    TitleBar w(nullptr);
    // MW->setWindowTitle("Battery Studio 0.0.0");
    // MW->setWindowState(Qt::WindowMaximized);
    // MW->show();
    w.show();
    return a.exec();
}
