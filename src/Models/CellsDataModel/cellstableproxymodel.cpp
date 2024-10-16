#include "cellstableproxymodel.h"
#include "src/bstunamespace.h"
#include <QColor>
#include <QAbstractTableModel>
#include <QFont>

CellsTableProxyModel::CellsTableProxyModel(QObject* parent) {}

QModelIndex CellsTableProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if (!sourceIndex.isValid())
        return QModelIndex();

    int cellsCount = sourceIndex.model()->rowCount();
    int row = cellsCount / m_cellsPerRow ;
    int col = cellsCount % m_cellsPerRow;
    return index(row, col);
}

QModelIndex CellsTableProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!proxyIndex.isValid())
        return QModelIndex();

    int cellNumber = proxyIndex.row() * m_cellsPerRow + proxyIndex.column();
    if (cellNumber > sourceModel()->rowCount() - 1)
        return QModelIndex();
    return sourceModel()->index(cellNumber, 0);
}


QModelIndex CellsTableProxyModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QModelIndex CellsTableProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();

}

int CellsTableProxyModel::rowCount(const QModelIndex& parent) const
{
    return std::ceil(static_cast<float>(sourceModel()->rowCount()) / m_cellsPerRow);
}

int CellsTableProxyModel::columnCount(const QModelIndex& parent) const
{
    return m_cellsPerRow;
}

QVariant CellsTableProxyModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
        case Qt::DisplayRole:
            return sourceModel()->data(mapToSource(index));
        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;
        case Qt::FontRole:
        {
            QFont font = QFont("Segoe UI", 6, QFont::Normal);
            return font;
        }
        case Qt::BackgroundRole:
            return valToColor((sourceModel()->data(mapToSource(index)).toFloat()));
        case Qt::UserRole:
        {
            float range = 5;
            float relativeBarHeight = (sourceModel()->data(mapToSource(index)).toFloat()) / range;
            return relativeBarHeight;
        }
        case Qt::UserRole + 1:
            return sourceModel()->data(mapToSource(index).siblingAtRow(0));
        default:
            break;
    }
        return QVariant();
}

QColor CellsTableProxyModel::valToColor(float value) const
{
    return (value > 3) ? Qt::green : Qt::red;
}

void CellsTableProxyModel::setCellsPerRow(int value)
{
    m_cellsPerRow = value;
    // Update logic
}
