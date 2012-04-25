#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(QWidget *parent) :
    QWidget(parent)
{
    connect(this, SIGNAL(ready()), this, SLOT(showTryIcon()));
}

void SystemTrayIcon::setReady(QMenu *menu, const QIcon &icon)
{
    _tryIcon = new QSystemTrayIcon;

    _tryIcon->setContextMenu(menu);
    _tryIcon->setIcon(icon);
    emit ready();
}

void SystemTrayIcon::showTryIcon()
{
    _tryIcon->show();
}
