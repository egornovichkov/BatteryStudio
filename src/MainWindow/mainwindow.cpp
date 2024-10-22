#include "mainwindow.h"
#include "../Flag/flag.h"
#include "src/Models/CellsDataModel/cellstableproxymodel.h"
#include "ui_mainwindow.h"
#include "../Warning/warning.h"
#include "../Warning/warninggroup.h"
#include <QFileInfo>
#include <QFontDatabase>
#include <QImage>
#include <QPushButton>
#include <QMouseEvent>
#include <QWKWidgets/widgetwindowagent.h>

#include <QTableView>
#include "../Models/CellsDataModel/cellsdatamodel.h"
#include "../Views/CellsDataView/cellstableviewwidget.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>
#include <QtWidgets/QPushButton>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    #include <QtGui/QActionGroup>
#else
    #include <QtWidgets/QActionGroup>
#endif

#include "../WidgetFrame/src/windowbar.h"
#include "../WidgetFrame/src/windowbutton.h"

#include <QAbstractItemModelTester>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_DontCreateNativeAncestors);
    installWindowAgent();
    ui->setupUi(this);
    setTitleBarStyleSheet();

    // Cells data model
    CellsDataModel *cellsData = new CellsDataModel(BSTU::VoltageType);
    cellsData->setMinVal(0);
    cellsData->setMaxVal(5);

    // Cells proxy model
    CellsTableProxyModel *cellsProxyModel = new CellsTableProxyModel();
    cellsProxyModel->setSourceModel(cellsData);

    // Cells table view
    CellsTableViewWidget *cellsTableView = new CellsTableViewWidget(ui->VoltCellsWidget);
    ui->VoltCellsLayout->addWidget(cellsTableView);
    cellsTableView->setModel(cellsProxyModel);


    // Adding data
    for (int i = 0; i < 40; ++i)
    {
        cellsData->appendCell(3.3);
        cellsData->appendCell(0.2);
        cellsData->appendCell(0.9);
        cellsData->appendCell(3.9);
        cellsData->appendCell(3.5);
        cellsData->appendCell(3.3);
        cellsData->appendCell(5);
    }
    // for (int i = 0; i < 30; i++)
    // {
    //     cellsTableView->setRowHeight(i, 20);
    //     cellsTableView->setColumnWidth(i, 20);
    // }

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

static inline void emulateLeaveEvent(QWidget *widget)
{
    Q_ASSERT(widget);
    if (!widget)
    {
        return;
    }
    QTimer::singleShot(0, widget, [widget]()
    {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        const QScreen *screen = widget->screen();
#else
        const QScreen *screen = widget->windowHandle()->screen();
#endif
        const QPoint globalPos = QCursor::pos(screen);
        if (!QRect(widget->mapToGlobal(QPoint{0, 0}), widget->size()).contains(globalPos))
        {
            QCoreApplication::postEvent(widget, new QEvent(QEvent::Leave));
            if (widget->testAttribute(Qt::WA_Hover))
            {
                const QPoint localPos = widget->mapFromGlobal(globalPos);
                const QPoint scenePos = widget->window()->mapFromGlobal(globalPos);
                static constexpr const auto oldPos = QPoint{};
                const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();
#if (QT_VERSION >= QT_VERSION_CHECK(6, 4, 0))
                const auto event =
                    new QHoverEvent(QEvent::HoverLeave, scenePos, globalPos, oldPos, modifiers);
                Q_UNUSED(localPos);
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 3, 0))
                const auto event =  new QHoverEvent(QEvent::HoverLeave, localPos, globalPos, oldPos, modifiers);
                Q_UNUSED(scenePos);
#else
                const auto event =  new QHoverEvent(QEvent::HoverLeave, localPos, oldPos, modifiers);
                Q_UNUSED(scenePos);
#endif
                QCoreApplication::postEvent(widget, event);
            }
        }
    });
}

bool MainWindow::event(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::WindowActivate:
        {
            auto menu = menuWidget();
            if (menu)
            {
                menu->setProperty("bar-active", true);
                style()->polish(menu);
            }
            break;
        }

        case QEvent::WindowDeactivate:
        {
            auto menu = menuWidget();
            if (menu)
            {
                menu->setProperty("bar-active", false);
                style()->polish(menu);
            }
            break;
        }

        default:
            break;
    }
    return QMainWindow::event(event);
}

