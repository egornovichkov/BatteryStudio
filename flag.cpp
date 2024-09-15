#include "flag.h"
#include <QLayout>
#include <QPainter>

Flag::Flag(QWidget *parent)
    : QWidget{parent}
{}

Flag::Flag(QString label, bool mode, QWidget *parent)
    : QWidget{parent}, m_label(label, parent), m_led(parent, mode), m_mode(mode)
{
    // Setting label coordinates
    int x = (3 * m_led.getSize())/2 + 3;
    m_label.setMargin(x);
}

void Flag::switchFlag()
{
    m_led.switchLed();
}
