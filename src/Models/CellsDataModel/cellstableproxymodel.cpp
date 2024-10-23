#include "cellstableproxymodel.h"
#include "src/bstunamespace.h"
#include <QColor>
#include <QAbstractTableModel>
#include <QFont>

CellsTableProxyModel::CellsTableProxyModel(QAbstractProxyModel* parent)
    : QAbstractProxyModel{parent}
{}

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
    Q_UNUSED(child);
    return QModelIndex();
}

QModelIndex CellsTableProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();

}

int CellsTableProxyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return std::ceil(static_cast<float>(sourceModel()->rowCount()) / m_cellsPerRow);
}

int CellsTableProxyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_cellsPerRow;
}

QVariant CellsTableProxyModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
        case Qt::DisplayRole:
        case BSTU::NumRole:
        case BSTU::VoltRole:
        case BSTU::TempRole:
        case BSTU::MinVoltRole:
        case BSTU::MaxVoltRole:
        case BSTU::MinTempRole:
        case BSTU::MaxTempRole:
        case BSTU::VoltRangeRole:
        case BSTU::TempRangeRole:
            return sourceModel()->data(mapToSource(index), role);
        case BSTU::RelativeBarHeightRole:
        {
            if (data(index, BSTU::ModelTypeRole).toInt() == BSTU::VoltageType)
                return data(index, BSTU::VoltRole).toFloat() / data(index, BSTU::VoltRangeRole).toFloat();
            else
                return data(index, BSTU::TempRole).toFloat() / data(index, BSTU::TempRangeRole).toFloat();
        }
        case BSTU::LastCellIndexRole:
        {
            return m_cellsCount % m_cellsPerRow;
        }
        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;
        case Qt::FontRole:
        {
            QFont font = QFont("Segoe UI", 6, QFont::Normal);
            return font;
        }
        case Qt::BackgroundRole:
        {
            if (data(index, BSTU::ModelTypeRole).toInt() == BSTU::VoltageType)
                return valToColor(data(index, BSTU::VoltRole).toFloat());
            else
                return valToColor(data(index, BSTU::TempRole).toFloat());
        }
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
