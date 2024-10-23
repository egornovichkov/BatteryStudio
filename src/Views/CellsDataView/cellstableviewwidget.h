#ifndef CELLSTABLEVIEWWIDGET_H
#define CELLSTABLEVIEWWIDGET_H

#include <QTableWidget>


class CellsTableViewWidget : public QTableView
{
    Q_OBJECT
public:
    CellsTableViewWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e) override;
};

#endif // CELLSTABLEVIEWWIDGET_H
