/****************************************************************************************
** yomessage.cpp is part of yoDownet
**
** Copyright 2011, 2012 Alireza Savand <alireza.savand@gmail.com>
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

#include "yomessage.h"

void yoMessage::dbError(const QString dbErrorText, const QString action)
{
    critical(0, tr("yoDownet : Database error"),
                          tr("Whoops, we have little error from database on <b>%1</b>.<br />"
                             "See the details below:<br />%2").arg(action, dbErrorText),
                          Ok);
}

void yoMessage::userError(const QString detailsText)
{
    critical(0, tr("yoDownet : Watch out"), QString("%1").arg(detailsText), Ok);
}

void yoMessage::notify(const QString &notif)
{
    information(0, tr("yoDownet : Just for information sake ;)"),
                notif, Ok);
}

int yoMessage::ask(const QString argQuestionTitle, const QString argQuestionBody)
{
    StandardButton ask;
    ask = question(0, tr("yoDownet : %1").arg(argQuestionTitle),
                                           argQuestionBody,
                                           Yes | No);
    return ask;
}
