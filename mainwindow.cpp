#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QFileInfo>
#include <QImage>
#include <QPushButton>
#include "flag.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *FlagsLayout = new QGridLayout(ui->FlagsWidget);
    Flag *F1 = new Flag("Flag1", 0, ui->FlagsWidget);
    Flag *F2 = new Flag("Flag2", 0, ui->FlagsWidget);
    Flag *F3 = new Flag("Flag3", 0, ui->FlagsWidget);
    FlagsLayout->addWidget(F1, 0, 0);
    FlagsLayout->addWidget(F2, 0, 1);
    FlagsLayout->addWidget(F3, 1, 1);
    QPushButton *btn = new QPushButton(ui->FlagsWidget);
    FlagsLayout->addWidget(btn, 1, 0);


    // LeftRightPartSplitter initial sizes
    QList<int> LRSplitSizes;
    LRSplitSizes << 100 << 350;
    ui->LeftRightPartSplitter->setSizes(LRSplitSizes);

    // Adding fonts
    int id = QFontDatabase::addApplicationFont("D:/Qt/Projects/Battery_Studio/fonts/Roboto-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont f(family);
    f.setHintingPreference(QFont::HintingPreference::PreferFullHinting);
}

MainWindow::~MainWindow()
{
    delete ui;
}
