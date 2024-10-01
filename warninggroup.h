#ifndef WARNINGGROUP_H
#define WARNINGGROUP_H

#include <QWidget>

namespace Warnings
{
/// Enumeration for warning group names.
enum warningGroup
{
    Voltage = 0,
    Current = 1,
    Temperature = 2,
    Other = 3
};
}

class QLabel;
class QVBoxLayout;
class Warning;

class WarningGroup : public QWidget
{
    Q_OBJECT
public:
    /// Map for matching type to group of warning.
    static inline std::map<QString, Warnings::warningGroup> warningGroupMap
    {
        {"Low Voltage", Warnings::warningGroup::Voltage},
        {"High Voltage", Warnings::warningGroup::Voltage},
        {"High Temperature", Warnings::warningGroup::Temperature}
    };

    explicit WarningGroup(QString group, QWidget *parent = nullptr);

protected:
    /// paintEvent override for warning group.
    virtual void paintEvent(QPaintEvent*) override;

public slots:
    /// Function for adding warning to group.
    void addWarning(Warning *warning);

private:
    /// Color of frame and text.
    QColor m_color = QColor(180, 180, 190);
    /// Text label.
    QLabel *m_label;
    /// Group name.
    Warnings::warningGroup m_group;
    /// Group layout.
    QVBoxLayout *m_WarningGroupLayout;
    /// List of pointers to all warnings of this group.
    QList<Warning *> m_warnings;

signals:
};

#endif // WARNINGGROUP_H
