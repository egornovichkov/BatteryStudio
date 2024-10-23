#include "cellstableviewwidget.h"
#include "cellsviewdelegate.h"
#include "src/bstunamespace.h"
#include <QPainter>
#include <QHeaderView>
#include <iostream>

// Re-implementation of QHeaderView
// class MyHeaderView : public QHeaderView {
// public:
//     MyHeaderView(QWidget* parent = NULL) : QHeaderView(Qt::Vertical,parent){}
//     virtual void resizeEvent(QResizeEvent * event);
// };

// void MyHeaderView::resizeEvent(QResizeEvent * event) {
//     QHeaderView::resizeEvent(event);
//     emit geometriesChanged();
// }

CellsTableViewWidget::CellsTableViewWidget(QWidget *parent)
{
    Q_UNUSED(parent);
    CellsViewDelegate *delegate = new CellsViewDelegate(this);
    setItemDelegate(delegate);
    // MyHeaderView* header = new MyHeaderView(this);
    // setVerticalHeader(header);
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
    // painter.drawRect(0,0,height(),width());


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
    // Hiding unused cells
    // ...................

    // Calling parent's paintEvent to draw default QTableWidget

}
