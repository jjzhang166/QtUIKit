#ifndef AUTOSIZEWIDGET_H
#define AUTOSIZEWIDGET_H

#include <QWidget>
#include "ImportHeaderFile.h"

enum CursorPos
{
    Default,
    Right,
    Left,
    Bottom,
    Top,
    TopRight,
    TopLeft,
    BottomRight,
    BottomLeft
};
enum AutoSizeMethod
{
    WinMessage,
    CrossPlatform
};

struct pressWindowsState
{
    bool    MousePressed;
    bool    IsPressBorder;
    QPoint  MousePos;
    QPoint  WindowPos;
    QSize   PressedSize;
};
class AutoSizeWidget : public QWidget
{
    Q_OBJECT
public:
    AutoSizeWidget(QWidget *parent = 0);
    void Init(AutoSizeMethod HowToAutoSize);
    inline void setBorder(int border);
    void mouseMoveRect(const QPoint &p);
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    int m_Border;
    pressWindowsState m_State;
    CursorPos m_CursorPos;
    AutoSizeMethod m_AutoSizeMethod;
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};

#endif // AUTOSIZEWIDGET_H
