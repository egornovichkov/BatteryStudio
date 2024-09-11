#ifndef BATTERYCHARGE_H
#define BATTERYCHARGE_H

#include <QProgressBar>
#include <QImage>
#include <QMainWindow>

class BatteryCharge : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryCharge(QWidget *parent = nullptr);

private:
    QWidget *BatteryImgWidget;
    QProgressBar *BatteryChargeBar;
    QImage *BatteryImg;


signals:
};

#endif // BATTERYCHARGE_H
