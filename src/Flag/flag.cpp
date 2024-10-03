#include "flag.h"
#include "ledimg.h"
#include <QLabel>
#include <QPainter>

Flag::Flag(QWidget *parent)
    : QWidget{parent}
{}

Flag::Flag(QString label, bool mode, QWidget *parent)
    : QWidget{parent}
{

    m_label = new QLabel(label, this);
    m_led = new LedImg(12, mode, this);
    m_mode = mode;

    // Managing label size and pos
    m_label->setStyleSheet(QString::fromUtf8("QLabel { \n"
        "color: rgb(50, 50, 65);\n"
        "border: 0px;\n"
        "background-color: transparent;\n"
        "font: 9pt \"Segoe UI\";\n"
        "}"));
    int x = (3 * m_led->getSize()) / 2 + 4; // 4 is margin from led
    m_label->setContentsMargins(x, 0, 0, 0);
    QFontMetrics fm(m_label->font());
    int w = fm.boundingRect(m_label->text()).width();
    m_label->setGeometry(0, 0, this->width(), this->height());
    int minWidth = 3 * m_led->getSize() + w;
    this->setMinimumWidth(minWidth);
}

/// @brief Handler for flag mode switch.
void Flag::switchFlag()
{
    m_led->switchLed();
}
