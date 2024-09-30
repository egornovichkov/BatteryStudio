#include "titlebar.h"
#include <QMenu>
#include "qpainter.h"
#include "ui_titlebar.h"
#include <QMouseEvent>
#include <iostream>


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
    // setAttribute(Qt::WA_TranslucentBackground);

    mIsCollapse = false;

    /// CHANGE

    connect(ui->close, SIGNAL(clicked(bool)), this, SLOT(onCloseClicked()));
    connect(ui->maximum, SIGNAL(clicked(bool)), this,  SLOT(onMaximumClicked()));
    connect(ui->minimum, SIGNAL(clicked(bool)), this,  SLOT(onMinimumClicked()));
}

/// @brief Destructor for the WindowFrame class.
TitleBar::~TitleBar()
{
    delete ui;
}


/// @brief Init frame icons.
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

// QPoint TitleBar::previousPosition() const
// {
//     return mPosition;
// }

// void TitleBar::setPreviousPosition(QPoint previousPosition)
// {
//     if (mPosition == previousPosition)
//         return;

//     mPosition = previousPosition;
//     emit previousPositionChanged(previousPosition);
// }

// void TitleBar::mousePressEvent(QMouseEvent *event)
// {
//     // При клике левой кнопкой мыши
//     if (event->button() == Qt::LeftButton)
//     {
//         // Определяем, в какой области произошёл клик
//         m_leftMouseButtonPressed = checkResizableField(event);
//         setPreviousPosition(event->pos()); // и устанавливаем позицию клика
//     }
//     return QWidget::mousePressEvent(event);
// }

// void TitleBar::mouseReleaseEvent(QMouseEvent *event)
// {
//     if (event->button() == Qt::LeftButton)
//     {
//         // При отпускании левой кнопки мыши сбрасываем состояние клика
//         m_leftMouseButtonPressed = MouseType::None;
//         setPreviousPosition(event->pos());
//         return QWidget::mouseReleaseEvent(event);
//     }
// }

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
            // if (isMaximized())
            // {
            //     ui->maximum->setIcon(QIcon(maximizeIcon));
            //     ui->header->setStyleSheet(headerDefaultStyle);
            //     showNormal();
            // }
            // else
            // {
            //     ui->maximum->setIcon(QIcon(defaultSizeIcon));
            //     ui->header->setStyleSheet(headerMaximizeStyle);
            //     showMaximized();
            // }
        }
    }
}

void TitleBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(ui->body->x(), ui->body->y(), ui->body->width(), ui->body->height());
    painter.drawRect(x(), y(), width(), height());
}

// /// @brief Handler for the mouse move event within the window.
// /// @param event Pointer to the mouse move event object (QMouseEvent).
// /// @return No return value.
// void TitleBar::mouseMoveEvent(QMouseEvent *event)
// {
//     std::cout << "MOVE";
//     // При перемещении мыши, проверяем статус нажатия левой кнопки мыши
//     switch (m_leftMouseButtonPressed)
//     {
//         case MouseType::Move:
//         {
//             if (!isMaximized())
//             {
//                 // Если окно не максимизировано, то просто перемещаем его относительно
//                 // последней запомненной позиции, пока не отпустим кнопку мыши
//                 auto dx = event->position().x() - mPosition.x();
//                 auto dy = event->position().y() - mPosition.y();
//                 setGeometry(x() + dx, y() + dy, width(), height());
//             }
//             break;
//         }
//         case MouseType::Top:
//         {
//             // Для изменения размеров также проверяем на максимизацию
//             // поскольку мы же не можем изменить размеры у максимизированного окна
//             if (!isMaximized())
//             {
//                 auto dy = event->position().y() - mPosition.y();
//                 setGeometry(x(), y() + dy, width(), height() - dy);
//             }
//             break;
//         }
//         case MouseType::Bottom:
//         {
//             if (!isMaximized())
//             {
//                 auto dy = event->position().y() - mPosition.y();
//                 setGeometry(x(), y(), width(), height() + dy);
//                 setPreviousPosition(event->pos());
//             }
//             break;
//         }
//         case MouseType::Left:
//         {
//             if (!isMaximized())
//             {
//                 auto dx = event->position().x() - mPosition.x();
//                 setGeometry(x() + dx, y(), width() - dx, height());
//             }
//             break;
//         }
//         case MouseType::Right:
//         {
//             if (!isMaximized())
//             {
//                 auto dx = event->position().x() - mPosition.x();
//                 setGeometry(x(), y(), width() + dx, height());
//                 setPreviousPosition(event->pos());
//             }
//             break;
//         }
//         default:
//             // Если курсор перемещается по окну без зажатой кнопки,
//             // то просто отслеживаем в какой области он находится
//             // и изменяем его курсор
//             checkResizableField(event);
//             break;
//     }

