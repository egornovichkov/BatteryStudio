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
    /// Color for border of frame.
    QColor m_border_color = QColor(150, 150, 160);
    /// Color for background of frame.
    QColor m_background_color = QColor(220, 220, 230);
    /// Color for backrgound of charge area.
    QColor m_charge_color = QColor(70, 230, 70);
    /// Color for border of charge area.
    QColor m_charge_border_color = QColor(20, 170, 20);
    /// Text on battery charge image.
    QString m_showText;
    /// Text "show/hide" option.
    int m_showTextFlg = 1;

protected:
    /// paintEvent override for battery image.
    virtual void paintEvent(QPaintEvent *event) override;

};

#endif // BATCHARGEIMG_H
