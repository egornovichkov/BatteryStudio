#include "cellstableviewwidget.h"
#include "cellsviewdelegate.h"
#include "src/bstunamespace.h"
#include <QPainter>
#include <QHeaderView>
#include <iostream>

CellsTableViewWidget::CellsTableViewWidget(QWidget *parent)
{
    Q_UNUSED(parent);
    CellsViewDelegate *delegate = new CellsViewDelegate(this);
    setItemDelegate(delegate);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setMinimumSectionSize(30);
    horizontalHeader()->setMinimumSectionSize(43);
    horizontalHeader()->hide();
    verticalHeader()->hide();
}

void CellsTableViewWidget::paintEvent(QPaintEvent *e)
{
    QTableView::paintEvent(e);

    QPainter painter(viewport());


    if (model())
    {
        int lastCellCol = model()->data(QModelIndex(), BSTU::LastCellIndexRole).toInt();
        int lastCellRow = model()->rowCount() - 1;
        std::cout << columnViewportPosition(lastCellCol) << "\n";
        std::cout << rowViewportPosition(lastCellRow) << "\n";
        int x = columnViewportPosition(lastCellCol);
        int y = rowViewportPosition(lastCellRow);
        painter.setBrush(QColor(244, 244, 249));
        painter.setPen(QColor(244, 244, 249));
        painter.drawRect(x, y, width() - x, height() - y);
    }
}
