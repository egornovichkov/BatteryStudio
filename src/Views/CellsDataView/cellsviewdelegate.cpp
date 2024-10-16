#include "cellsviewdelegate.h"
#include "src/bstunamespace.h"
#include <QPainter>
#include <charconv>

CellsViewDelegate::CellsViewDelegate() {}

void CellsViewDelegate::paint(QPainter *painter,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    painter->setRenderHint(QPainter::Antialiasing);
    const QAbstractItemModel *model = index.model();
    BSTU::CellsModel modelType = BSTU::CellsModel((model->data(index, BSTU::ModelTypeRole)).toInt());
    float value = (modelType == BSTU::VoltageType)
        ? model->data(index, BSTU::VoltRole).toFloat()
        : model->data(index, BSTU::TempRole).toFloat();
    QColor color = qvariant_cast<QColor>(model->data(index, Qt::BackgroundRole));
    float relativeBarHeight = model->data(index, BSTU::RelativeBarHeightRole).toFloat();
    if (relativeBarHeight > 0)
    {
        float barHeight = option.rect.height() * relativeBarHeight;
        QRectF cellRect = option.rect;

        // Height according to value
        cellRect.setHeight(barHeight);
        // Move to cell bottom
        cellRect.moveBottom(option.rect.height());

        // Translate coordinate system to cell bottom
        painter->translate(0, index.row() * option.rect.height() + 1);
        painter->fillRect(cellRect, color);
        // Back to native coordinate system
        painter->translate(0, -index.row() * option.rect.height() - 1);
        QString caption;
        caption = QString::number(value) + "V" + "\n" + "Cell ";
        painter->drawText(option.rect, Qt::AlignCenter, caption);
    }
}
