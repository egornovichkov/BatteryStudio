#include "warninggroup.h"
#include "warning.h"
#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

WarningGroup::WarningGroup(QString group, QWidget *parent) : QWidget{parent}
{
    m_label = new QLabel(group, this);
    m_group = warningGroupMap[group];

    // Creating Layout
    m_WarningGroupLayout = new QVBoxLayout(this);
    m_WarningGroupLayout->setContentsMargins(10, 12, 10, 10);
    m_WarningGroupLayout->setSpacing(0);
    QSpacerItem *spacer = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Expanding);
    m_WarningGroupLayout->addSpacerItem(spacer);
}

void WarningGroup::paintEvent(QPaintEvent*)
{
    // Drawing frame
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(m_color);
    int x, y, w, h;
    x = 5;
    y = 5;
    w = this->width() - 2 * x;
    h = this->height() - 2 * y;
    painter.drawRoundedRect(x, y, w, h, 2, 2);

    // Managing caption style, size and pos
    m_label->setStyleSheet(
        QString::fromUtf8("QLabel { \n"
        "color: rgb(150, 150, 160);\n"
        "border: 0px;\n"
        "background-color: rgb(244, 244, 244);\n"
        "font: 7pt \"Inter\";\n"
        "}"));
    QFontMetrics fm(m_label->font());
    QRect rect = fm.boundingRect(m_label->text());
    int x1, y1, w1, h1;
    x1 = 12;
    y1 = 0;
    w1 = rect.width() + 4;
    h1 = rect.height();
    m_label->setContentsMargins(2, 0, 0, 0);
    m_label->setGeometry(x1, y1, w1, h1);
}

void WarningGroup::addWarning(Warning *warning)
{
    m_warnings.append(warning);
    m_WarningGroupLayout->insertWidget(0, warning);
}
