#ifndef CELLSDATAMODEL_H
#define CELLSDATAMODEL_H

#include <QAbstractTableModel>

class CellsDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum CellParams
    {
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

    typedef QHash<CellParams, QVariant> cellValues;
    typedef QList<cellValues> cellsData;
    cellsData m_cellsData;
};

#endif // CELLSDATAMODEL_H
