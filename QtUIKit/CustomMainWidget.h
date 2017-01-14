#ifndef CUSTOMMAINWIDGET_H
#define CUSTOMMAINWIDGET_H

#include <QWidget>
#include "BaseWidget/UIMainView.h"
#include "BaseWidget/BaseMenu/BaseMenu.h"
#include <QContextMenuEvent>
class CustomMainWidget : public UIMainView
{
    Q_OBJECT

public:
    CustomMainWidget(QWidget *parent = 0);
    ~CustomMainWidget();

    void contextMenuEvent(QContextMenuEvent *);


    BaseMenu *m_Menu;
};

#endif // CUSTOMMAINWIDGET_H
