/****************************************************************************************
** message.cpp is part of yoDownet
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

#include "message.h"
#include <QTimer>

Message::Message(QObject *parent) :
    QObject(parent), _messages(new QQueue<BaseMessage>)
{
}

Message::~Message()
{
    delete _messages;
    delete _checkQueue;
}

void Message::addMessage(const QString &title, const QString &message, const MessageConstants::Tag tag)
{
    BaseMessage baseMessage;
    baseMessage.setMessage(title, message, tag);

    _checkQueue = new QTimer(this);
    connect(_checkQueue, SIGNAL(timeout()), this, SLOT(showMessage()));
    _checkQueue->start(3000);

    _messages->enqueue(baseMessage);
}

void Message::setSysTrayIcon(SystemTrayIcon *sysTrayIcon)
{
    _sysTrayIcon = sysTrayIcon;
}

void Message::showMessage()
{
    if(_messages->count() > 0){
        QString messageTitle = _messages->first().title();
        QString messageBody = _messages->first().body();
        MessageConstants::Tag messageTag = _messages->first().tag();
        _messages->removeFirst();
        _sysTrayIcon->showMessage(messageTitle, messageBody, messageTag);
        if(_messages->count() == 0){
            disconnect(_checkQueue, SIGNAL(timeout()), this, SLOT(showMessage()));
            _checkQueue = 0;
        }
    }
}
