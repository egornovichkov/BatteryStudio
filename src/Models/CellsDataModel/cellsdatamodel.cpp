#include "cellsdatamodel.h"
#include <QColor>
#include <QFont>
#include <iostream>


CellsDataModel::CellsDataModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

QModelIndex CellsDataModel::parent(const QModelIndex &child) const
{
    Q_ASSERT(child.isValid() ? child.model() == this : true);
    return QModelIndex();
}

QModelIndex CellsDataModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
        return QModelIndex();
    QModelIndex ind = createIndex(row, column);
    return ind;
}

float CellsDataModel::maxVoltage(void) const
{
    return m_maxVoltage;
}

float CellsDataModel::minVoltage(void) const
{
    return m_minVoltage;
}

int CellsDataModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_cellsData.count();
}

int CellsDataModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return BSTU::CELLPARAMSCOUNT;
}

QVariant CellsDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QVariant CellsDataModel::data(const QModelIndex& index, int role) const
{
    if (index.row() <= this->rowCount(index) && index.column() <= this->columnCount(index) && index.isValid())
    {
        QVariant value = m_cellsData[index.row()][BSTU::CellParams(BSTU::Voltage)];
        switch (role)
        {
            case Qt::DisplayRole:
                return value;
        }
    }
    return QVariant();
}

bool CellsDataModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || role != Qt::EditRole || m_cellsData.count() <= index.row())
    {
        return false;
    }

    m_cellsData[index.row()][BSTU::CellParams(index.column())] = value;
    emit dataChanged(index, index);

    return true;
}

void CellsDataModel::appendCell(int number, float voltage)
{
    cellValues cellVal;
    cellVal = {{BSTU::CellParams::Number, number},
        {BSTU::CellParams::Voltage, voltage},
    };
    int row = m_cellsData.count();

    beginInsertRows(QModelIndex(), row, row);
    m_cellsData.append(cellVal);
    endInsertRows();
}
