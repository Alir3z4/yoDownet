/****************************************************************************************
** urlvalidator.cpp is part of yoDownet
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

#include "urlvalidator.h"
#include "plus/messages/constants.h"
#include <QUrl>

UrlValidator::UrlValidator(QObject *parent, const QString &url) :
    BaseValidator(parent)
{
    if(!url.isNull()) setInput(url);
}

void UrlValidator::setUrl(const QString &url)
{
    _input = QUrl(url).toEncoded();
}

bool UrlValidator::isValid()
{
    return QUrl(_input).isValid();
}

MessageConstants::Tag UrlValidator::errorTag() const
{
    return MessageConstants::Critial;
}

QString UrlValidator::errorTitle() const
{
    return tr("Invalid Url");
}

QString UrlValidator::errorMessage() const
{
    if(!_input.isEmpty())
        return tr("%1 is not a valid Url.")
                .arg(_input);
    return QString("");
}
