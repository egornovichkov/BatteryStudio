#ifndef CELLSDATAMODEL_H
#define CELLSDATAMODEL_H

#include <QAbstractTableModel>

class CellsDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    /// Enumeration for cell parameters names.
    enum CellParams
    {
        // Params must be equal to int numbers from 0 to parameters count in order
        Number = 0,
        Voltage = 1,
        Minimum = 2,
        Maximum = 3,
        Color = 4,
        CELLPARAMSCOUNT // Do not insert any params after this
    };

    explicit CellsDataModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void appendCell(int, float, float, float);
    // Qt::ItemFlags flags(const QModelIndex& index) const override;

    float maxVoltage(void) const;
    float minVoltage(void) const;

private:    
    /// QHash holds cell parameter name as a key and parameter value as value.
    typedef QHash<CellParams, QVariant> cellValues;
    /// List holds cell data for all cells.
    typedef QList<cellValues> cellsData;
    cellsData m_cellsData;

    /// Min/Max voltages are for correct display of voltage bar and color of cell backrgound.
    /// Minimum voltage (default = 0).
    float m_minVoltage = 0;
    /// Maximum voltage.
    float m_maxVoltage;
};

#endif // CELLSDATAMODEL_H
