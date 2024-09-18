#ifndef WARNING_H
#define WARNING_H

#include <QWidget>

class QLabel;

class Warning : public QWidget
{
    Q_OBJECT
public:
    explicit Warning(QString label, QString type, QWidget *parent = nullptr);

    enum class warningGroup {
        Voltage = 0,
        Current = 1,
        Temperature = 2,
        Other = 3
    };

    std::map<QString, QColor> warningTypeMap{{"Low Voltage", QColor(250, 215, 76)},
                                             {"High Voltage", QColor(219, 100, 100)},
                                             {"High Temperature", QColor(219, 100, 100)}};

    std::map<QString, warningGroup> warningGroupMap{{"Low Voltage", warningGroup::Voltage},
                                             {"High Voltage", warningGroup::Voltage},
                                             {"High Temperature", warningGroup::Temperature}};


protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    QLabel *m_label;
    QString m_type;
    QColor m_backgroundColor;
    QColor m_borderColor = QColor(150, 150, 160);
    int m_maximumWidth = 150;
    warningGroup m_group;

signals:
};

#endif // WARNING_H
