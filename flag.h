#ifndef FLAG_H
#define FLAG_H

#include "ledimg.h"
#include <QWidget>

class Flag : public QWidget
{
    Q_OBJECT
public:
    explicit Flag(QWidget *parent = nullptr);

private:
    QString m_label;
    LedImg m_led;

signals:
};

#endif // FLAG_H
