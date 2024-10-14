#include "cellsviewdelegate.h"
#include <QPainter>
#include <iostream>

CellsViewDelegate::CellsViewDelegate() {}

void CellsViewDelegate::paint(QPainter *painter,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    const QAbstractItemModel *model = index.model();
    QColor color = qvariant_cast<QColor>(model->data(index, Qt::BackgroundRole));
    float relativeBarHeight = (model->data(index, Qt::UserRole)).toFloat();
    float barHeight = option.rect.height() * relativeBarHeight;
    if (barHeight > 0)
    {
        QRect cellRect = option.rect;
        cellRect.setHeight(barHeight);
        cellRect.moveBottom(option.rect.height() - barHeight + 1);
        std::cout << cellRect.topLeft().x() << " " << cellRect.topLeft().y() << "\n";
        painter->fillRect(cellRect, color);
        painter->drawRect(option.rect);
    }
}
