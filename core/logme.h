/****************************************************************************************
** logme.h is part of yoDownet
**
** Copyright 2013 Alireza Savand <alireza.savand@gmail.com>
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

#ifndef LOGME_H
#define LOGME_H

#include <QObject>

class LogMe : public QObject
{
    Q_OBJECT
public:
    explicit LogMe(QObject *parent = 0);

    void debug(const QString &debugMessage);
    void info(const QString &infoMessage);
    void success(const QString &successMessage);
    void error(const QString &errorMessage);

    void setClassName(const QString &className);

private:
    QString _className;

    void logMessage(const QString &logLevel, const QString &logMessage) const;
};

#endif // LOGME_H
