#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(QWidget *parent) :
    QWidget(parent)
{
    _trayIcon = new QSystemTrayIcon(this);

    connect(this, SIGNAL(ready()), _trayIcon, SLOT(show()));
    connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void SystemTrayIcon::setReady(QMenu *menu, const QIcon &icon)
{
    _trayIcon->setContextMenu(menu);
    _trayIcon->setIcon(icon);
    emit ready();
}

void SystemTrayIcon::showMessage(const QString &title, const QString &msg, MessageConstants::Tag icon, int msec)
{
    QSystemTrayIcon::MessageIcon messageId = QSystemTrayIcon::Information;
    switch(icon){
    case MessageConstants::Critial:
        messageId = QSystemTrayIcon::Critical;
        break;
    case MessageConstants::Info:
        messageId = QSystemTrayIcon::Information;
        break;
    case MessageConstants::Warning:
        messageId = QSystemTrayIcon::Warning;
        break;
    case MessageConstants::Success:
        messageId = QSystemTrayIcon::Information;
        break;
    default:
        return;
    }

    _trayIcon->showMessage(title, msg, messageId, msec);
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
