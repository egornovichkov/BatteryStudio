#include "cellstableproxymodel.h"
#include "src/bstunamespace.h"
#include <QColor>
#include <QAbstractTableModel>
#include <QFont>
#include <iostream>

CellsTableProxyModel::CellsTableProxyModel(QObject* parent) {}

QModelIndex CellsTableProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    std::cout << "mapFromSource" << " " << sourceIndex.row() << " " << sourceIndex.column();
    if (!sourceIndex.isValid())
    {
        // root
        return QModelIndex();
    }

    int cellNumber = sourceIndex.row();
    int row = cellNumber / m_cellsPerRow;
    int col = cellNumber - row * m_cellsPerRow;
    std::cout << " " << row << " " << col << "\n";

    return index(row, col);
}

// Pay attention (!)
QModelIndex CellsTableProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!proxyIndex.isValid())
    {
        return QModelIndex();
    }

    int cellNumber = mapFromSource(proxyIndex).row();
    std::cout << "cellNumber" << " " << cellNumber << "\n";

    if (sourceModel())
    {
        QModelIndex ind = sourceModel()->index(cellNumber, 0);
        std::cout << "sourceIndexResult" << " " << ind.row() << " " << ind.column() << "\n";
        return ind;
    }
    else
        return QModelIndex();
}


QModelIndex CellsTableProxyModel::parent(const QModelIndex &child) const
{
    Q_ASSERT(child.isValid() ? child.model() == this : true);
    return QModelIndex();
}

QModelIndex CellsTableProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    // Q_ASSERT(hasChildren(parent));
    // Q_ASSERT(row >= 0 && row < rowCount(parent));
    // Q_ASSERT(column >= 0 && column < columnCount(parent));
    // std::cout << "index" << " " << row << " " << column << " " << parent.row() << " " << parent.column() <<  "\n";
    std::cout << "index" << "\n";
    if (parent.model() == this)
        std::cout << "lol";
    if (parent.isValid())
    {
        std::cout << "parent.isvalid == true" << "\n";
        return QModelIndex();
    }
    QModelIndex ind = createIndex(row, column);
    std::cout << "createIndex" << " " << row << " " << column << "\n";
    return ind;

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
    std::cout << "valToColor" << "\n";
    return Qt::red;
}

void CellsTableProxyModel::setCellsPerRow(int value)
{
    std::cout << "setCellsPerRow" << "\n";
    m_cellsPerRow = value;
    // Update logic
}
