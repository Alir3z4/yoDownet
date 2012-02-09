/****************************************************************************************
** aria2.h is part of yoDownet
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

#ifndef ARIA2C_H
#define ARIA2C_H

#include <QObject>
#include "libmaia/maiaXmlRpcClient.h"
#include "yoUtils/status.h"
#include "yoUtils/downloaderversion.h"

class Aria2c : public QObject
{
    Q_OBJECT

public:
    explicit Aria2c(QObject *parent = 0);
    ~Aria2c();

    const Status *status();
    const DownloaderVersion *DlVersion();

public slots:
    void addUri(const QVariant &uri, QVariantMap &options);
    void remove(const QVariant &gid);
    void forceRemove(const QVariant &gid);
    void pause(const QVariant &gid);
    void stop(const QVariant &gid);
    void pauseAll();
    void forcePause(const QVariant &gid);
    void forcePauseAll();
    void unpause(const QVariant &gid);
    void unpauseAll();
    void tellStatus(const QVariant &gid, const QVariantList &keys);
    void getVersion();
    void shutdown();
    void forceShutdown();

    // overload
    void refreshStatus(const QVariant &gid, const QVariantList &keys);

private slots:
    void addUriResponse(QVariant &gid);
    void forceRemoveResponse(QVariant &gid);
    void removeResponse(QVariant &gid);
    void pauseResponse(QVariant &gid);
    void pauseAllResponse(QVariant &msg);
    void forcePauseResponse(QVariant &gid);
    void forcePauseAllResponse(QVariant &msg);
    void unpauseResponse(QVariant &gid);
    void unpauseAllResponse(QVariant &msg);
    void tellStatusResponse(QVariant &tell);
    void getVersionResponse(QVariant &version);
    void shutdownResponse(QVariant &msg);
    void forceShutdownResponse(QVariant &msg);

    //
    void setStatus(const Status *status);
    void setVersion(const DownloaderVersion *version);

    // Fault
    void faultResponse(int faultCode, const QString &faultString);

    // To overloading :|
    void stopResponse(QVariant &gid);
    void refreshStatusResponse(QVariant &tell);
    const Status *swallowingStatus(QVariant &tell);

protected slots:
    // Budies
    void startAria();
    void setAriaStarted(bool isIt);
    bool isAriaStarted() const;

signals:
    void uriAdded(const QVariant &gid);
    void uriRemoved(const QString &gid);
    void uriForcedToRemove(const QString &gid);
    void uriPaused(const QString &gid);
    void uriStopped(const QString &gid);
    void allUrisPaused(const QString &msg);
    void uriForcedToPause(const QString &gid);
    void allUrisForcedToPause(const QString &msg);
    void uriUnPaused(const QString &gid);
    void allUrisUnPaused(const QString &msg);
    void statusTold(const Status* tell);
    void versionGot(const DownloaderVersion *version);
    void aria2Shuteddown(const QString &msg);
    void aria2ForcedToShutdown(const QString &msg);

    // Home use only! :D
    void ariaIsRunning();
    void ariaIsNotRunning();
    void ariaStarted(bool started);

    // Also overloaded signals =))
    void statusRefreshed(const Status* status);

private:
    MaiaXmlRpcClient *_client;
    QProcess *_process;
    bool _isAriaStarted;

    const Status *_status;
    const DownloaderVersion *_version;

};
#endif // ARIA2C_H
