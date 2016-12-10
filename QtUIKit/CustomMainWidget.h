#ifndef CUSTOMMAINWIDGET_H
#define CUSTOMMAINWIDGET_H

#include <QWidget>
#include "BaseWidget/UIMainView.h"
class CustomMainWidget : public UIMainView
{
    Q_OBJECT

public:
    CustomMainWidget(QWidget *parent = 0);
    ~CustomMainWidget();
};

#endif // CUSTOMMAINWIDGET_H
