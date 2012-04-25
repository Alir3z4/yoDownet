#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(QWidget *parent) :
    QWidget(parent)
{
    _tryIcon = new QSystemTrayIcon;

    connect(this, SIGNAL(ready()), _tryIcon, SLOT(show()));

void SystemTrayIcon::setReady(QMenu *menu, const QIcon &icon)
{
    _tryIcon->setContextMenu(menu);
    _tryIcon->setIcon(icon);
    emit ready();
}

{
}
