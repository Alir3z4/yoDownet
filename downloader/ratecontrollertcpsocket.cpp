/****************************************************************************************
** ratecontrollertcpsocket.cpp is part of yoDownet
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

#include "ratecontrollertcpsocket.h"

RateControllerTcpSocket::RateControllerTcpSocket(QObject *parent) :
    QTcpSocket(parent)
{

bool RateControllerTcpSocket::canReadLine() const
{
    return incoming.contains('\n');
}

qint64 RateControllerTcpSocket::writeToNetwork(qint64 maxLen)
{
    qint64 bytesWritten = QTcpSocket::writeData(
                outgoing.data(),
                qMin(maxLen, qint64(outgoing.size()))
    );

    if (bytesWritten <= 0) {
        return bytesWritten;
    }

    outgoing.remove(0, bytesWritten);

    return bytesWritten;
}

qint64 RateControllerTcpSocket::readFromNetwork(qint64 maxLen)
{
    int oldSize = incoming.size();
    incoming.resize(incoming.size() + maxLen);
    qint64 bytesRead = QTcpSocket::readData(
                incoming.data() + oldSize, maxLen
    );
    incoming.resize(bytesRead <= 0 ? oldSize : oldSize + bytesRead);

    if (bytesRead > 0) {
        emit readyRead();
    }

    return bytesRead;
}

bool RateControllerTcpSocket::canTransferMore() const
{
    return !incoming.isEmpty()
            || !outgoing.isEmpty()
            || QTcpSocket::bytesAvailable() > 0 ;
}

qint64 RateControllerTcpSocket::bytesAvailable() const
{
    if (state() != ConnectedState) {
        QByteArray buffer;
        buffer.resize(QTcpSocket::bytesAvailable());

        RateControllerTcpSocket *that = const_cast<RateControllerTcpSocket *>(this);
        that->QTcpSocket::readData(buffer.data(), buffer.size());
        that->incoming += buffer;
    }

    return incoming.size();
}

qint64 RateControllerTcpSocket::readData(char *data, qint64 maxlen)
{
    int bytesRead = qMin<int>(maxlen, incoming.size());
    memcpy(data, incoming.constData(), bytesRead);
    incoming.remove(0, bytesRead);

    if (state() != ConnectedState) {
        QByteArray buffer;
        buffer.resize(QTcpSocket::bytesAvailable());

        QTcpSocket::readData(buffer.data(), buffer.size());

        incoming += buffer;
    }

    return qint64(bytesRead);
}

qint64 RateControllerTcpSocket::readLineData(char *data, qint64 maxlen)
{
    return QIODevice::readLineData(data, maxlen);
}
}
