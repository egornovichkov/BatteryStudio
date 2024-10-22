#include "cellsviewdelegate.h"
#include "src/bstunamespace.h"
#include <QPainter>
#include <QTableView>
#include <iostream>

CellsViewDelegate::CellsViewDelegate(QTableView* view) : m_view(view) {}

void CellsViewDelegate::paint(QPainter *painter,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    // painter->setRenderHint(QPainter::Antialiasing);
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

        // Translate coordinate system to current row
        painter->translate(0, m_view->rowViewportPosition(index.row()));
        painter->fillRect(cellRect, color);
        // Back to native coordinate system
        painter->translate(0, -m_view->rowViewportPosition(index.row()));
    }
    QString caption;
    if (modelType == BSTU::VoltageType)
        caption = QString::number(value) + "V\nCell " + QString::number(model->data(index, BSTU::NumRole).toInt());
    else
        caption = QString::number(value) + "°C\nCell " + QString::number(model->data(index, BSTU::NumRole).toInt());
    painter->drawText(option.rect, Qt::AlignCenter, caption);
}
