#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>

class TitleBar;
class MainWindow;

class AppWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppWidget(QWidget *parent = nullptr);
    ~AppWidget();

    /// Getter for previous mouse position within the window.
    QPoint previousPosition() const;

public slots:
    /// Handler for the "Close" button click signal.
    void closeApp();
    /// Handler for the "Maximize/Restore" button click signal.
    void maximizeApp();
    /// Handler for the "Minimize" button click signal.
    void minimizeApp();

protected:
    /// Handler for the mouse press event.
    void mousePressEvent(QMouseEvent *event) override;
    /// Handler for the mouse move event.
    void mouseMoveEvent(QMouseEvent *event) override;
    /// Handler for the mouse release event.
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    /// Enumeration for mouse type.
    enum class MouseType
    {
        None = 0,
        Top = 1,
        Bottom = 2,
        Left = 3,
        Right = 4,
        Move = 5
    };
    /// Function which returns mouse type due to its position within the window.
    MouseType checkResizableField(QMouseEvent *event);
    /// Setter for previous mouse position within the window.
    void setPreviousPosition(QPoint previousPosition);

private:
    /// App body.
    MainWindow *m_mainWindow;
    /// App title bar.
    TitleBar *m_titleBar;
    /// Mouse pressed variable.
    MouseType m_leftMouseButtonPressed;
    /// Previous mouse position within the window.
    QPoint m_Position;

signals:
    void previousPositionChanged(QPoint);
};

#endif // APPWIDGET_H
