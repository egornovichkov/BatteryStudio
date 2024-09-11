#include "batterycharge.h"

BatteryCharge::BatteryCharge(QWidget *parent)
    : QWidget{parent}
{
    BatteryImg = new QImage("images/BatteryIcon.png");
    BatteryChargeBar = new QProgressBar();


    BatteryChargeBar->setObjectName("BatteryChargeBar");
    BatteryChargeBar->setGeometry(QRect(70, 70, 70, 70));
    QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    sizePolicy2.setHorizontalStretch(70);
    sizePolicy2.setVerticalStretch(70);
    sizePolicy2.setHeightForWidth(BatteryChargeBar->sizePolicy().hasHeightForWidth());
    BatteryChargeBar->setSizePolicy(sizePolicy2);
    BatteryChargeBar->setMinimumSize(QSize(70, 70));
    BatteryChargeBar->setMaximumSize(QSize(70, 70));
    QFont font2;
    font2.setFamilies({QString::fromUtf8("Roboto")});
    BatteryChargeBar->setFont(font2);
    BatteryChargeBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
                                                 "	border: 0px;\n"
                                                 "	border-radius: 0px;\n"
                                                 "	background: transparent;\n"
                                                 "	alternate-background-color: rgb(85, 255, 0);\n"
                                                 "}\n"
                                                 "QProgressBar::chunk {\n"
                                                 "	border-radius: 0px;\n"
                                                 "	background:rgb(85, 255, 0);\n"
                                                 "}"));
    BatteryChargeBar->setValue(24);
    BatteryChargeBar->setAlignment(Qt::AlignmentFlag::AlignCenter);
}
