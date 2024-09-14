#include "flag.h"
#include <QPainter>

Flag::Flag(QWidget *parent)
    : QWidget{parent}
{}

Flag::Flag(QString label, bool mode, QWidget *parent)
    : QWidget{parent}, m_label(label), m_led(parent, mode), m_mode(mode)
{}

void Flag::switchFlag()
{
    m_led.switchLed();
}
