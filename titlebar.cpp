#include "titlebar.h"
#include <QMenu>
#include <QMouseEvent>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>
#include <QtWidgets/QPushButton>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#  include <QtGui/QActionGroup>
#else
#  include <QtWidgets/QActionGroup>
#endif

#include <QWKWidgets/widgetwindowagent.h>

#include <WidgetFrame/src/windowbar.h>
#include <WidgetFrame/src/windowbutton.h>
#include "MainWindow/mainwindow.h"

static inline void emulateLeaveEvent(QWidget *widget) {
    Q_ASSERT(widget);
    if (!widget) {
        return;
    }
    QTimer::singleShot(0, widget, [widget]() {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        const QScreen *screen = widget->screen();
#else
        const QScreen *screen = widget->windowHandle()->screen();
#endif
        const QPoint globalPos = QCursor::pos(screen);
        if (!QRect(widget->mapToGlobal(QPoint{0, 0}), widget->size()).contains(globalPos)) {
            QCoreApplication::postEvent(widget, new QEvent(QEvent::Leave));
            if (widget->testAttribute(Qt::WA_Hover)) {
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

TitleBar::TitleBar(MainWindow *parent)
    : QWidget(parent)/*, ui(new Ui::TitleBar)*/
{
    // ui->setupUi(this);

    // mBorderSize = 5;

    // initIcons();

    // ui->title->setText(title);

    // setWindowFlags(Qt::FramelessWindowHint);

    // mIsCollapse = false;
    // m_MaximizedFlag = true;

    // connect(ui->close, SIGNAL(clicked(bool)), this, SLOT(onCloseClicked()));
    // connect(ui->maximum, SIGNAL(clicked(bool)), this,  SLOT(onMaximumClicked()));
    // connect(ui->minimum, SIGNAL(clicked(bool)), this,  SLOT(onMinimumClicked()));


    ////
    ///
    ///
    ///

    m_mainWindow = parent;

    // 2. Construct your title bar
    auto menuBar = [this]() {
        auto menuBar = new QMenuBar(this);

        // Virtual menu
        auto file = new QMenu(tr("File(&F)"), menuBar);
        file->addAction(new QAction(tr("New(&N)"), menuBar));
        file->addAction(new QAction(tr("Open(&O)"), menuBar));
        file->addSeparator();

        auto edit = new QMenu(tr("Edit(&E)"), menuBar);
        edit->addAction(new QAction(tr("Undo(&U)"), menuBar));
        edit->addAction(new QAction(tr("Redo(&R)"), menuBar));

        // Theme action
        // auto darkAction = new QAction(tr("Enable dark theme"), menuBar);
        // darkAction->setCheckable(true);
        // connect(darkAction, &QAction::triggered, this, [this](bool checked) {
        //     loadStyleSheet(checked ? Dark : Light); //
        // });
        // connect(this, &MainWindow::themeChanged, darkAction, [this, darkAction]() {
        //     darkAction->setChecked(currentTheme == Dark); //
        // });

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
        connect(winStyleGroup, &QActionGroup::triggered, this, [this, winStyleGroup](QAction *action) {
            // Unset all custom style attributes first, otherwise the style will not display correctly
            for (const QAction* _act : winStyleGroup->actions()) {
                const QString data = _act->data().toString();
                if (data.isEmpty() || data == QStringLiteral("none")) {
                    continue;
                }
                m_mainWindow->windowAgent()->setWindowAttribute(data, false);
            }
            const QString data = action->data().toString();
            if (data == QStringLiteral("none")) {
                setProperty("custom-style", false);
            } else if (!data.isEmpty()) {
                m_mainWindow->windowAgent()->setWindowAttribute(data, true);
                setProperty("custom-style", true);
            }
            style()->polish(this);
        });

#elif defined(Q_OS_MAC)
        auto darkBlurAction = new QAction(tr("Dark blur"), menuBar);
        darkBlurAction->setCheckable(true);
        connect(darkBlurAction, &QAction::toggled, this, [this](bool checked) {
            if (!m_mainWindow->windowAgent()->setWindowAttribute(QStringLiteral("blur-effect"), "dark")) {
                return;
            }
            if (checked) {
                setProperty("custom-style", true);
                style()->polish(this);
            }
        });

        auto lightBlurAction = new QAction(tr("Light blur"), menuBar);
        lightBlurAction->setCheckable(true);
        connect(lightBlurAction, &QAction::toggled, this, [this](bool checked) {
            if (!m_mainWindow->windowAgent()->setWindowAttribute(QStringLiteral("blur-effect"), "light")) {
                return;
            }
            if (checked) {
                setProperty("custom-style", true);
                style()->polish(this);
            }
        });

        auto noBlurAction = new QAction(tr("No blur"), menuBar);
        noBlurAction->setCheckable(true);
        connect(noBlurAction, &QAction::toggled, this, [this](bool checked) {
            if (!m_mainWindow->windowAgent()->setWindowAttribute(QStringLiteral("blur-effect"), "none")) {
                return;
            }
            if (checked) {
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

    auto titleLabel = new QLabel();
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

    m_mainWindow->windowAgent()->setTitleBar(windowBar);
#ifndef Q_OS_MAC
    m_mainWindow->windowAgent()->setSystemButton(QWK::WindowAgentBase::WindowIcon, iconButton);
    m_mainWindow->windowAgent()->setSystemButton(QWK::WindowAgentBase::Minimize, minButton);
    m_mainWindow->windowAgent()->setSystemButton(QWK::WindowAgentBase::Maximize, maxButton);
    m_mainWindow->windowAgent()->setSystemButton(QWK::WindowAgentBase::Close, closeButton);
#endif
    m_mainWindow->windowAgent()->setHitTestVisible(menuBar, true);

#ifdef Q_OS_MAC
    windowAgent->setSystemButtonAreaCallback([](const QSize &size) {
        static constexpr const int width = 75;
        return QRect(QPoint(size.width() - width, 0), QSize(width, size.height())); //
    });
#endif

    m_mainWindow->setMenuWidget(windowBar);


#ifndef Q_OS_MAC
    connect(windowBar, &QWK::WindowBar::minimizeRequested, m_mainWindow, &QWidget::showMinimized);
    connect(windowBar, &QWK::WindowBar::maximizeRequested, m_mainWindow, [this, maxButton](bool max) {
        if (max) {
            m_mainWindow->showMaximized();
        } else {
            m_mainWindow->showNormal();
        }

        // It's a Qt issue that if a QAbstractButton::clicked triggers a window's maximization,
        // the button remains to be hovered until the mouse move. As a result, we need to
        // manually send leave events to the button.
        emulateLeaveEvent(maxButton);
    });
    connect(windowBar, &QWK::WindowBar::closeRequested, this, &QWidget::close);
#endif
}


// /// @brief Destructor for the WindowFrame class.
// TitleBar::~TitleBar()
// {
//     delete ui;
// }


// /// @brief Function for initialization frame icons.
// void TitleBar::initIcons()
// {
//     QPixmap pixmap(appIcon);
//     ui->icon->setPixmap(pixmap);
//     ui->icon->setScaledContents(true);
//     ui->icon->setAlignment(Qt::AlignCenter);
//     ui->icon->resize(24, 24);

//     ui->close->setIcon(QIcon(closeIcon));
//     ui->maximum->setIcon(QIcon(defaultSizeIcon));
//     ui->minimum->setIcon(QIcon(minimizeIcon));
// }

// /// @brief Show header menu.
// /// @param pos position mouse click.
// void TitleBar::showHeaderContextMenu(const QPoint &pos)
// {
//     QMenu contextMenu(this);

//     QAction *exitAction = contextMenu.addAction(tr("&Exit"));
//     connect(exitAction, &QAction::triggered, this, &TitleBar::close);

//     contextMenu.addAction(exitAction);
//     contextMenu.exec(mapToGlobal(pos));
// }


// /// @brief Handler for the "Close" button click signal.
// void TitleBar::onCloseClicked()
// {
//     emit onCloseClickedSignal();
// }

// /// @brief Handler for the "Maximize/Restore" button click signal.
// void TitleBar::onMaximumClicked()
// {
//     m_MaximizedFlag = !m_MaximizedFlag;
//     emit onMaximumClickedSignal();

//     if (m_MaximizedFlag)
//     {
//         ui->maximum->setIcon(QIcon(defaultSizeIcon));
//         ui->header->setStyleSheet(headerMaximizeStyle);
//     }
//     else
//     {
//         ui->maximum->setIcon(QIcon(maximizeIcon));
//         mIsCollapse ? ui->header->setStyleSheet(headerCollapseStyle) : ui->header->setStyleSheet(headerDefaultStyle);
//     }
// }

/// @brief Handler for the "Minimize" button click signal.
// void TitleBar::onMinimumClicked()
// {
//     emit onMinimumClickedSignal();
// }

/// @brief Handler for the mouse double-click event within the window.
/// @param event Pointer to the mouse double-click event object (QMouseEvent).
// void TitleBar::mouseDoubleClickEvent(QMouseEvent * event)
// {
//     if (event->buttons() == Qt::LeftButton)
//     {
//         QWidget* widget = childAt(event->pos().x(), event->pos().y());
//         if (widget == ui->LHeader)
//         {
//             emit onMaximumClickedSignal();
//         }
//     }
// }
