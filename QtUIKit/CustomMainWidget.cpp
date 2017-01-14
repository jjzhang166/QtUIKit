#include "CustomMainWidget.h"
#include <QDebug>
#include <QPushButton>
CustomMainWidget::CustomMainWidget(QWidget *parent)
    : UIMainView(parent)
{

    this->Init(WinMessage);
    this->isShadow(true);
    m_Menu = new BaseMenu();
    QAction *openFileAction = new QAction();
    openFileAction->setText("打开文件");
    m_Menu->addAction(openFileAction);
    QAction *closeVideoPlayerViewAction = new QAction();
    closeVideoPlayerViewAction->setText("退出");
    m_Menu->addAction(closeVideoPlayerViewAction);
    QAction *helpAction = new QAction();
    helpAction->setText("帮助");
    m_Menu->addAction(helpAction);

}

CustomMainWidget::~CustomMainWidget()
{

}

void CustomMainWidget::contextMenuEvent(QContextMenuEvent *)
{
    m_Menu->exec(QCursor::pos());
    qDebug()<< "emit";
}
