/****************************************************************************************
** ratecontroller.h is part of yoDownet
**
** Copyright 2014 Alireza Savand <alireza.savand@gmail.com>
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

#ifndef RATECONTROLLER_H
#define RATECONTROLLER_H

#include <QObject>
#include <QtCore/QTime>
#include "downloader/ratecontrollertcpsocket.h"

class RateController : public QObject
{
    Q_OBJECT
public:
    explicit RateController(QObject *parent = 0)
        : QObject(parent), transferScheduled(false) {}

    void addSocket(RateControllerTcpSocket *socket);
    void removeSocket(RateControllerTcpSocket *socket);

    int uploadLimit() const;
    int downloadLimit() const;
    void setUploadLimit(int bytesPerSecond);
    void setDownloadLimit(int bytesPerSecond);
};

#endif // RATECONTROLLER_H
