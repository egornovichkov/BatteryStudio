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
    /// Constructor with text and mode parameters.
    Flag(QString label, bool mode, QWidget *parent = nullptr);

private:
    /// Text label.
    QLabel *m_label;
    /// LED indicator.
    LedImg *m_led;
    /// Flag mode ("on/off")
    bool m_mode;

public slots:
    /// Handler for flag mode switch.
    void switchFlag();

};

#endif // FLAG_H
