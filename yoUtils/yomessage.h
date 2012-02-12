/****************************************************************************************
** yomessage.h is part of yoDownet
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

#ifndef YOMESSAGE_H
#define YOMESSAGE_H

#include <QtGui/QMessageBox>
class QString;

class yoMessage : public QMessageBox
{
    Q_OBJECT
public:
    //explicit yoMessage(QObject *parent = 0);
    void dbError(const QString dbErrorText, const QString action);
    void userError(const QString detailsText);
    void notify(const QString &notif);
    int ask(const QString argQuestionTitle, const QString argQuestionBody);

};

#endif // YOMESSAGE_H
