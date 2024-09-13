#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QFileInfo>
#include <QImage>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // BatChargeIcon initial size
    int BatChargeLayoutLMargin = ui->BatInfoLayout->contentsMargins().left();
    int BatChargeLayoutRMargin = ui->BatInfoLayout->contentsMargins().right();
    int BatChargeWidgetWidth = ui->BatChargeWidget->width();
    int BatChargeHorizontalSpacerLWidth = (BatChargeWidgetWidth -
    BatChargeLayoutLMargin - BatChargeLayoutRMargin) / 3;
    ui->BatChargeHorizontalSpacerL->changeSize(BatChargeHorizontalSpacerLWidth, 20);

    // LeftRightPartSplitter initial sizes
    QList<int> LRSplitSizes;
    LRSplitSizes << 10 << 35;
    ui->LeftRightPartSplitter->setSizes(LRSplitSizes);

    // Adding fonts
    int id = QFontDatabase::addApplicationFont("D:/Qt/Projects/Battery_Studio/fonts/Roboto-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont f(family);
}

MainWindow::~MainWindow()
{
    delete ui;
}
