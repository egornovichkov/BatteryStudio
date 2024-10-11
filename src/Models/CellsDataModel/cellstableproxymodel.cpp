#include "cellstableproxymodel.h"
#include "src/bstunamespace.h"
#include <QColor>
#include <QAbstractTableModel>
#include <QFont>

CellsTableProxyModel::CellsTableProxyModel(QObject* parent) {}



QModelIndex CellsTableProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    int cellNumber = m_cellsPerRow * proxyIndex.row() + proxyIndex.column();
    QPersistentModelIndex ind = m_model->index(cellNumber, 0);
    return ind;
}

QModelIndex CellsTableProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    int cellNumber = sourceIndex.row();
    int row = cellNumber / m_cellsPerRow;
    int col = cellNumber - row * m_cellsPerRow;
    QPersistentModelIndex ind = index(row, col);
    return ind;
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
            // return QString("voltage /n Cell number")
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
