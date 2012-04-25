#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(QWidget *parent) :
    QWidget(parent)
{
    connect(this, SIGNAL(ready()), this, SLOT(showTryIcon()));
}

void SystemTrayIcon::setReady(const QList<QAction *> &actions, const QIcon &icon)
{
    _tryIcon = new QSystemTrayIcon;
    _tryIconMenu = new QMenu;

    _tryIconMenu->addActions(actions);
    _tryIcon->setContextMenu(_tryIconMenu);
    _tryIcon->setIcon(icon);
    emit ready();
}

void SystemTrayIcon::showTryIcon()
{
    _tryIcon->show();
}
