#include "CustomMainWidget.h"

CustomMainWidget::CustomMainWidget(QWidget *parent)
    : UIMainView(parent)
{

    this->Init(WinMessage);
    this->isShadow(true);

}

CustomMainWidget::~CustomMainWidget()
{

}
