/****************************************************************************************
** systemtrayicon.cpp is part of yoDownet
**
** Copyright 2012 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

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