void MainWindow::installWindowAgent()
{
    // 1. Setup window agent
    m_widgetWindowAgent = new QWK::WidgetWindowAgent(this);
    m_widgetWindowAgent->setup(this);

    // 2. Construct your title bar
    auto menuBar = [this]()
    {
        auto menuBar = new QMenuBar(this);

        // Virtual menu
        auto file = new QMenu(tr("File(&F)"), menuBar);
        file->addAction(new QAction(tr("New(&N)"), menuBar));
        file->addAction(new QAction(tr("Open(&O)"), menuBar));
        file->addSeparator();

        auto edit = new QMenu(tr("Edit(&E)"), menuBar);
        edit->addAction(new QAction(tr("Undo(&U)"), menuBar));
        edit->addAction(new QAction(tr("Redo(&R)"), menuBar));

#ifdef Q_OS_WIN
        auto noneAction = new QAction(tr("None"), menuBar);
        noneAction->setData(QStringLiteral("none"));
        noneAction->setCheckable(true);
        noneAction->setChecked(true);

        auto dwmBlurAction = new QAction(tr("Enable DWM blur"), menuBar);
        dwmBlurAction->setData(QStringLiteral("dwm-blur"));
        dwmBlurAction->setCheckable(true);

        auto acrylicAction = new QAction(tr("Enable acrylic material"), menuBar);
        acrylicAction->setData(QStringLiteral("acrylic-material"));
        acrylicAction->setCheckable(true);

        auto micaAction = new QAction(tr("Enable mica"), menuBar);
        micaAction->setData(QStringLiteral("mica"));
        micaAction->setCheckable(true);

        auto micaAltAction = new QAction(tr("Enable mica alt"), menuBar);
        micaAltAction->setData(QStringLiteral("mica-alt"));
        micaAltAction->setCheckable(true);

        auto winStyleGroup = new QActionGroup(menuBar);
        winStyleGroup->addAction(noneAction);
        winStyleGroup->addAction(dwmBlurAction);
        winStyleGroup->addAction(acrylicAction);
        winStyleGroup->addAction(micaAction);
        winStyleGroup->addAction(micaAltAction);
        connect(winStyleGroup, &QActionGroup::triggered, this, [this, winStyleGroup](QAction * action)
        {
            // Unset all custom style attributes first, otherwise the style will not display correctly
            for (const QAction * _act : winStyleGroup->actions())
            {
                const QString data = _act->data().toString();
                if (data.isEmpty() || data == QStringLiteral("none"))
                {
                    continue;
                }
                m_widgetWindowAgent->setWindowAttribute(data, false);
            }
            const QString data = action->data().toString();
            if (data == QStringLiteral("none"))
            {
                setProperty("custom-style", false);
            }
            else if (!data.isEmpty())
            {
                m_widgetWindowAgent->setWindowAttribute(data, true);
                setProperty("custom-style", true);
            }
            style()->polish(this);
        });

#elif defined(Q_OS_MAC)
        auto darkBlurAction = new QAction(tr("Dark blur"), menuBar);
        darkBlurAction->setCheckable(true);
        connect(darkBlurAction, &QAction::toggled, this, [this](bool checked)
        {
            if (!windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "dark"))
            {
                return;
            }
            if (checked)
            {
                setProperty("custom-style", true);
                style()->polish(this);
            }
        });

        auto lightBlurAction = new QAction(tr("Light blur"), menuBar);
        lightBlurAction->setCheckable(true);
        connect(lightBlurAction, &QAction::toggled, this, [this](bool checked)
        {
            if (!windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "light"))
            {
                return;
            }
            if (checked)
            {
                setProperty("custom-style", true);
                style()->polish(this);
            }
        });

        auto noBlurAction = new QAction(tr("No blur"), menuBar);
        noBlurAction->setCheckable(true);
        connect(noBlurAction, &QAction::toggled, this, [this](bool checked)
        {
            if (!windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "none"))
            {
                return;
            }
            if (checked)
            {
                setProperty("custom-style", false);
                style()->polish(this);
            }
        });

        auto macStyleGroup = new QActionGroup(menuBar);
        macStyleGroup->addAction(darkBlurAction);
        macStyleGroup->addAction(lightBlurAction);
        macStyleGroup->addAction(noBlurAction);
