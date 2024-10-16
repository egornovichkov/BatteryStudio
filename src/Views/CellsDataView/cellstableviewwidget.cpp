#include "cellstableviewwidget.h"
#include "cellsviewdelegate.h"
#include <QHeaderView>
#include <iostream>

CellsTableViewWidget::CellsTableViewWidget(QWidget *parent)
{
    m_model = model();
    CellsViewDelegate *delegate = new CellsViewDelegate();
    setItemDelegate(delegate);
    horizontalHeader()->hide();
    verticalHeader()->hide();
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

void CellsTableViewWidget::setSizeToContents()
{
    float height = 0;
    float width = 0;

    verticalHeader()->setDefaultSectionSize(20);
    for (int col = 0; col < model()->columnCount(); col++)
    {
        std::cout << columnWidth(col) << "\n";
        width += columnWidth(col);
    }
    for (int row = 0; row < model()->rowCount(); row++)
    {
        setRowHeight(row, 100);
        std::cout << rowHeight(row) << "\n";
        height += rowHeight(row);
    }
    std::cout << height << " " << width << "\n";
    // setFixedWidth(width);
    // setFixedHeight(height);
}
