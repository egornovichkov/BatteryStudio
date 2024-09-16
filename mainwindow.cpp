#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
#include <QFileInfo>
#include <QImage>
#include <QPushButton>
#include "flag.h"
#include "warning.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Flags demonstration
    QGridLayout *FlagsLayout = new QGridLayout(ui->FlagsWidget);
    FlagsLayout->setSpacing(0);
    FlagsLayout->setContentsMargins(5,0,0,0);
    Flag *F1 = new Flag("Flag1", 0, ui->FlagsWidget);
    Flag *F2 = new Flag("Flag2", 0, ui->FlagsWidget);
    Flag *F3 = new Flag("Flag3", 0, ui->FlagsWidget);
    Flag *F4 = new Flag("Flag3", 0, ui->FlagsWidget);
    Flag *F5 = new Flag("Flag3", 0, ui->FlagsWidget);
    FlagsLayout->addWidget(F1, 0, 0);
    FlagsLayout->addWidget(F2, 0, 1);
    FlagsLayout->addWidget(F3);
    FlagsLayout->addWidget(F4);
    FlagsLayout->addWidget(F5);

    //Warnings demonstration
    QVBoxLayout *WarningLayout = new QVBoxLayout(ui->WarningsWidget);
    FlagsLayout->setSpacing(0);
    FlagsLayout->setContentsMargins(0,0,0,0);
    Warning *W1 = new Warning("High Voltage", "High Voltage", ui->WarningsWidget);
    Warning *W2 = new Warning("Low Voltage", "Low Voltage", ui->WarningsWidget);
    Warning *W3 = new Warning("High Temperature", "High Temperature", ui->WarningsWidget);
    WarningLayout->addWidget(W1);
    WarningLayout->addWidget(W2);
    WarningLayout->addWidget(W3);

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
