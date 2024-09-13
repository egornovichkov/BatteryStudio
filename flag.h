#ifndef FLAG_H
#define FLAG_H

#include <QWidget>

class Flag : public QWidget
{
    Q_OBJECT
public:
    explicit Flag(QWidget *parent = nullptr);

private:
    QString m_label;

signals:
};

#endif // FLAG_H
