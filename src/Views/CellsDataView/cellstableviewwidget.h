#ifndef CELLSTABLEVIEWWIDGET_H
#define CELLSTABLEVIEWWIDGET_H

#include <QTableWidget>


class CellsTableViewWidget : public QTableView
{
    Q_OBJECT
public:
    CellsTableViewWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e) override;

private:
    /// Max count of cells in a row (default = 10).
    int m_cellsPerRow = 10;
    /// Min/Max voltages are for correct display of voltage bar and color of cell backrgound.
    /// Minimum voltage (default = 0).
    float m_minVoltage = 0;
    /// Maximum voltage.
    float m_maxVoltage;

};

#endif // CELLSTABLEVIEWWIDGET_H
