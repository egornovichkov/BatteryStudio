#include "cellstableviewwidget.h"

CellsTableViewWidget::CellsTableViewWidget(QAbstractTableModel *model, QWidget *parent)
{
    m_model = model;
    setModel(m_model);

    // this->setColumnWidth();
    // this->setRowHeight();

    // for (int row = 0; row < model->rowCount(); ++row)
    // {
    //     for (int col = 0; col < model->columnCount(); ++col)
    //     {
    //         // model->data(QModelIndex(row, col, 1))
    //     }
    // }
}

void CellsTableViewWidget::paintEvent(QPaintEvent *e)
{
    // Hiding unused cells
    // ...................

    // Calling parent's paintEvent to draw default QTableWidget
    QTableView::paintEvent(e);
}

QColor CellsTableViewWidget::valToColor(float val)
{
    if (val > 2)
        return QColor(Qt::green);
    return QColor(Qt::red);
}

