#ifndef CELLSVIEWDELEGATE_H
#define CELLSVIEWDELEGATE_H

#include <QStyledItemDelegate>

class CellsViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    CellsViewDelegate();
};

#endif // CELLSVIEWDELEGATE_H
