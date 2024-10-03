#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>

class MainWindow;

namespace Ui
{
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(MainWindow *parent = nullptr);
    /// Function for initialization frame icons.
    // void initIcons();
    /// Function for showing header menu.
    // void showHeaderContextMenu(const QPoint &pos);

    // ~TitleBar();

protected:
    /// Handler for the mouse double-click event within the window.
    // void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    /// Signal of "Close" button click.
    // void onCloseClickedSignal();
    /// Signal of "Maximize/Restore" button click.
    // void onMaximumClickedSignal();
    /// Signal of "Minimize" button click.
    // void onMinimumClickedSignal();

private slots:
    /// Handler for the "Close" button click signal.
    // void onCloseClicked();
    /// Handler for the "Maximize/Restore" button click signal.
    // void onMaximumClicked();
    /// Handler for the "Minimize" button click signal.
    // void onMinimumClicked();
public:
    /// Pointer to the user interface object.
    // Ui::TitleBar *ui;
    /// Pointer to main window
    MainWindow *m_mainWindow;
private:
    /// Size of the window borders for resize.
    int mBorderSize;
    /// Collapse flag.
    bool mIsCollapse;
    /// Flag for current appwidget state ("maximized/not maximized")
    bool m_MaximizedFlag;
};

#endif // TITLEBAR_H
