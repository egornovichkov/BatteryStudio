#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AppWidget;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    // bool virtual eventFilter(QObject *obj, QEvent *event) override;
    /// Handler for the mouse move event.
    void mouseMoveEvent(QMouseEvent *event) override;

    /// Handler for the mouse press event.
    void mousePressEvent(QMouseEvent *event) override;
    /// Handler for the mouse release event.
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

private:
    /// Function which returns mouse type due to its position within the window.
    // bool checkResizableField(QMouseEvent *event);

private:
    /// Pointer to the user interface object.
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
