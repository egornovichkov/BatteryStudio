#include "appwidget.h"
#include <QBoxLayout>
#include "mainwindow.h"
#include "qevent.h"
#include "titlebar.h"
#include <QMainWindow>
#include <QWidget>
#include <iostream>

AppWidget::AppWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowFullScreen);
    setMouseTracking(true);

    m_mainWindow = new MainWindow();
    m_titleBar = new TitleBar();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_titleBar);
    layout->addWidget(m_mainWindow);

    connect(m_titleBar, SIGNAL(onCloseClickedSignal()), this, SLOT(closeApp()));
    connect(m_titleBar, SIGNAL(onMaximumClickedSignal()), this,  SLOT(maximizeApp()));
    connect(m_titleBar, SIGNAL(onMinimumClickedSignal()), this,  SLOT(minimizeApp()));
}

AppWidget::~AppWidget()
{}

/// @brief Handler for the "Close" button click signal.
void AppWidget::closeApp()
{
    close();
}

/// @brief Handler for the "Maximize/Restore" button click signal.
void AppWidget::maximizeApp()
{
    if (isMaximized())
    {
        showNormal();
    }
    else
    {
        showMaximized();
    }
}

/// @brief Handler for the "Minimize" button click signal.
void AppWidget::minimizeApp()
{
    showMinimized();
}

/// @brief Getter for previous mouse position within the window.
QPoint AppWidget::previousPosition() const
{
    return m_Position;
}

/// @brief Setter for previous mouse position within the window.
void AppWidget::setPreviousPosition(QPoint previousPosition)
{
    if (m_Position == previousPosition)
        return;

    m_Position = previousPosition;
    emit previousPositionChanged(previousPosition);
}

/// @brief Handler for mouse press event.
void AppWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtonPressed = checkResizableField(event);
        setPreviousPosition(event->pos());
    }
    return QWidget::mousePressEvent(event);
}

/// @brief Handler for mouse press event.
void AppWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtonPressed = MouseType::None;
        setPreviousPosition(event->pos());
        return QWidget::mouseReleaseEvent(event);
    }
}

/// @brief Handler for the mouse move event.
void AppWidget::mouseMoveEvent(QMouseEvent *event)
{
    switch (m_leftMouseButtonPressed)
    {
        case MouseType::Move:
        {
            if (!isMaximized())
            {
                auto dx = event->position().x() - m_Position.x();
                auto dy = event->position().y() - m_Position.y();
                setGeometry(x() + dx, y() + dy, width(), height());
            }
            break;
        }
        case MouseType::Top:
        {
            if (!isMaximized())
            {
                auto dy = event->position().y() - m_Position.y();
                setGeometry(x(), y() + dy, width(), height() - dy);
            }
            break;
        }
        case MouseType::Bottom:
        {
            if (!isMaximized())
            {
                auto dy = event->position().y() - m_Position.y();
                setGeometry(x(), y(), width(), height() + dy);
                setPreviousPosition(event->pos());
            }
            break;
        }
        case MouseType::Left:
        {
            if (!isMaximized())
            {
                auto dx = event->position().x() - m_Position.x();
                setGeometry(x() + dx, y(), width() - dx, height());
            }
            break;
        }
        case MouseType::Right:
        {
            if (!isMaximized())
            {
                auto dx = event->position().x() - m_Position.x();
                setGeometry(x(), y(), width() + dx, height());
                setPreviousPosition(event->pos());
            }
            break;
        }
        default:
            checkResizableField(event);
            break;
    }

    return QWidget::mouseMoveEvent(event);
}

/// @brief Function which returns mouse type due to its position within the window.
AppWidget::MouseType AppWidget::checkResizableField(QMouseEvent *event)
{
    QPointF position = event->globalPosition();
    qreal x = this->x();
    qreal y = this->y();
    qreal width = this->width();
    qreal height = this->height();
    qreal headerheight = m_titleBar->height();

    qreal fieldSize = 5;

    qreal borderRad = 5; // MUST BE CHANGED!

    QRectF rectTop(x + borderRad, y, width - 2 * borderRad, fieldSize);
    QRectF rectBottom(x + borderRad, y + height - fieldSize, width - 2 * borderRad, fieldSize);
    QRectF rectLeft(x, y + borderRad, fieldSize, height - 2 * borderRad);
    QRectF rectRight(x + width - fieldSize, y + borderRad, fieldSize, height - 2 * borderRad);
    QRectF rectHeader(x, y, width, headerheight);

    if (rectTop.contains(position))
    {
        setCursor(Qt::SizeVerCursor);
        return MouseType::Top;
    }
    else if (rectBottom.contains(position))
    {
        setCursor(Qt::SizeVerCursor);
        return MouseType::Bottom;
    }
    else if (rectLeft.contains(position))
    {
        setCursor(Qt::SizeHorCursor);
        return MouseType::Left;
    }
    else if (rectRight.contains(position))
    {
        setCursor(Qt::SizeHorCursor);
        return MouseType::Right;
    }
    else if (rectHeader.contains(position))
    {
        setCursor(QCursor(Qt::ArrowCursor));
        return MouseType::Move;
    }
    else
    {
        setCursor(QCursor(Qt::ArrowCursor));
        std::cout << "None";
        return MouseType::None;
    }
}
