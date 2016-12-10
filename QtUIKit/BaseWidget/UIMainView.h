#ifndef UIMAINVIEW_H
#define UIMAINVIEW_H

#include <QWidget>
#include "BaseWidget/AutoSizeWidget.h"
class UIMainView : public AutoSizeWidget
{
    Q_OBJECT
public:
    explicit UIMainView(QWidget *parent = 0);
    void isShadow(bool ifDrawShadow);
protected:
     void paintEvent(QPaintEvent *event);
private:
     inline bool getifDrawShadow();

     bool m_ifDrawShadow;
signals:

public slots:
};

#endif // UIMAINVIEW_H
