#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<int> LRSplitSizes;
    LRSplitSizes << 10 << 35;
    ui->LeftRightPartSplitter->setSizes(LRSplitSizes);
    int id = QFontDatabase::addApplicationFont(":/fonts/Inter-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
    QFont f(family);  // QFont c вашим шрифтом
}

MainWindow::~MainWindow()
{
    delete ui;
}
