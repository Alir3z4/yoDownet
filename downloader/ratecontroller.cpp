/****************************************************************************************
** ratecontroller.cpp is part of yoDownet
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

#include "ratecontroller.h"
#include <QtCore/QTimer>


void RateController::addSocket(RateControllerTcpSocket *socket)
{
    connect(socket, SIGNAL(readyToTransfer()), this, SLOT(transfer()));

    socket->setReadBufferSize(downLimit * 2);
    sockets.insert(socket);

    scheduleTransfer();
}

void RateController::removeSocket(RateControllerTcpSocket *socket)
{
    disconnect(socket, SIGNAL(readyToTransfer()), this, SLOT(transfer()));

    socket->setReadBufferSize(0);
    sockets.remove(socket);
}

int RateController::uploadLimit() const
{
    return upLimit;
}

int RateController::downloadLimit() const
{
    return downLimit;
}

void RateController::setUploadLimit(int bytesPerSecond)
{
    upLimit = bytesPerSecond;
}

void RateController::setDownloadLimit(int bytesPerSecond)
{
    downLimit = bytesPerSecond;

    foreach (RateControllerTcpSocket *socket, sockets) {
        socket->setReadBufferSize(downLimit * 2);
    }
}

void RateController::scheduleTransfer()
{
    if (transferScheduled) {
        return;
    }

    transferScheduled = true;

    QTimer::singleShot(50, this, SLOT(transfer()));
}
