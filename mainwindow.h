#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "batchargeimg.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    BatChargeImg *BatteryCharge;
};
#endif // MAINWINDOW_H
