#include "titlebar.h"
#include <QMenu>
#include "qpainter.h"
#include "ui_titlebar.h"
#include <QMouseEvent>

QString title = "Custom Title Bar";

QString headerDefaultStyle = QStringLiteral(
    "#header {"
    "    background-color: rgb(244, 244, 249);"
    "    border: 0px;"
    "    border-top-left-radius: 10px;"
    "    border-top-right-radius: 10px;"
    "}"
    );

QString headerCollapseStyle = QStringLiteral(
    "#header {"
    "    background-color: rgb(244, 244, 249);"
    "    border: 0px;"
    "    border-top-left-radius: 10px;"
    "    border-top-right-radius: 10px;"
    "    border-bottom-left-radius: 10px;"
    "    border-bottom-right-radius: 10px;"
    "}"
    );

QString headerMaximizeStyle = QStringLiteral(
    "#header {"
    "    background-color: rgb(244, 244, 249);"
    "    border: 0px;"
    "    border-top-left-radius: 0px;"
    "    border-top-right-radius: 0px;"
    "}"
    );

QString appIcon           = ":/images/BatteryIcon.png";
QString closeIcon         = ":/images/CloseIcon.png";
QString maximizeIcon      = ":/images/maximizeicon.png";
QString minimizeIcon      = ":/images/minimizeicon.png";
QString defaultSizeIcon   = ":/images/defaultsizeicon.png";


TitleBar::TitleBar(QWidget *parent)
    : QFrame(parent), ui(new Ui::TitleBar)
{

    ui->setupUi(this);

    mBorderSize = 5;

    initIcons();

    ui->title->setText(title);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    mIsCollapse = false;

    connect(ui->close, SIGNAL(clicked(bool)), this, SLOT(onCloseClicked()));
    connect(ui->maximum, SIGNAL(clicked(bool)), this,  SLOT(onMaximumClicked()));
    connect(ui->minimum, SIGNAL(clicked(bool)), this,  SLOT(onMinimumClicked()));
}

/// @brief Destructor for the WindowFrame class.
TitleBar::~TitleBar()
{
    delete ui;
}


/// @brief Function for initialization frame icons.
void TitleBar::initIcons()
{
    QPixmap pixmap(appIcon);
    ui->icon->setPixmap(pixmap);
    ui->icon->setScaledContents(true);
    ui->icon->setAlignment(Qt::AlignCenter);
    ui->icon->resize(24, 24);

    ui->close->setIcon(QIcon(closeIcon));
    ui->maximum->setIcon(QIcon(maximizeIcon));
    ui->minimum->setIcon(QIcon(minimizeIcon));
}

/// @brief Show header menu.
/// @param pos position mouse click.
void TitleBar::showHeaderContextMenu(const QPoint &pos)
{
    QMenu contextMenu(this);

    QAction *exitAction = contextMenu.addAction(tr("&Exit"));
    connect(exitAction, &QAction::triggered, this, &TitleBar::close);

    contextMenu.addAction(exitAction);
    contextMenu.exec(mapToGlobal(pos));
}


/// @brief Handler for the "Close" button click signal.
void TitleBar::onCloseClicked()
{
    emit onCloseClickedSignal();
}

/// @brief Handler for the "Maximize/Restore" button click signal.
void TitleBar::onMaximumClicked()
{
    emit onMaximumClickedSignal();

    if (isMaximized())
    {
        ui->maximum->setIcon(QIcon(maximizeIcon));
        mIsCollapse ? ui->header->setStyleSheet(headerCollapseStyle) : ui->header->setStyleSheet(headerDefaultStyle);
    }
    else
    {
        ui->maximum->setIcon(QIcon(defaultSizeIcon));
        ui->header->setStyleSheet(headerMaximizeStyle);
    }
}

/// @brief Handler for the "Minimize" button click signal.
void TitleBar::onMinimumClicked()
{
    emit onMinimumClickedSignal();
}

/// @brief Handler for the mouse double-click event within the window.
/// @param event Pointer to the mouse double-click event object (QMouseEvent).
void TitleBar::mouseDoubleClickEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        QWidget* widget = childAt(event->pos().x(), event->pos().y());
        if (widget == ui->LHeader)
        {
            emit onMaximumClickedSignal();
        }
    }
}

/// @brief paintEvent override for title bar.
void TitleBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(ui->body->x(), ui->body->y(), ui->body->width(), ui->body->height());
    painter.drawRect(x(), y(), width(), height());
}
