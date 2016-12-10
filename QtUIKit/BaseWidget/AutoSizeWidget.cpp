#include "AutoSizeWidget.h"

AutoSizeWidget::AutoSizeWidget(QWidget *parent)
    : QWidget(parent)
{
    Init(WinMessage);
}

void AutoSizeWidget::Init(AutoSizeMethod HowToAutoSize)
{
    if(HowToAutoSize == WinMessage)
    {
        m_State.MousePressed = false;
        m_State.IsPressBorder = false;
        m_Border = 4;
        this->setMouseTracking(true);
        this->setWindowFlags(Qt::FramelessWindowHint);
        setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    }else if(HowToAutoSize == CrossPlatform)
    {
        this->setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint);
        HWND hwnd = (HWND)this->winId();
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    }
}
void AutoSizeWidget::setBorder(int border)
{
    m_Border = border;
}

void AutoSizeWidget::mouseMoveRect(const QPoint& p)
{
    if(!m_State.IsPressBorder)
    {
        if(p.x() >  (width() - m_Border) && p.y() < height() - m_Border && p.y() > m_Border)
        {
            setCursor(Qt::SizeHorCursor);
            m_CursorPos = CursorPos::Right;
        }
        else if(p.x() < m_Border && p.y() < (height() - m_Border) && p.y() > m_Border)
        {
            setCursor(Qt::SizeHorCursor);
            m_CursorPos = CursorPos::Left;
        }
        else if(p.y() > (height() - m_Border) && p.x() > m_Border && p.x() < (width() - m_Border))
        {
            setCursor(Qt::SizeVerCursor);
            m_CursorPos = CursorPos::Bottom;
        }
        else if(p.y() < m_Border && p.x() > m_Border && p.x() < (width() - m_Border))
        {
            setCursor(Qt::SizeVerCursor);
            m_CursorPos = CursorPos::Top;
        }
        else if(p.y() < m_Border && p.x() > (width() - m_Border))
        {
            setCursor(Qt::SizeBDiagCursor);
            m_CursorPos = CursorPos::TopRight;
        }

        else if(p.y() < m_Border && p.x() < m_Border)
        {
            setCursor(Qt::SizeFDiagCursor);
            m_CursorPos = CursorPos::TopLeft;
        }

        else if(p.x() > m_Border && p.y() > (height() - m_Border))
        {
            setCursor(Qt::SizeFDiagCursor);
            m_CursorPos = CursorPos::BottomRight;
        }

        else if(p.x() < m_Border && p.y() > (height() - m_Border))
        {
            setCursor(Qt::SizeBDiagCursor);
            m_CursorPos = CursorPos::BottomLeft;
        }
        else
        {
            m_CursorPos = CursorPos::Default;
            setCursor(Qt::ArrowCursor);
        }
    }
    else
    {
        switch(m_CursorPos) {
        case CursorPos::Right:
        {
           int setW = QCursor::pos().x() - x();
           if(minimumWidth() <= setW && setW <= maximumWidth())
             setGeometry(x(), y(), setW, height());
            break;
        }
        case CursorPos::Left:
        {
            int setW = x() + width() - QCursor::pos().x();
            int setX = QCursor::pos().x();
            if(minimumWidth() <= setW && setW <= maximumWidth())
              setGeometry(setX, y(), setW, height());
             break;
        }
        case CursorPos::Bottom:
        {
            int setH = QCursor::pos().y() - y();
            if(minimumHeight() <= setH && setH <= maximumHeight())
            setGeometry(x(), y(), width(), setH);
            break;
        }
        case CursorPos::Top:
        {
           int setH = y() - QCursor::pos().y() + height();
           if(minimumHeight() <= setH && setH <= maximumHeight())
             setGeometry(x(), QCursor::pos().y(), width(), setH);
             break;
        }
        case CursorPos::TopRight:
        {
            int setH = y() + height() - QCursor::pos().y();
            int setW = QCursor::pos().x() - x();
            int setY = QCursor::pos().y();
            if(setH >= maximumHeight())
            {
                setY =m_State.WindowPos.y() + m_State.PressedSize.height() - height();
                setH = maximumHeight();
            }
            if(setH <= minimumHeight())
            {
                setY = m_State.WindowPos.y() + m_State.PressedSize.height() - height();
                setH = minimumHeight();
            }
            setGeometry(m_State.WindowPos.x(), setY, setW, setH);
            break;
        }
        case CursorPos::TopLeft:
        {
            int setY = QCursor::pos().y();
            int setX = QCursor::pos().x();

            int setW = pos().x() + width() - setX;
            int setH = pos().y() + height() - setY;
            int totalW = m_State.WindowPos.x()  + m_State.PressedSize.width();
            int totalH = m_State.WindowPos.y() + m_State.PressedSize.height();

            if((totalW - setX) >= maximumWidth())
            {
                setX = totalW - maximumWidth();
                setW = maximumWidth();
            }
            if((totalW - setX) <= minimumWidth())
            {
                setX = totalW-minimumWidth();
                setW = minimumWidth();
            }
            if((totalH - setY) >= maximumHeight())
            {
                setY = totalH - maximumHeight();
                setH = maximumHeight();
            }
            if((totalH - setY) <= minimumHeight())
            {
                setY = totalH - minimumHeight();
                setH = minimumHeight();
            }
            setGeometry(setX, setY, setW, setH);
            break;
        }
        case CursorPos::BottomRight:
        {
            int setW = QCursor::pos().x() - x();
            int setH = QCursor::pos().y() - y();
            setGeometry(m_State.WindowPos.x(), m_State.WindowPos.y(), setW, setH);
            break;
        }
        case CursorPos::BottomLeft:
        {
            int setW = x() + width() - QCursor::pos().x();
            int setH = QCursor::pos().y() - m_State.WindowPos.y();
            int setX = QCursor::pos().x();
            int totalW= m_State.WindowPos.x() + m_State.PressedSize.width();
            if((totalW-setX) >= maximumWidth())
            {
                setX = totalW - maximumWidth();
                setW = maximumWidth();
            }
            if((totalW - setX) <= minimumWidth())
            {
                setX = totalW-minimumWidth();
                setW = minimumWidth();
            }
            setGeometry(setX, m_State.WindowPos.y(), setW, setH);
            break;
        }
        case CursorPos::Default:
        default:
            break;
        }
    }
}
void AutoSizeWidget::mousePressEvent(QMouseEvent *event)
{
    m_State.PressedSize = this->size();
    m_State.IsPressBorder = false;
    this->setFocus();
    if (event->button() == Qt::LeftButton)
    {
        m_State.WindowPos = this->pos();
        if(QRect(m_Border + 1, m_Border + 1, width()-(m_Border + 1)*2, height()-(m_Border + 1)*2).contains(QPoint(event->globalX() - x(),event->globalY() - y())))
        {
            m_State.MousePos = event->globalPos();
            m_State.MousePressed = true;
        }
        else
            m_State.IsPressBorder = true;
    }
}
void AutoSizeWidget::mouseMoveEvent(QMouseEvent *event)
{
    mouseMoveRect(mapFromGlobal(event->globalPos()));
    if (m_State.MousePressed)
    {
        this->move(m_State.WindowPos + (event->globalPos() - m_State.MousePos));
    }
}
void AutoSizeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_State.IsPressBorder = false;
    if(event->button() == Qt::LeftButton)
    {
        this->m_State.MousePressed = false;
    }
    setCursor(Qt::ArrowCursor);
}
bool AutoSizeWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    MSG* msg = reinterpret_cast<MSG*>(message);

    int xPos = 0, yPos = 0;
    switch(msg->message)
    {
    case WM_NCHITTEST:
        xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
        if(this->childAt(xPos,yPos) == 0)
        {
            *result = HTCAPTION;
        }else{
            return false;
        }
        if(xPos > 0 && xPos < 5)
            *result = HTLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0))
            *result = HTRIGHT;
        if(yPos > 0 && yPos < 5)
            *result = HTTOP;
        if(yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOM;
        if(xPos > 0 && xPos < 5 && yPos > 0 && yPos < 5)
            *result = HTTOPLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0) && yPos > 0 && yPos < 5)
            *result = HTTOPRIGHT;
        if(xPos > 0 && xPos < 5 && yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOMLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0) && yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOMRIGHT;

        return true;
        break;

    case WM_GETMINMAXINFO:
        if (::IsZoomed(msg->hwnd)) {

            RECT frame = { 0, 0, 0, 0 };
            AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
            frame.left = abs(frame.left);
            frame.top = abs(frame.bottom);
            this->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
        }
        else {
            this->setContentsMargins(0, 0, 0, 0);
        }

        *result = ::DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
        break;

    case WM_NCCALCSIZE:
        return true;
        break;
    default:
        return false;
    }
}
