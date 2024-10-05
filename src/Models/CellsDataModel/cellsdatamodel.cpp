#include "cellsdatamodel.h"

CellsDataModel::CellsDataModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int CellsDataModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_cellsData.count();
}

int CellsDataModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return CELLPARAMSCOUNT;
}

QVariant CellsDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Vertical)
    {
        return section;
    }

    switch (section)
    {
        case Number:
            return QString::fromUtf8("Number");
        case Voltage:
            return QString::fromUtf8("Voltage");

    }

    return QVariant();
}

QVariant CellsDataModel::data(const QModelIndex& index, int role) const
{
    if (
        !index.isValid() ||
        m_cellsData.count() <= index.row() ||
        (role != Qt::DisplayRole && role != Qt::EditRole)
    )
    {
        return QVariant();
    }

    return m_cellsData[index.row()][CellParams(index.column())];
}

bool CellsDataModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || role != Qt::EditRole || m_cellsData.count() <= index.row())
    {
        return false;
    }

    m_cellsData[index.row()][CellParams(index.column())] = value;
    emit dataChanged(index, index);

    return true;
}
