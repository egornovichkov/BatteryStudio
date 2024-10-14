#include "cellsdatamodel.h"
#include <QColor>
#include <QFont>
#include <iostream>


CellsDataModel::CellsDataModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

QModelIndex CellsDataModel::parent(const QModelIndex &child) const
{
    std::cout << "cellsdatamodel::parent()" << "\n";
    Q_ASSERT(child.isValid() ? child.model() == this : true);
    return QModelIndex();
}

QModelIndex CellsDataModel::index(int row, int column, const QModelIndex &parent) const
{
    std::cout << "cellsdatamodel::index()" << " " << row << " " << column << "\n";
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
    std::cout << "Cellsdatamodel::rowCount()" << "\n";
    Q_UNUSED(parent)
    return m_cellsData.count();
}

int CellsDataModel::columnCount(const QModelIndex& parent) const
{
    std::cout << "Cellsdatamodel::columnCount()" << "\n";
    Q_UNUSED(parent)
    return BSTU::CELLPARAMSCOUNT;
}

QVariant CellsDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QVariant CellsDataModel::data(const QModelIndex& index, int role) const
{
    std::cout << "CellsDataModel::data()" << "\n";
    if (index.row() <= this->rowCount(index) && index.column() <= this->columnCount(index) && index.isValid())
    {
        std::cout << "DataIndex: " << index.row() << " " << index.column() << "\n";
        QVariant value = m_cellsData[index.row()][BSTU::CellParams(index.column())];
        if (role == Qt::DisplayRole)
            return value;
        switch (role)
        {
            case Qt::TextAlignmentRole:
                return Qt::AlignCenter;
            case Qt::FontRole:
            {
                QFont font = QFont("Segoe UI", 6, QFont::Normal);
                return font;
            }
            case Qt::BackgroundRole:
                return valToColor((m_cellsData[index.row()][BSTU::CellParams(index.column())]).toFloat());
            case Qt::UserRole:
            {
                float range = (m_cellsData[index.row()][BSTU::CellParams(index.column())]).toFloat() -
                    (m_cellsData[index.row()][BSTU::CellParams(index.column())]).toFloat();
                float relativeBarHeight = (m_cellsData[index.row()][BSTU::CellParams(index.column())]).toFloat() / range;
                return relativeBarHeight;
            }
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

void CellsDataModel::appendCell(int number, float voltage, float minvoltage, float maxvoltage)
{
    cellValues cellVal;
    cellVal = {{BSTU::CellParams::Number, number},
        {BSTU::CellParams::Voltage, voltage},
        {BSTU::CellParams::Minimum, minvoltage},
        {BSTU::CellParams::Maximum, maxvoltage}
    };
    int row = m_cellsData.count();

    beginInsertRows(QModelIndex(), row, row);
    m_cellsData.append(cellVal);
    endInsertRows();
}

QColor CellsDataModel::valToColor(float value) const
{
    return Qt::green;
}
