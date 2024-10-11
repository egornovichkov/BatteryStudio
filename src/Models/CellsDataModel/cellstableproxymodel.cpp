#include "cellstableproxymodel.h"
#include "src/bstunamespace.h"
#include <QColor>
#include <QAbstractTableModel>
#include <QFont>

CellsTableProxyModel::CellsTableProxyModel(QObject* parent) {}



QModelIndex CellsTableProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    // int cellNumber = m_cellsPerRow * proxyIndex.row() + proxyIndex.column();
    // QPersistentModelIndex ind = m_model->index(cellNumber, 0);
    // return ind;
    return proxyIndex;
}

QModelIndex CellsTableProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    // int cellNumber = sourceIndex.row();
    // int row = cellNumber / m_cellsPerRow;
    // int col = cellNumber - row * m_cellsPerRow;
    // QPersistentModelIndex ind = createIndex(row, col);
    // return ind;
    return sourceIndex;
}

QModelIndex CellsTableProxyModel::parent(const QModelIndex &child) const
{
    if (child.isValid())
        return QModelIndex();
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
    return m_cellsCount / m_cellsPerRow;
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
        return sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Voltage));
            break;
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
    return QVariant();
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
