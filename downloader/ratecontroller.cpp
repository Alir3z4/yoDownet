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

void RateController::transfer()
{
    transferScheduled = false;
    int msecs = 1000;

    if (!stopWatch.isNull()) {
        msecs = qMin(msecs, stopWatch.elapsed());
    }

    qint64 bytesToWrite = (upLimit * msecs) / 1000;
    qint64 bytesToRead = (downLimit * msecs) / 1000;

    if (bytesToWrite == 0 && bytesToRead == 0) {
        scheduleTransfer();
        return;
    }

    QSet<RateControllerTcpSocket *> pendingSockets;
    foreach (RateControllerTcpSocket *client, sockets) {
        if (client->canTransferMore()) {
            pendingSockets.insert(client);
        }
    }

    if (pendingSockets.isEmpty()) {
        return;
    }

    stopWatch.start();

    bool canTransferMore;

    do {
        canTransferMore = false;
        qint64 writeChunk = qMax<qint64>(1, bytesToWrite / pendingSockets.size());
        qint64 readChunk = qMax<qint64>(1, bytesToRead / pendingSockets.size());

        QSetIterator<RateControllerTcpSocket *> it(pendingSockets);
        while (it.hasNext() && (bytesToWrite > 0 || bytesToRead > 0)) {
            RateControllerTcpSocket *socket = it.next();

            bool dataTransfered = false;
            qint64 available = qMin<qint64>(socket->bytesAvailable(), readChunk);
            if (available > 0) {
                qint64 readBytes = socket->readFromNetwork(qMin<qint64>(available, bytesToRead));
                if (readBytes > 0) {
                    bytesToRead -= readBytes;
                    dataTransfered = true;
                }
            }

            if (upLimit * 2 > socket->bytesToWrite()) {
                qint64 chunkSize = qMin<qint64>(writeChunk, bytesToWrite);
                qint64 toWrite = qMin<qint64>(upLimit * 2 - socket->bytesToWrite(), chunkSize);

                if (toWrite > 0) {
                    qint64 writtenBytes = socket->writeToNetwork(toWrite);

                    if (writtenBytes > 0) {
                        bytesToWrite -= writtenBytes;
                        dataTransfered = true;
                    }
                }
            }

            if (dataTransfered && socket->canTransferMore()) {
                canTransferMore = true;
            } else {
                pendingSockets.remove(socket);
            }
        }

    } while (canTransferMore && (bytesToWrite > 0 || bytesToRead > 0) && pendingSockets.isEmpty());

    if (canTransferMore) {
        scheduleTransfer();
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
