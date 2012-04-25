#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(QWidget *parent) :
    QWidget(parent)
{
    _tryIcon = new QSystemTrayIcon;

    connect(this, SIGNAL(ready()), _tryIcon, SLOT(show()));
    connect(_tryIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void SystemTrayIcon::setReady(QMenu *menu, const QIcon &icon)
{
    _tryIcon->setContextMenu(menu);
    _tryIcon->setIcon(icon);
    emit ready();
}

void SystemTrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
        case QSystemTrayIcon::Trigger:
            emit triggered();
            break;
        case QSystemTrayIcon::DoubleClick:
            emit doubleClicked();
            break;
        case QSystemTrayIcon::MiddleClick:
            emit middleClicked();
            break;
        default:
            ;
    }
}
