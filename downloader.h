/****************************************************************************************
** downloader.h is part of yoDownet
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
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include "yoDownloaders/aria2c.h"
#include "yoUtils/yodatabase.h"

class Downloader : public Aria2c
{
    Q_OBJECT

public:
    explicit Downloader();
    ~Downloader();

public slots:
    void resume(const QString &uri);
    void askForStartAria();
    void askForRefreshStatus(const QString &gid);

signals:
    void uriUpdatedOnDb(const Status *status);
    void uriAddedToDb(const QString &gid);
    void uriAddedToDb(const QVariantMap &uri);
    void statusAsked(const Status *status);

private slots:
    void askForStatus(const QVariant &gid);
    void addUriToDb(const Status *status);
    void updateUriToDb(const Status *status);

private:

};

#endif // DOWNLOADER_H
