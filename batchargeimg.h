#ifndef BATCHARGEIMG_H
#define BATCHARGEIMG_H

#include <QWidget>

class BatChargeImg : public QWidget
{
    Q_OBJECT
public:
    explicit BatChargeImg(QWidget *parent = nullptr);

private:
    int m_value = 10;
    QColor m_border_color = QColor(150, 150, 160);
    QColor m_background_color = QColor(220, 220, 225);
    QColor m_charge_color = QColor(70, 230, 70);
    QColor m_charge_border_color = QColor(20, 170, 20);
    int m_showTextFlg = 1;
    QString m_showText;//Display text

protected:
    virtual void paintEvent(QPaintEvent *event) override;

};

#endif // BATCHARGEIMG_H
