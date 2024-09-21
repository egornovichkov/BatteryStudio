#ifndef LEDIMG_H
#define LEDIMG_H

#include <QWidget>

class LedImg : public QWidget
{
    Q_OBJECT
public:
    explicit LedImg(int size, bool mode = 0, QWidget *parent = nullptr);
    void setSize(int size);
    int getSize();

protected:
    virtual void paintEvent(QPaintEvent*) override;

public slots:
    void switchLed();

private:
    bool m_mode;
    int m_size;
    QColor m_activeColor = QColor(70, 230, 70);
    QColor m_inactiveColor = QColor(220, 220, 225);
    QColor m_borderColor = QColor(150, 150, 160);

signals:
};

#endif // LEDIMG_H
