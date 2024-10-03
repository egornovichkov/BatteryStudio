#ifndef LEDIMG_H
#define LEDIMG_H

#include <QWidget>

class LedImg : public QWidget
{
    Q_OBJECT
public:
    explicit LedImg(int size, bool mode = 0, QWidget *parent = nullptr);
    /// Setter for LED diameter.
    void setSize(int size);
    /// Getter for LED diameter.
    int getSize();

protected:
    /// paintEvent override for LED image.
    virtual void paintEvent(QPaintEvent*) override;

public slots:
    /// Handler for LED mode switch.
    void switchLed();

private:
    /// LED mode ("on/off").
    bool m_mode;
    /// Diameter of LED.
    int m_size;
    /// Inside color for active mode.
    QColor m_activeColor = QColor(70, 230, 70);
    /// Inside color for inactive mode.
    QColor m_inactiveColor = QColor(220, 220, 225);
    /// Border color.
    QColor m_borderColor = QColor(150, 150, 160);

signals:
};

#endif // LEDIMG_H
