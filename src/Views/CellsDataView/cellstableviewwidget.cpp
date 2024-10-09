#include "cellstableviewwidget.h"
#include "cellsviewdelegate.h"

CellsTableViewWidget::CellsTableViewWidget(QAbstractTableModel *model, QWidget *parent)
{
    int rowHeight = 10;
    int colWidth = 20;
    m_model = model;
    setModel(m_model);

    // setItemDelegate(new CellsViewDelegate());
    for (int row = 0; row < model->rowCount(); ++row)
    {
        this->setRowHeight(row, rowHeight);
        for (int col = 0; col < model->columnCount(); ++col)
        {
            if (row == 0)
                this->setColumnWidth(col, colWidth);
        }
    }
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

