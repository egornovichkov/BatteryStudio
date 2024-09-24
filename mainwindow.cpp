#include "mainwindow.h"
#include "flag.h"
#include "ui_mainwindow.h"
#include "warning.h"
#include "warninggroup.h"
#include <QFileInfo>
#include <QFontDatabase>
#include <QImage>
#include <QPushButton>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Flags demo
    ui->FlagsWidget->setContentsMargins(5, 0, 0, 0);
    QHBoxLayout *FlagsLayout = new QHBoxLayout(ui->FlagsWidget);
    FlagsLayout->setSpacing(0);
    Flag *F1 = new Flag("Flag1", 0, ui->FlagsWidget);
    Flag *F2 = new Flag("Flag2", 0, ui->FlagsWidget);
    Flag *F3 = new Flag("Flag3", 0, ui->FlagsWidget);
    Flag *F4 = new Flag("Flag4", 0, ui->FlagsWidget);
    Flag *F5 = new Flag("Flag5", 0, ui->FlagsWidget);
    FlagsLayout->addWidget(F1);
    FlagsLayout->addWidget(F2);
    FlagsLayout->addWidget(F3);
    FlagsLayout->addWidget(F4);
    FlagsLayout->addWidget(F5);
    QSpacerItem *FlagsSpacer =
        new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding);
    FlagsLayout->addItem(FlagsSpacer);

    // Warnings demo
    // QVBoxLayout *WarningLayout = new QVBoxLayout(ui->WarningsWidget);
    // WarningLayout->setSpacing(0);
    // WarningLayout->setContentsMargins(0,0,0,0);
    // Warning *W3 = new Warning("High Temperature", "High Temperature",
    // ui->WarningsWidget); WarningLayout->addWidget(W1);
    // WarningLayout->addWidget(W2);
    // WarningLayout->addWidget(W3);

    // WarningsGroup demo
    WarningGroup *WVoltageGroup = new WarningGroup("Voltage", ui->WarningsWidget);
    WarningGroup *WTempGroup =
        new WarningGroup("Temperature", ui->WarningsWidget);
    WarningGroup *WCurrentGroup = new WarningGroup("Current", ui->WarningsWidget);
    WarningGroup *WGeneralGroup = new WarningGroup("General", ui->WarningsWidget);
    QHBoxLayout *WarningGroupLayout = new QHBoxLayout(ui->WarningsWidget);
    WarningGroupLayout->setSpacing(5);
    WarningGroupLayout->setContentsMargins(10, 10, 10, 10);
    WarningGroupLayout->addWidget(WVoltageGroup);
    WarningGroupLayout->addWidget(WTempGroup);
    WarningGroupLayout->addWidget(WCurrentGroup);
    WarningGroupLayout->addWidget(WGeneralGroup);
    Warning *W2 = new Warning("Low Voltage", "Low Voltage", WVoltageGroup);
    Warning *W1 = new Warning("High Voltage", "High Voltage", WVoltageGroup);
    WVoltageGroup->addWarning(W1);
    WVoltageGroup->addWarning(W2);

    // MenuBar demo
    // ui->menuBar->

    // LeftRightPartSplitter initial sizes
    QList<int> LRSplitSizes;
    LRSplitSizes << 100 << 300;
    ui->LeftRightPartSplitter->setSizes(LRSplitSizes);

    // BatInfoWarningsSplitter initial sizes
    QList<int> BatInfoWarningsSizes;
    BatInfoWarningsSizes << 300 << 100;
    ui->BatInfoWarningsSplitter->setSizes(BatInfoWarningsSizes);

    // Adding fonts
    int id = QFontDatabase::addApplicationFont(
        "D:/Qt/Projects/Battery_Studio/fonts/Roboto-Medium.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont f(family);
    f.setHintingPreference(QFont::HintingPreference::PreferFullHinting);

    this->setWindowFlag(Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}
