#include "flag.h"
#include <QLabel>
#include "ledimg.h"
#include <QPainter>

Flag::Flag(QWidget *parent)
    : QWidget{parent}
{}

Flag::Flag(QString label, bool mode, QWidget *parent)
    : QWidget{parent}
{
    this->setMinimumWidth(70);
    m_label = new QLabel(label, this);
    m_led = new LedImg(11, mode, this);
    m_mode = mode;

    // Setting label coordinates
    int x = (3 * m_led->getSize())/2 + 4;
    m_label->setContentsMargins(x, 0, 0, 0);
    m_label->setGeometry(0, 0, this->width(), this->height());
    m_label->setStyleSheet(QString::fromUtf8("QLabel { \n"
        "color: rgb(25, 25, 25);\n"
        "border: 0px;\n"
        "background-color: transparent;\n"
        "font: 9pt \"Inter\";\n"
    "}"));
}

void Flag::switchFlag()
{
    m_led->switchLed();
}
