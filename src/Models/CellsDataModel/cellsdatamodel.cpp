#include "cellsdatamodel.h"
#include <QColor>
#include <QFont>


CellsDataModel::CellsDataModel(BSTU::CellsModel modelType, QObject *parent)
    : QAbstractTableModel{parent}, m_modelType(modelType)
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


int CellsDataModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_cellsData.count();
}

int CellsDataModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return BSTU::CELLPARAMSCOUNT;
}

QVariant CellsDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

QVariant CellsDataModel::data(const QModelIndex& index, int role) const
{
    if (index.row() <= this->rowCount(index) && index.column() <= this->columnCount(index) && index.isValid())
    {
        switch (role)
        {
            case BSTU::NumRole:
                return m_cellsData[index.row()][BSTU::CellParams(BSTU::Number)];
            case BSTU::VoltRole:
                return (m_modelType == BSTU::VoltageType)
                    ? m_cellsData[index.row()][BSTU::CellParams(BSTU::Voltage)]
                    : QVariant();
            case BSTU::TempRole:
                return (m_modelType == BSTU::TemperatureType)
                    ? m_cellsData[index.row()][BSTU::CellParams(BSTU::Temperature)]
                    : QVariant();
            case BSTU::MinVoltRole:
                return (m_modelType == BSTU::VoltageType) ? m_minVal : QVariant();
            case BSTU::MaxVoltRole:
                return (m_modelType == BSTU::VoltageType) ? m_maxVal : QVariant();
            case BSTU::MinTempRole:
                return (m_modelType == BSTU::TemperatureType) ? m_minVal : QVariant();
            case BSTU::MaxTempRole:
                return (m_modelType == BSTU::TemperatureType) ? m_maxVal : QVariant();
            case BSTU::VoltRangeRole:
                return (m_modelType == BSTU::VoltageType) ? range() : QVariant();
            case BSTU::TempRangeRole:
                return (m_modelType == BSTU::TemperatureType) ? range() : QVariant();
            case BSTU::ModelTypeRole:
                return m_modelType;
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

float CellsDataModel::maxVal() const
{
    return m_maxVal;
}

float CellsDataModel::minVal() const
{
    return m_minVal;
}

void CellsDataModel::setMinVal(float val)
{
    m_minVal = val;
}
void CellsDataModel::setMaxVal(float val)
{
    m_maxVal = val;
}

float CellsDataModel::range() const
{
    float range = m_maxVal - m_minVal;
    Q_ASSERT(range > 0);
    return range;

}

void CellsDataModel::appendCell(float val)
{
    cellValues cellVal;
    int row = m_cellsData.count();
    if (m_modelType == BSTU::VoltageType)
        cellVal = {{BSTU::CellParams::Number, row + 1}, {BSTU::CellParams::Voltage, val}};
    else
        cellVal = {{BSTU::CellParams::Number, row + 1}, {BSTU::CellParams::Temperature, val}};

    beginInsertRows(QModelIndex(), row, row);
    m_cellsData.append(cellVal);
    endInsertRows();
}
