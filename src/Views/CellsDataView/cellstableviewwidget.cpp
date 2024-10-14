#include "cellstableviewwidget.h"
#include "cellsviewdelegate.h"

CellsTableViewWidget::CellsTableViewWidget(QWidget *parent)
{
    CellsViewDelegate *delegate = new CellsViewDelegate();
    setItemDelegate(delegate);
}

void CellsTableViewWidget::paintEvent(QPaintEvent *e)
{
    // Hiding unused cells
    // ...................

    // Calling parent's paintEvent to draw default QTableWidget
    QTableView::paintEvent(e);
}
