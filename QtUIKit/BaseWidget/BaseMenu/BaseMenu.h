#ifndef BASEMENU_H
#define BASEMENU_H

#include <QWidget>
#include <QMenu>
#include <QAction>
class BaseMenu : public QMenu
{
    Q_OBJECT
public:
    explicit BaseMenu(QWidget *parent = 0);

signals:

public slots:
};

#endif // BASEMENU_H