//     return QWidget::mouseMoveEvent(event);
// }

// TitleBar::MouseType TitleBar::checkResizableField(QMouseEvent *event)
// {
//     QPointF position = event->globalPosition();
//     qreal x = this->x();
//     qreal y = this->y();
//     qreal width = this->width();
//     qreal height = this->height();
//     qreal headerheight = ui->header->height();

//     qreal fieldSize = 5;

//     qreal borderRad = 5; // MUST BE CHANGED!

//     // Определяем области, в которых может находиться курсор мыши
//     // По ним будет определён статус клика
//     QRectF rectTop(x + borderRad, y, width - 2 * borderRad, fieldSize);
//     QRectF rectBottom(x + borderRad, y + height - fieldSize, width - 2 * borderRad, fieldSize);
//     QRectF rectLeft(x, y + borderRad, fieldSize, height - 2 * borderRad);
//     QRectF rectRight(x + width - fieldSize, y + borderRad, fieldSize, height - 2 * borderRad);
//     QRectF rectHeader(x, y, width, headerheight);

//     // И в зависимости от области, в которой находится курсор
//     // устанавливаем внешний вид курсора и возвращаем его статус
//     if (rectTop.contains(position))
//     {
//         setCursor(Qt::SizeVerCursor);
//         return MouseType::Top;
//     }
//     else if (rectBottom.contains(position))
//     {
//         setCursor(Qt::SizeVerCursor);
//         return MouseType::Bottom;
//     }
//     else if (rectLeft.contains(position))
//     {
//         setCursor(Qt::SizeHorCursor);
//         return MouseType::Left;
//     }
//     else if (rectRight.contains(position))
//     {
//         setCursor(Qt::SizeHorCursor);
//         return MouseType::Right;
//     }
//     else if (rectHeader.contains(position))
//     {
//         setCursor(QCursor(Qt::ArrowCursor));
//         return MouseType::Move;
//     }
//     else
//     {
//         setCursor(QCursor(Qt::ArrowCursor));
//         std::cout << "None";
//         return MouseType::None;
//     }
// }


/// @brief Show or hide the window minimization button.
/// @param enable If true, the button will be shown; if false, it will be hidden.
void TitleBar::enableMinimum(bool enable)
{
    !enable ? ui->minimum->hide() : ui->minimum->show();
}

/// @brief Show or hide the window maximization button.
/// @param enable If true, the button will be shown; if false, it will be hidden.
void TitleBar::enableMaximum(bool enable)
{
    !enable ? ui->maximum->hide() : ui->maximum->show();
}

/// @brief Show or hide the window close button.
/// @param enable If true, the button will be shown; if false, it will be hidden.
void TitleBar::enableClose(bool enable)
{
    !enable ? ui->close->hide() : ui->close->show();
}

// /// @brief Override event filtering function for the WindowFrame class.
// /// @param obj Pointer to the object for which the event was generated.
// /// @param event Pointer to the QEvent object representing the event.
// /// @return `true` if the event was handled, otherwise `false`.
// bool TitleBar::eventFilter(QObject *obj, QEvent *event)
// {
//     if (obj == mMainBody)
//     {
//         if (event->type() == QEvent::HideToParent)
//         {
//             hide();
//             return true;
//         }
//         if (event->type() == QEvent::ShowToParent)
//         {
//             show();
//             return true;
//         }
//         return QObject::eventFilter(obj, event);
//     }
//     else
//     {
//         return QFrame::eventFilter(obj, event);
//     }
//     return false;
// }
