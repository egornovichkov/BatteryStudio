#include "batterychargeicon.h"
#include <QPainter>

BatteryChargeIcon::BatteryChargeIcon(QWidget *parent)
    : QWidget{parent}
{
}


void BatteryChargeIcon::paintEvent(QPaintEvent *event)
{

    QSize itemSize = this->size();
    const int margin = 4;//The margin of the outer frame
    int w = itemSize.width();
    int h = itemSize.height();

    int x0, y0, w0, h0;//Outer frame data
    int x1, y1, w1, h1;//Inner frame data-battery
    int x2, y2, w2, h2;//Inner frame data-battery head

    //Outer frame
    x0 = 1; y0 = x0;
    w0 = w - 2 * x0 - margin;
    h0 = h - 2 * y0;

    //Inner box filling
    x1 = 5; y1 = x1;
    w1 = w - 2 * x1 - 4;
    h1 = h - 2 * y1;

    //Battery small head
    x2 = x0 + w0 ;
    y2 = h / 3;
    w2 = margin;
    h2 = h / 3;

    QPainter painter(this);
    QPen pen;

    painter.setPen(m_frame_color);//The color of the frame
    pen = painter.pen();
    pen.setWidth(1);//Set the width of the wireframe
    painter.setPen(pen);
    painter.setBrush(m_background_color);

    //Draw the outline rectangle and background
    painter.drawRoundedRect(x0, y0, w0, h0, 3, 3);

    //Draw the the small head of the battery
    painter.drawRoundedRect(x2, y2, w2, h2, 2, 2);

    // Draw inner rectangle
    painter.setPen(m_charge_color);
    painter.setBrush(m_charge_color);
    int w1_current = m_value*0.01*(w1);
    //Set the power according to the value
    painter.drawRoundedRect(x1, y1, w1_current, h1, 2, 2);

    painter.setPen(QColor(0, 0, 0));//The color of the frame

    switch (m_showTextFlg)
    {
    case 0://0:Show default text
        painter.drawText(x0, y0, w0, h0,
                         Qt::AlignHCenter | Qt::AlignVCenter,
                         m_showText);
        break;
    case 1://1:Show percentage and caption
        painter.drawText(x0, y0, w0, h0,
                         Qt::AlignHCenter | Qt::AlignVCenter,
                         QString::asprintf("%d%%", m_value));
        break;
    }

    QWidget::paintEvent(event);
}
