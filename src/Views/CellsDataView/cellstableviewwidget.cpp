#include "cellstableviewwidget.h"

CellsTableViewWidget::CellsTableViewWidget(QWidget *parent) {}

void CellsTableViewWidget::paintEvent(QPaintEvent *e)
{
    // Hiding unused cells
    // ...................

    // Calling parent's paintEvent to draw default QTableWidget
    QTableWidget::paintEvent(e);
}
