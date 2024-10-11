#include "cellsdatamodel.h"
#include <QColor>
#include <QFont>

CellsDataModel::CellsDataModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

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
        case BSTU::Number:
            return QString::fromUtf8("Number");
        case BSTU::Voltage:
            return QString::fromUtf8("Voltage");

    }

    return QVariant();
}

QVariant CellsDataModel::data(const QModelIndex& index, int role) const
{
    QVariant value = m_cellsData[index.row()][BSTU::CellParams(index.column())];

    if (role == Qt::DisplayRole)
        return value;
    return QVariant();
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
    return Qt::red;
}
