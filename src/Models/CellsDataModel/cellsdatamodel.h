#ifndef CELLSDATAMODEL_H
#define CELLSDATAMODEL_H

#include <QAbstractTableModel>

class CellsDataModel : public QAbstractTableModel
{
public:
    explicit CellsDataModel(QObject *parent = nullptr);
};

#endif // CELLSDATAMODEL_H
