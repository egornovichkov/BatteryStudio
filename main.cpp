#include "appwidget.h"
#include <QPainter>

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    AppWidget w;
    w.show();
    return a.exec();
}
