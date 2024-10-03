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


protected:
    bool event(QEvent *event) override;

private:
    /// Function which sets title bar.
    void installWindowAgent();
    void setTitleBarStyleSheet();

private:
    /// Pointer to the user interface object.
    Ui::MainWindow *ui;
    /// Pointer to window agent.
    QWK::WidgetWindowAgent *m_widgetWindowAgent;
};
#endif // MAINWINDOW_H