#endif

        // Real menu
        auto settings = new QMenu(tr("Settings(&S)"), menuBar);
        // settings->addAction(darkAction);

#ifdef Q_OS_WIN
        settings->addSeparator();
        settings->addAction(noneAction);
        settings->addAction(dwmBlurAction);
        settings->addAction(acrylicAction);
        settings->addAction(micaAction);
        settings->addAction(micaAltAction);
#elif defined(Q_OS_MAC)
        settings->addAction(darkBlurAction);
        settings->addAction(lightBlurAction);
        settings->addAction(noBlurAction);
#endif

        menuBar->addMenu(file);
        menuBar->addMenu(edit);
        menuBar->addMenu(settings);
        return menuBar;
    }();
    menuBar->setObjectName(QStringLiteral("win-menu-bar"));

    auto titleLabel = new QLabel("Battery Studio");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName(QStringLiteral("win-title-label"));

#ifndef Q_OS_MAC
    auto iconButton = new QWK::WindowButton();
    iconButton->setObjectName(QStringLiteral("icon-button"));
    iconButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto minButton = new QWK::WindowButton();
    minButton->setObjectName(QStringLiteral("min-button"));
    minButton->setProperty("system-button", true);
    minButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto maxButton = new QWK::WindowButton();
    maxButton->setCheckable(true);
    maxButton->setObjectName(QStringLiteral("max-button"));
    maxButton->setProperty("system-button", true);
    maxButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto closeButton = new QWK::WindowButton();
    closeButton->setObjectName(QStringLiteral("close-button"));
    closeButton->setProperty("system-button", true);
    closeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
#endif

    auto windowBar = new QWK::WindowBar();
#ifndef Q_OS_MAC
    windowBar->setIconButton(iconButton);
    windowBar->setMinButton(minButton);
    windowBar->setMaxButton(maxButton);
    windowBar->setCloseButton(closeButton);
#endif
    windowBar->setMenuBar(menuBar);
    windowBar->setTitleLabel(titleLabel);
    windowBar->setHostWidget(this);

    m_widgetWindowAgent->setTitleBar(windowBar);
#ifndef Q_OS_MAC
    m_widgetWindowAgent->setSystemButton(QWK::WindowAgentBase::WindowIcon, iconButton);
    m_widgetWindowAgent->setSystemButton(QWK::WindowAgentBase::Minimize, minButton);
    m_widgetWindowAgent->setSystemButton(QWK::WindowAgentBase::Maximize, maxButton);
    m_widgetWindowAgent->setSystemButton(QWK::WindowAgentBase::Close, closeButton);
#endif
    m_widgetWindowAgent->setHitTestVisible(menuBar, true);

#ifdef Q_OS_MAC
    windowAgent->setSystemButtonAreaCallback([](const QSize & size)
    {
        static constexpr const int width = 75;
        return QRect(QPoint(size.width() - width, 0), QSize(width, size.height())); //
    });
#endif

    setMenuWidget(windowBar);


#ifndef Q_OS_MAC
    connect(windowBar, &QWK::WindowBar::minimizeRequested, this, &QWidget::showMinimized);
    connect(windowBar, &QWK::WindowBar::maximizeRequested, this, [this, maxButton](bool max)
    {
        if (max)
        {
            showMaximized();
        }
        else
        {
            showNormal();
        }

        // It's a Qt issue that if a QAbstractButton::clicked triggers a window's maximization,
        // the button remains to be hovered until the mouse move. As a result, we need to
        // manually send leave events to the button.
        emulateLeaveEvent(maxButton);
    });
    connect(windowBar, &QWK::WindowBar::closeRequested, this, &QWidget::close);
#endif
}

void MainWindow::setTitleBarStyleSheet()
{
    if (QFile qss(QStringLiteral(":/TitleBar.qss"));
        qss.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        setStyleSheet(QString::fromUtf8(qss.readAll()));
    }
}
