#include "cellstableviewwidget.h"
#include "cellsviewdelegate.h"
#include "src/bstunamespace.h"
#include <QPainter>
#include <QHeaderView>
#include <iostream>

CellsTableViewWidget::CellsTableViewWidget(QWidget *parent)
{
    CellsViewDelegate *delegate = new CellsViewDelegate(this);
    setItemDelegate(delegate);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setMinimumSectionSize(30);
    horizontalHeader()->setMinimumSectionSize(43);
}

void CellsTableViewWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QTableView::paintEvent(e);

    int lastCellCol = model()->data(QModelIndex(), BSTU::LastCellIndexRole).toInt();
    int lastCellRow = model()->rowCount();
    int x = columnViewportPosition(lastCellCol);
    int y = rowViewportPosition(lastCellRow);
    painter.setBrush(Qt::gray);
    painter.drawRect(x, y, 20, 20);
    // Hiding unused cells
    // ...................

    // Calling parent's paintEvent to draw default QTableWidget
}
