#ifndef LED_H
#define LED_H

#include <QWidget>

class LED : public QWidget
{
    Q_OBJECT
public:
    explicit LED(QWidget *parent = nullptr);

signals:
};

#endif // LED_H
