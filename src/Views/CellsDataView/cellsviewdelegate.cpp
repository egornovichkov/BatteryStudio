#include "cellsviewdelegate.h"
#include <QPainter>

CellsViewDelegate::CellsViewDelegate() {}

void CellsViewDelegate::paint(QPainter *painter,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    float relativeBarHeight;
    QColor color = QColor(255, 0, 0);

    float range = (model->data(index.siblingAtColumn(3))).toFloat() - (model->data(index.siblingAtColumn(2))).toFloat();
    relativeBarHeight = (model->data(index.siblingAtColumn(1))).toFloat() / range;
    QRect cellRect = option.rect;
    cellRect.setHeight(cellRect.height() * relativeBarHeight);
    painter->fillRect(cellRect, color);

    return QStyledItemDelegate::paint(painter, option, index);
}
