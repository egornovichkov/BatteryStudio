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

    std::map<QString, QColor> warningTypeMap{{"Low Voltage", QColor(250, 215, 76)},
                                             {"High Voltage", QColor(219, 100, 100)},
                                             {"High Temperature", QColor(219, 100, 100)}};

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    QLabel *m_label;
    QString m_type;
    QColor m_backgroundColor;
    QColor m_borderColor = QColor(150, 150, 160);
    Warnings::warningGroup m_group;
    QList<WarningGroup *> m_groups;
    int m_maximumWidth = 120;
    static bool m_groupMode;

signals:
};

#endif // WARNING_H
