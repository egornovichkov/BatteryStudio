#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>

class AppWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppWidget(QWidget *parent = nullptr);

signals:
};

#endif // APPWIDGET_H
