#ifndef CELLSTABLEPROXYMODEL_H
#define CELLSTABLEPROXYMODEL_H

#include <QAbstractProxyModel>

class CellsTableProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    CellsTableProxyModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    // bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    // QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;

private slots:
    void setCellsPerRow(int val);

private:
    /// Function matches color of cell background to voltage value.
    QColor valToColor(float val) const;

    QAbstractTableModel *m_model;
    int m_cellsPerRow = 10;
    int m_cellsCount;
};

#endif // CELLSTABLEPROXYMODEL_H
