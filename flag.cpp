#include "flag.h"
#include <QLayout>
#include <QPainter>
#include <iostream>

Flag::Flag(QWidget *parent)
    : QWidget{parent}
{}

Flag::Flag(QString label, bool mode, QWidget *parent)
    : QWidget{parent}, m_label(label, parent), m_led(parent, mode), m_mode(mode)
{
    // m_label.setFixedSize(parent->width(), parent->height());

    // Setting label coordinates
    int x = (3 * m_led.getSize())/2 + 3;
    m_label.setMargin(x);
    std::cout << this->width() << " " << this->height() << " " << m_label.width() << " " << m_label.height() << "\n";
}

void Flag::switchFlag()
{
    m_led.switchLed();
}

void Flag::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
}



// QSize Flag::sizeHint() const {
//     int w = m_label.width();
//     int h = m_label.height();
//     return QSize(w, h);
// }
