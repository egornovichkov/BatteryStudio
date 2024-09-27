#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>

namespace Ui
{
class TitleBar;
}

class TitleBar : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(QPoint previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)
public:
    explicit TitleBar(QWidget *parent = nullptr, QWidget *child = nullptr);
    /// Init frame icons
    void initIcons();
    /// Show header menu.
    void showHeaderContextMenu(const QPoint &pos);
    /// Show or hide the window minimization button.
    void enableMinimum(bool enable);
    /// Show or hide the window maximization button.
    void enableMaximum(bool enable);
    /// Show or hide the window close button.
    void enableClose(bool enable);
    /// Returns previous mouse position
    QPoint previousPosition() const;

    ~TitleBar();

protected:
    /// Handler for the mouse press event.
    void mousePressEvent(QMouseEvent *event) override;
    /// Handler for the mouse move event within the window.
    void mouseMoveEvent(QMouseEvent *event) override;
    /// Handler for the mouse release event within the window.
    void mouseReleaseEvent(QMouseEvent *event) override;
    /// Handler for the mouse double-click event within the window.
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    bool eventFilter(QObject *obj, QEvent *event) override;

    virtual void paintEvent(QPaintEvent*) override;

private:
    /// Mouse type enumeration
    enum class MouseType
    {
        None = 0,
        Top = 1,
        Bottom = 2,
        Left = 3,
        Right = 4,
        Move = 5
    };
    /// Returnes mouse type
    MouseType checkResizableField(QMouseEvent *event);
    /// Sets previous mouse position
    void setPreviousPosition(QPoint previousPosition);

signals:
    void previousPositionChanged(QPoint previousPosition);

private slots:
    /// Handler for the "Close" button click signal.
    void onCloseClicked();
    /// Handler for the "Maximize/Restore" button click signal.
    void onMaximumClicked();
    /// Handler for the "Minimize" button click signal.
    void onMinimumClicked();
    /// Handler for the "Collapse" button click signal.
    void onCollapseClicked();

private:
    /// Pointer to the user interface object.
    Ui::TitleBar *ui;
    /// Pointer to the main widget (child widget).
    QWidget *mMainBody;
    /// Window mPosition on the screen.
    QPoint mPosition;
    /// Size of the window borders for resize.
    int mBorderSize;
    /// Collapse flag.
    bool mIsCollapse;
    /// Mouse pressed variable
    MouseType m_leftMouseButtonPressed;
};

#endif // TITLEBAR_H
