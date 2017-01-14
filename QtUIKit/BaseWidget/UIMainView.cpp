#include "UIMainView.h"

UIMainView::UIMainView(QWidget *parent) : AutoSizeWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground,true);
}

void UIMainView::isShadow(bool ifDrawShadow)
{
    m_ifDrawShadow = ifDrawShadow;
}

inline bool UIMainView::getifDrawShadow()
{
    return m_ifDrawShadow;
}

void UIMainView::paintEvent(QPaintEvent *event)
{
    if(getifDrawShadow() == true)
    {
        AutoSizeWidget::paintEvent(event);
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(9, 9, this->width()-18, this->height()-18);


        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(path, QBrush(Qt::white));


        QColor color(0, 0, 0, 50);
        for(int i=0; i<9; i++)
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRect(9-i, 9-i, this->width()-(9-i)*2, this->height()-(9-i)*2);
            color.setAlpha(150 - qSqrt(i)*60);
            painter.setPen(color);
            painter.drawPath(path);
        }
    }
}


