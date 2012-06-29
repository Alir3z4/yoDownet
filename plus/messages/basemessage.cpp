/****************************************************************************************
** basemessage.cpp is part of yoDownet
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

#include "basemessage.h"

BaseMessage::BaseMessage()
{
    return;
}

void BaseMessage::setTitle(const QString &title)
{
    _title = title;
}

QString BaseMessage::title() const
{
    return _title;
}

void BaseMessage::setBody(const QString &message)
{
    _message = message;
}

void BaseMessage::setMessage(const QString &title, const QString &message, const MessageConstants::Tag &tag)
{
    _title = title;
    _message = message;
    _tag = tag;
}

void BaseMessage::setTag(const MessageConstants::Tag &tag)
{
    _tag = tag;
}

MessageConstants::Tag BaseMessage::tag() const
{
    return _tag;
}

QString BaseMessage::body() const
{
    return _message;
}

