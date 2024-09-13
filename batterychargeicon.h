#ifndef BATTERYCHARGEICON_H
#define BATTERYCHARGEICON_H

#include <QWidget>

class BatteryChargeIcon : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryChargeIcon(QWidget *parent = nullptr);

private:
    int m_value = 100;
    QColor m_frame_color = QColor(150, 150, 160);
    QColor m_charge_color = QColor(70, 230, 70);
    QColor m_background_color = QColor(200, 200, 205);
    int m_showTextFlg = 1;
    QString m_showText;//Display text text

protected:
    virtual void paintEvent(QPaintEvent * event) override;

signals:
};

#endif // BATTERYCHARGEICON_H
