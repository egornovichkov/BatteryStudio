#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>

class QWidget;
class TitleBar;

class AppWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppWidget(QWidget *parent = nullptr);
    ~AppWidget();

    QPoint previousPosition() const;

protected:
    /// Handler for the mouse press event.
    void mousePressEvent(QMouseEvent *event) override;
    /// Handler for the mouse move event within the window.
    void mouseMoveEvent(QMouseEvent *event) override;
    /// Handler for the mouse release event within the window.
    void mouseReleaseEvent(QMouseEvent *event) override;
    /// Handler for the mouse double-click event within the window.
    // void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:
    /// Handler for the "Close" button click signal.
    void closeApp();
    /// Handler for the "Maximize/Restore" button click signal.
    void maximizeApp();
    /// Handler for the "Minimize" button click signal.
    void minimizeApp();

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

    QWidget *m_mainWindow;
    TitleBar *m_titleBar;
    /// Mouse pressed variable
    MouseType m_leftMouseButtonPressed;
    /// Window mPosition on the screen.
    QPoint mPosition;

signals:
    void previousPositionChanged(QPoint);
};

#endif // APPWIDGET_H
