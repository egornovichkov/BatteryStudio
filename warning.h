#ifndef WARNING_H
#define WARNING_H

#include <QWidget>

class QLabel;

class Warning : public QWidget
{
    Q_OBJECT
public:
    explicit Warning(QString label, QString type, QWidget *parent = nullptr);

    std::map<QString, QColor> warningTypeMap{{"Low Voltage", QColor(255, 255, 102)},
                                             {"High Voltage", QColor(255, 50, 50)},
                                             {"High Temperature", QColor(255, 50, 50)}};

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    QLabel *m_label;
    QString m_type;
    QColor m_backgroundColor;
    QColor m_borderColor = QColor(150, 150, 160);
    int m_maximumWidth = 150;

signals:
};

#endif // WARNING_H
