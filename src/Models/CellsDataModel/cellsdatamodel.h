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
        CELLPARAMSCOUNT // Do not insert any params after this
    };

    explicit CellsDataModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    // Qt::ItemFlags flags(const QModelIndex& index) const override;

private:    
    /// QHash holds cell parameter name as a key and parameter value as value.
    typedef QHash<CellParams, QVariant> cellValues;
    /// List holds cell data for all cells.
    typedef QList<cellValues> cellsData;
    cellsData m_cellsData;
};

#endif // CELLSDATAMODEL_H
