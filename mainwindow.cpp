#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<int> LRSplitSizes;
    LRSplitSizes << 10 << 35;
    ui->LeftRightPartSplitter->setSizes(LRSplitSizes);
}

MainWindow::~MainWindow()
{
    delete ui;
}
