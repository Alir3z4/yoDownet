/****************************************************************************************
** basemessage.h is part of yoDownet
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

#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H

#include <QString>
#include "plus/messages/constants.h"

class BaseMessage
{
public:
    explicit BaseMessage();

    void setTitle(const QString &title);
    QString title() const;

    void setBody(const QString &message);
    QString body() const;

    void setMessage(const QString &title, const QString &message, const MessageConstants::Tag &tag);

    void setTag(const MessageConstants::Tag &tag);
    MessageConstants::Tag tag() const;

private:
    QString _title;
    QString _message;
    MessageConstants::Tag _tag;
};

#endif // BASEMESSAGE_H
