#include "ledimg.h"
#include <QPainter>

LedImg::LedImg(int size, bool mode, QWidget *parent)
    : QWidget{parent}, m_mode(mode), m_size(size) {}

/// @brief paintEvent override for LED image.
void LedImg::paintEvent(QPaintEvent*)
{

    // Led positioned on parent
    int h = this->height();
    int x = m_size / 2;
    int y = h / 2 - m_size / 2;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 0: inactive mode, 1: active mode
    m_mode ? painter.setBrush(m_activeColor) : painter.setBrush(m_inactiveColor);
    painter.setPen(m_borderColor);
    painter.drawEllipse(x, y, m_size, m_size);
}

/// @brief Setter for LED diameter.
void LedImg::setSize(int size)
{
    m_size = size;
    update();
}

/// @brief Getter for LED diameter.
int LedImg::getSize()
{
    return m_size;
}

/// @brief Handler for LED mode switch.
void LedImg::switchLed()
{
    m_mode = !m_mode;
    update();
}
