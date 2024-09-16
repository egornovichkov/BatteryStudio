#include "warning.h"
#include "qpainter.h"
#include <QLabel>


Warning::Warning(QString label, QString type, QWidget *parent)
    : QWidget{parent}
{
    m_type = type;
    m_backgroundColor = warningTypeMap[type];

    m_label = new QLabel(label, this);
    m_label->setGeometry(0, 0, this->width(), this->height());
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setStyleSheet(QString::fromUtf8("QLabel { \n"
                                             "color: rgb(25, 25, 25);\n"
                                             "border: 0px;\n"
                                             "background-color: transparent;\n"
                                             "font: 8pt \"Roboto\";\n"
                                             "}"));
}

void Warning::paintEvent(QPaintEvent *)
{
    // Getting cords for margins
    int x, y, w, h;
    x = this->x() + 2;
    y = this->y() + 2;
    w = this->width() - 4;
    h = this->height() - 4;

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(m_backgroundColor);
    painter.setPen(m_borderColor);
    painter.drawRoundedRect(x, y, w, h, 5, 5);
}
