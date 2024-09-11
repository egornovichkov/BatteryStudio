#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QFileInfo>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BatteryChargeWidget = new BatteryCharge(ui->BatInfoWidget);
    ui->InfChargeLayout->addWidget(BatteryChargeWidget);

    QList<int> LRSplitSizes;
    LRSplitSizes << 10 << 35;
    ui->LeftRightPartSplitter->setSizes(LRSplitSizes);
    int id = QFontDatabase::addApplicationFont("D:/Qt/Projects/Battery_Studio/fonts/Roboto-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont f(family);

}

MainWindow::~MainWindow()
{
    delete ui;
}
