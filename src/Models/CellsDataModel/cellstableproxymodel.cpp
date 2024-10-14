#include "cellstableproxymodel.h"
#include "src/bstunamespace.h"
#include <QColor>
#include <QAbstractTableModel>
#include <QFont>
#include <iostream>

CellsTableProxyModel::CellsTableProxyModel(QObject* parent) {}

QModelIndex CellsTableProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if (!sourceIndex.isValid())
        return QModelIndex();

    int cellsCount = sourceIndex.model()->rowCount();
    int row = cellsCount / m_cellsPerRow ;
    int col = cellsCount % m_cellsPerRow;
    std::cout << "mapFromSource" << " " << row << " " << col << "\n";
    return index(row, col);
}

QModelIndex CellsTableProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!proxyIndex.isValid())
        return QModelIndex();

    int cellNumber = proxyIndex.row() * m_cellsPerRow + proxyIndex.column();
    if (cellNumber > sourceModel()->rowCount() - 1)
        return QModelIndex();
    std::cout << "maptosrc proxyIndex row/col" << " " << proxyIndex.row() << " " << proxyIndex.column() << "\n";
    std::cout << "mapToSource" << " " << cellNumber << " 0" << "\n";
    return sourceModel()->index(cellNumber, 0);
}


QModelIndex CellsTableProxyModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QModelIndex CellsTableProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    std::cout << "index() " << row << " " << column << "\n";
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();

}

int CellsTableProxyModel::rowCount(const QModelIndex& parent) const
{
    std::cout << "rowCount" << "\n";
    return std::ceil(static_cast<float>(sourceModel()->rowCount()) / m_cellsPerRow);
}

int CellsTableProxyModel::columnCount(const QModelIndex& parent) const
{
    std::cout << "columnCount" << "\n";
    return m_cellsPerRow;
}

QVariant CellsTableProxyModel::data(const QModelIndex& index, int role) const
{
    std::cout << "data";
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
            return valToColor(sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Voltage)).toFloat());
        case Qt::UserRole:
        {
            // float range = (sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Maximum)).toFloat()) -
            //     (sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Minimum)).toFloat());
            // float relativeBarHeight = range * (sourceModel()->data(QModelIndex().siblingAtRow(BSTU::Voltage)).toFloat());
            // return relativeBarHeight;
        }
        default:
            break;
    }
        return QVariant();
}

QColor CellsTableProxyModel::valToColor(float value) const
{
    std::cout << "valToColor" << "\n";
    return Qt::red;
}

void CellsTableProxyModel::setCellsPerRow(int value)
{
    std::cout << "setCellsPerRow" << "\n";
    m_cellsPerRow = value;
    // Update logic
}
