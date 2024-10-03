#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TitleBar;

namespace QWK
{
class WidgetWindowAgent;
}

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

    /// Getter for pointer to internal widget window agent.
    QWK::WidgetWindowAgent *windowAgent();

protected:
    bool event(QEvent *event) override;

private:
    /// Function which returns mouse type due to its position within the window.
    // bool checkResizableField(QMouseEvent *event);
    /// Function which sets title bar.
    void installWindowAgent();

private:
    /// Pointer to the user interface object.
    Ui::MainWindow *ui;
    /// Pointer to title bar
    // TitleBar *m_titleBar;
    /// Pointer to window agent.
    QWK::WidgetWindowAgent *m_widgetWindowAgent;
};
#endif // MAINWINDOW_H
