#ifndef WARNING_H
#define WARNING_H

#include <QWidget>

class QLabel;

class Warning : public QWidget
{
    Q_OBJECT
public:
    explicit Warning(QString label, QString type, QWidget *parent = nullptr);

    std::map<QString, QColor> warningTypeMap{{"Low Voltage", Qt::yellow},
                                            {"High Voltage", Qt::red},
                                            {"High Temperature", Qt::red}};

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    QLabel *m_label;
    QString m_type;
    QColor m_backgroundColor;
    QColor m_borderColor = QColor(150, 150, 160);


signals:
};

#endif // WARNING_H
