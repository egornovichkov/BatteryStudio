#ifndef CELLSTABLEPROXYMODEL_H
#define CELLSTABLEPROXYMODEL_H

#include <QAbstractProxyModel>

class CellsTableProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    CellsTableProxyModel(QAbstractProxyModel* parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    // bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;

private slots:
    void setCellsPerRow(int val);

private:
    /// Function matches color of cell background to voltage value.
    QColor valToColor(float val) const;

    QAbstractTableModel *m_model;
    int m_cellsPerRow = 25;
    int m_cellsCount;
};

#endif // CELLSTABLEPROXYMODEL_H
