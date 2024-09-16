#ifndef LEDIMG_H
#define LEDIMG_H

#include <QWidget>

class LedImg : public QWidget
{
    Q_OBJECT
public:
    explicit LedImg(QWidget *parent = nullptr, bool mode = 0, int size = 11);
    void setSize(int size);
    int getSize();

protected:
    virtual void paintEvent(QPaintEvent *) override;

public slots:
    void switchLed();

private:
    bool m_mode;
    int m_size;
    QColor m_active_color = QColor(70, 230, 70);
    QColor m_inactive_color = QColor(220, 220, 225);
    QColor m_border_color = QColor(150, 150, 160);

signals:
};

#endif // LEDIMG_H
