#include "cellstableviewwidget.h"
#include "cellsviewdelegate.h"
#include <iostream>

CellsTableViewWidget::CellsTableViewWidget(QWidget *parent)
{
    m_model = model();
    CellsViewDelegate *delegate = new CellsViewDelegate();
    setItemDelegate(delegate);
}

void CellsTableViewWidget::paintEvent(QPaintEvent *e)
{
    // for (int row = 0; row < m_model->rowCount(); row++)
    // {
    //     std::cout << row << " ";
    //     setRowHeight(row, 30);
        // for (int col = 0; col < m_model->columnCount(); col++)
        // {
        //     if (row == 0)
        //         setColumnWidth(col, 30);
        // }
    // }
    // Hiding unused cells
    // ...................

    // Calling parent's paintEvent to draw default QTableWidget
    QTableView::paintEvent(e);
}
