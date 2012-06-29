/****************************************************************************************
** message.h is part of yoDownet
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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QQueue>
#include "plus/messages/basemessage.h"
#include "ui/widget/systemtrayicon.h"

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = 0);
    ~Message();

    void addMessage(const QString &title, const QString &message, const MessageConstants::Tag tag);
    void setSysTrayIcon(SystemTrayIcon *sysTrayIcon);

private slots:
    virtual void showMessage();

private:
    QQueue<BaseMessage> *_messages;
    SystemTrayIcon *_sysTrayIcon;
    QTimer *_checkQueue;
};

#endif // MESSAGE_H
