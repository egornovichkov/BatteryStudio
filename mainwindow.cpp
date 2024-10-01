#include "mainwindow.h"
#include "flag.h"
#include "ui_mainwindow.h"
#include "warning.h"
#include "warninggroup.h"
#include <QFileInfo>
#include <QFontDatabase>
#include <QImage>
#include <QPushButton>
#include <QMouseEvent>
#include "appwidget.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    setMouseTracking(true);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QApplication::postEvent(parent(), event);
}

/// Handler for the mouse press event.
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QApplication::postEvent(parent(), event);
}

/// Handler for the mouse release event.
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::postEvent(parent(), event);
}

// bool MainWindow::eventFilter(QObject *obj, QEvent *event)
// {
//     Q_UNUSED(obj);

//     if ((event->type() == QEvent::MouseMove || event->type() == QEvent::MouseButtonPress
//         || event->type() == QEvent::MouseButtonRelease) && (parent() != nullptr))
//     {
//         QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
//         return checkResizableField(mouseEvent);
//     }
//     return true;
// }

// /// @brief Function which returns mouse type due to its position within the window.
// bool MainWindow::checkResizableField(QMouseEvent *event)
// {
//     QPointF position = event->globalPosition();
//     qreal x = this->x();
//     qreal y = this->y();
//     qreal width = this->width();
//     qreal height = this->height();
//     std::cout << x << " " << y << " " << width << " " << height << "\n";

//     qreal fieldSize = 5;

//     qreal borderRad = 5; // MUST BE CHANGED!

//     QRectF rectBottom(x + borderRad, y + height - fieldSize, width - 2 * borderRad, fieldSize);
//     QRectF rectLeft(x, y + borderRad, fieldSize, height - 2 * borderRad);
//     QRectF rectRight(x + width - fieldSize, y + borderRad, fieldSize, height - 2 * borderRad);

//     if (rectBottom.contains(position) || rectLeft.contains(position) || rectRight.contains(position))
//     {
//         return true;
//     }
//     return false;
// }
