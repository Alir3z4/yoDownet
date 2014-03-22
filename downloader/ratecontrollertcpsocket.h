/****************************************************************************************
** ratecontrollertcpsocket.h is part of yoDownet
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

#ifndef RATECONTROLLERTCPSOCKET_H
#define RATECONTROLLERTCPSOCKET_H

#include <QTcpSocket>

class RateControllerTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit RateControllerTcpSocket(QObject *parent = 0);

    bool canReadLine() const;

    qint64 writeToNetwork(qint64 maxLen);
    qint64 readFromNetwork(qint64 maxLen);

    bool canTransferMore() const;
    qint64 bytesAvailable() const;
    qint64 networkBytesAvailable() const;

signals:
    void readyToTransfer();

protected:
    qint64 readData(char *data, qint64 maxlen);
    qint64 readLineData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    QByteArray outgoing;
    QByteArray incoming;
};

#endif // RATECONTROLLERTCPSOCKET_H