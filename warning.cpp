#include "warning.h"
#include "qpainter.h"
#include <QLabel>


Warning::Warning(QString label, QString type, QWidget *parent)
    : QWidget{parent}
{
    m_type = type;
    m_backgroundColor = warningTypeMap[type];
    m_group = warningGroupMap[type];

    m_label = new QLabel(label, this);
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setStyleSheet(QString::fromUtf8("QLabel { \n"
                                             "color: rgb(25, 25, 25);\n"
                                             "border: 0px;\n"
                                             "background-color: transparent;\n"
                                             "font: 8pt \"Inter\";\n"
                                             "}"));
}

void Warning::paintEvent(QPaintEvent *)
{
    // Getting cords for painting warnings
    int x, y, w, h;
    if (this->width() > m_maximumWidth)
    {
        x = (this->width() / 2) - (m_maximumWidth / 2) + 2;
        y = 2;
        w = m_maximumWidth - 4;
        h = 24;
    } else {
        x = 2;
        y = 2;
        w = this->width() - 4;
        h = 24;
    }

    m_label->setGeometry(x, y, w, h);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(m_backgroundColor);
    painter.setPen(m_borderColor);
    painter.drawRoundedRect(x, y, w, h, 3, 3);
}
