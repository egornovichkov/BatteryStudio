#include "cellstableproxymodel.h"
#include "src/bstunamespace.h"
#include <QColor>
#include <QAbstractTableModel>
#include <QFont>
#include <iostream>

CellsTableProxyModel::CellsTableProxyModel(QObject* parent) {}

QModelIndex CellsTableProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    int cellNumber = m_cellsPerRow * proxyIndex.row() + proxyIndex.column();
    QPersistentModelIndex ind = sourceModel()->index(cellNumber, 0);
    return ind;
}

QModelIndex CellsTableProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    int cellNumber = sourceIndex.row();
    int row = cellNumber / m_cellsPerRow;
    int col = cellNumber - row * m_cellsPerRow;
    QPersistentModelIndex ind = createIndex(row, col);
    return ind;
}

QModelIndex CellsTableProxyModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QModelIndex CellsTableProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return createIndex(row, column);
    }
    return QModelIndex();
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
    std::cout << "data";
    switch (role)
    {
        case Qt::DisplayRole:
            return sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Voltage));
        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;
        case Qt::FontRole:
        {
            QFont font = QFont("Segoe UI", 6, QFont::Normal);
            return font;
        }
        case Qt::BackgroundRole:
            return valToColor(sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Voltage)).toFloat());
        case Qt::UserRole:
        {
            float range = (sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Maximum)).toFloat()) -
                (sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Minimum)).toFloat());
            float relativeBarHeight = range * (sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Voltage)).toFloat());
            return relativeBarHeight;
        }
        default:
            break;
    }
    return mapToSource(index).data(role);
}

QColor CellsTableProxyModel::valToColor(float value) const
{
    return Qt::red;
}

void CellsTableProxyModel::setCellsPerRow(int value)
{
    m_cellsPerRow = value;
    // Update logic
}

void CellsTableProxyModel::modelAboutToBeResetInSourceModel()
{
    beginResetModel();
}

void CellsTableProxyModel::modelResetInSourceModel()
{
    endResetModel();
}

void CellsTableProxyModel::rowsAboutToBeInsertedInSourceModel(const QModelIndex &parent, int start, int end)
{
    if (parent.isValid())
    {
        // Added rows not below the root
        return;
    }

    beginInsertRows(QModelIndex(), start, end);
}

void CellsTableProxyModel::rowsInsertedInSourceModel(const QModelIndex &parent, int start, int end)
{
    {
        Q_UNUSED(start);
        Q_UNUSED(end);

        if (parent.isValid())
        {
            // Added rows not below the root
            return;
        }

        endInsertRows();
    }
}

void CellsTableProxyModel::rowsAboutToBeRemovedInSourceModel(const QModelIndex &parent, int first, int last)
{
    if (parent.isValid())
    {
        // Removed rows not below the root
        return;
    }

    beginRemoveRows(QModelIndex(), first, last);
}

void CellsTableProxyModel::rowsRemovedInSourceModel(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(first);
    Q_UNUSED(last);

    if (parent.isValid())
    {
        // Removed rows not below the root
        return;
    }

    endRemoveRows();
}

void CellsTableProxyModel::dataChangedInSourceModel(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                              const QVector<int> &roles)
{
    Q_ASSERT(topLeft.parent() == bottomRight.parent());
    if (topLeft.parent().isValid())
    {
        // Non-top level items changed, we don't display those
        return;
    }

    const int firstColumn = topLeft.column();
    const int lastColumn = bottomRight.column();

    const int firstRow = topLeft.row();
    const int lastRow = bottomRight.row();
    Q_EMIT dataChanged(index(firstRow, 0), index(lastRow, 0));
}
