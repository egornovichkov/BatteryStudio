#ifndef CELLSDATAMODEL_H
#define CELLSDATAMODEL_H

#include <QAbstractTableModel>
#include "./src/bstunamespace.h"

class CellsDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CellsDataModel(BSTU::CellsModel modelType, QObject *parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;


    void appendCell(float);
    // Qt::ItemFlags flags(const QModelIndex& index) const override;

    void setMinVal(float);
    void setMaxVal(float);

    float maxVal(void) const;
    float minVal(void) const;

    float range(void) const;

private:
    /// Function matches color of cell background to voltage value.
    QColor valToColor(float val) const;

    /// QHash holds cell parameter name as a key and parameter value as value.
    typedef QHash<BSTU::CellParams, QVariant> cellValues;
    /// List holds cell data for all cells.
    typedef QList<cellValues> cellsData;

    BSTU::CellsModel m_modelType;
    cellsData m_cellsData;

    /// Min/Max voltages are for correct display of voltage bar and color of cell backrgound.
    /// Minimum voltage (default = 0).
    float m_minVal = 0;
    /// Maximum voltage.
    float m_maxVal;
};

#endif // CELLSDATAMODEL_H
