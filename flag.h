#ifndef FLAG_H
#define FLAG_H

#include <QWidget>

class QLabel;
class LedImg;

class Flag : public QWidget
{
    Q_OBJECT
public:
    explicit Flag(QWidget *parent = nullptr);
    Flag(QString label, bool mode, QWidget *parent = nullptr);

private:
    QLabel *m_label;
    LedImg *m_led;
    bool m_mode;

public slots:
    void switchFlag();

};

#endif // FLAG_H
