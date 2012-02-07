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

    // Budies
    void startAria();
    void setAriaStarted(bool isIt);
    bool isAriaStarted() const;

    // To overloading :|
    void stopResponse(QVariant &gid);
    void refreshStatusResponse(QVariant &tell);
    const Status *swallowingStatus(QVariant &tell);

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
