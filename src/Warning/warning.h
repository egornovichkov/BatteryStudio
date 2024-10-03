#ifndef WARNING_H
#define WARNING_H

#include "warninggroup.h"
#include <QWidget>

class QLabel;

class Warning : public QWidget
{
    Q_OBJECT
public:
    explicit Warning(QString label, QString type, QWidget *parent = nullptr);

    /// Map for matching type to color of warning.
    std::map<QString, QColor> warningTypeMap{{"Low Voltage", QColor(250, 215, 76)},
        {"High Voltage", QColor(219, 100, 100)},
        {"High Temperature", QColor(219, 100, 100)}};

protected:
    /// paintEvent override for warning.
    virtual void paintEvent(QPaintEvent*) override;

private:
    /// Text label.
    QLabel *m_label;
    /// Warning type.
    QString m_type;
    /// Color for background.
    QColor m_backgroundColor;
    /// Color for border.
    QColor m_borderColor = QColor(150, 150, 160);
    /// Warning group.
    Warnings::warningGroup m_group;
    /// List of pointers to all warning groups
    QList<WarningGroup *> m_groups;
    /// Maximum width for warning
    int m_maximumWidth = 120;
    /// Flag for group mode ("groupped/ungroupped")
    static bool m_groupMode;
};

#endif // WARNING_H
