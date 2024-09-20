#ifndef WARNINGGROUP_H
#define WARNINGGROUP_H

#include <QWidget>

namespace Warnings {
    enum warningGroup {
        Voltage = 0,
        Current = 1,
        Temperature = 2,
        Other = 3
    };
}

class QLabel;
class QVBoxLayout;
class Warning;

class WarningGroup : public QWidget {
    Q_OBJECT
public:
    static inline std::map<QString, Warnings::warningGroup> warningGroupMap{
        {"Low Voltage", Warnings::warningGroup::Voltage},
        {"High Voltage", Warnings::warningGroup::Voltage},
        {"High Temperature", Warnings::warningGroup::Temperature}
    };

    explicit WarningGroup(QString group, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *) override;

public slots:
    void addWarning(Warning *warning);

private:
    QColor m_color = QColor(180, 180, 190);
    QLabel *m_label;
    Warnings::warningGroup m_group;
    QVBoxLayout *m_WarningGroupLayout;
    QList<Warning *> m_warnings;

signals:
};

#endif // WARNINGGROUP_H
