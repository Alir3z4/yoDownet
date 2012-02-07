#include "aria2c.h"
#include <QVariant>

Aria2c::Aria2c(QObject *parent) :
    QObject(parent), _client(new MaiaXmlRpcClient(QUrl("http://localhost:6800/rpc"), parent)),
    _process(new QProcess(parent))
{
    // signals/slots
    connect(this, SIGNAL(ariaStarted(bool)), this, SLOT(setAriaStarted(bool)));
    connect(this, SIGNAL(ariaIsNotRunning()), this, SLOT(startAria()));
    connect(this, SIGNAL(ariaIsRunning()), this, SLOT(shutdown()));
    connect(this, SIGNAL(statusTold(const Status*)), this, SLOT(setStatus(const Status*)));
    connect(this, SIGNAL(versionGot(const DownloaderVersion*)), this, SLOT(setVersion(const DownloaderVersion*)));
}

Aria2c::~Aria2c()
{
    _process->close();
    delete _process;
    delete _client;
}

const Status *Aria2c::status()
{
    return _status;
}

const DownloaderVersion *Aria2c::DlVersion()
{
    return _version;
}

void Aria2c::addUri(const QVariant &uri, QVariantMap &options)
{
    QVariantList params;
    params.push_back(uri);;
    params.push_back(options);
    _client->call("aria2.addUri", params, this, SLOT(addUriResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::remove(const QVariant &gid)
{
    QVariantList params;
    params.push_back(gid);
    _client->call("aria2.remove", params,
                  this, SLOT(removeResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::forceRemove(const QVariant &gid)
{
    QVariantList params;
    params.push_back(gid);
    _client->call("aria2.forceRemove", params,
                  this, SLOT(forceRemoveResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::pause(const QVariant &gid)
{
    QVariantList params;
    params.push_back(gid);
    _client->call("aria2.pause", params,
                  this, SLOT(pauseResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::stop(const QVariant &gid)
{
    QVariantList params;
    params.push_back(gid);
    _client->call("aria2.pause", params,
                  this, SLOT(stopResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::pauseAll()
{
    _client->call("aria2.pauseAll", QVariantList(),
                  this, SLOT(pauseAllResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::forcePause(const QVariant &gid)
{
    QVariantList params;
    params.push_back(gid);
    _client->call("aria2.forcePause", params,
                  this, SLOT(forcePauseResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::forcePauseAll()
{
    _client->call("aria2.forcePauseAll", QVariantList(),
                  this, SLOT(fforcePauseAllResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::unpause(const QVariant &gid)
{
    QVariantList params;
    params.push_back(gid);
    _client->call("aria2.unpause", params,
                  this, SLOT(unpauseResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::unpauseAll()
{
     _client->call("aria2.unpauseAll", QVariantList(),
                  this, SLOT(unpauseAllResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::tellStatus(const QVariant &gid, const QVariantList &keys)
{
    QVariantList params;
    params.push_back(gid);
    params.push_back(keys);
    _client->call("aria2.tellStatus", params,
                  this, SLOT(tellStatusResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::getVersion()
{
     _client->call("aria2.getVersion", QVariantList(),
                  this, SLOT(getVersionResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::shutdown()
{
    _client->call("aria2.shutdown", QVariantList(),
                  this, SLOT(shutdownResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::forceShutdown()
{
    _client->call("aria2.forceShutdown", QVariantList(),
                  this, SLOT(forceShutdownResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

void Aria2c::addUriResponse(QVariant &gid)
{
    emit uriAdded(gid);
}

void Aria2c::forceRemoveResponse(QVariant &gid)
{
    emit uriForcedToRemove(gid.toString());
}

void Aria2c::removeResponse(QVariant &gid)
{
    emit uriRemoved(gid.toString());
}

void Aria2c::pauseResponse(QVariant &gid)
{
    emit uriPaused(gid.toString());
}

void Aria2c::stopResponse(QVariant &gid)
{
    emit uriStopped(gid.toString());
}

void Aria2c::refreshStatusResponse(QVariant &tell)
{
    emit statusRefreshed(swallowingStatus(tell));
}

void Aria2c::pauseAllResponse(QVariant &msg)
{
    emit allUrisPaused(msg.toString());
}

void Aria2c::forcePauseResponse(QVariant &gid)
{
    emit uriForcedToPause(gid.toString());
}

void Aria2c::forcePauseAllResponse(QVariant &msg)
{
    emit allUrisForcedToPause(msg.toString());
}

void Aria2c::unpauseResponse(QVariant &gid)
{
    emit uriUnPaused(gid.toString());
}

void Aria2c::unpauseAllResponse(QVariant &msg)
{
    emit allUrisUnPaused(msg.toString());
}

void Aria2c::tellStatusResponse(QVariant &tell)
{
    emit statusTold(swallowingStatus(tell));
}

void Aria2c::getVersionResponse(QVariant &version)
{
    QVariantMap versionMap = version.toMap();
    DownloaderVersion *dlVersion = new DownloaderVersion(this);
    dlVersion->setVersion(versionMap.value("version").toString());
    dlVersion->setEnabledFeatures(versionMap.value("enabledFeatures").toStringList());

    emit versionGot(dlVersion);
}

void Aria2c::shutdownResponse(QVariant &msg)
{
    qWarning("shutdownResponse");
    emit aria2Shuteddown(msg.toString());
    _process->close();
    qWarning("_process->close()");
}

void Aria2c::forceShutdownResponse(QVariant &msg)
{
    emit aria2ForcedToShutdown(msg.toString());
}

void Aria2c::startAria()
{
    QStringList args;
    args << "--enable-rpc" << "--max-connection-per-server" << "4" << "--min-split-size" << "1M";
    _process->start("aria2c", args);
    emit ariaStarted(true);
}

void Aria2c::setAriaStarted(bool isIt)
{
    _isAriaStarted = isIt;
}

bool Aria2c::isAriaStarted() const
{
    return _isAriaStarted;
}

void Aria2c::refreshStatus(const QVariant &gid, const QVariantList &keys)
{
    QVariantList params;
    params.push_back(gid);
    params.push_back(keys);
    _client->call("aria2.tellStatus", params,
                  this, SLOT(refreshStatusResponse(QVariant&)), this, SLOT(faultResponse(int,QString)));
}

const Status *Aria2c::swallowingStatus(QVariant &tell)
{
    qDebug() << tell;
    Status *status = new Status(this);
    QVariantMap tellMap = tell.toMap();

    status->setGid(tellMap.value("gid").toString());
    status->setStatus(tellMap.value("status").toString());
    status->setTotalLength(tellMap.value("totalLength").toString());
    status->setCompletedLength(tellMap.value("completedLength").toString());
    bool ok;
    status->setBitField(QString::number(tellMap.value("bitField").toByteArray().toUInt(&ok, 16)));
    status->setDownloadSpeed(tellMap.value("downloadSpeed").toString());
    status->setUploadSpeed(tellMap.value("uploadSpeed").toString());
    status->setInfoHash(tellMap.value("infoHash").toString());
    status->setPieceLength(tellMap.value("pieceLength").toString());
    status->setNumPieces(tellMap.value("numPieces").toString());
    status->setConnections(tellMap.value("connections").toString());
    status->setErrorCode(tellMap.value("errorCode").toString());
    status->setFollowedBy(tellMap.value("followedBy").toString());
    status->setBelongsTo(tellMap.value("belongsTo").toString());
    status->setDir(tellMap.value("dir").toString());

    // TODO: add bittorrent information to status

    QList<FileInfo*> fileInfoList;
    QList<UriStatus*> uriStatusList;

    foreach (QVariant files, tellMap.value("files").toList()) {
        FileInfo *tempFile = new FileInfo(this);
        tempFile->setCompletedLength(files.toMap().value("completedLength").toString());
        tempFile->setIndex(files.toMap().value("index").toString());
        tempFile->setLength(files.toMap().value("length").toString());
        tempFile->setPath(files.toMap().value("path").toString());
        tempFile->setSelected(files.toMap().value("selected").toString());
        foreach (QVariant filesMap, files.toMap()) {
            foreach (QVariant uris, filesMap.toList()) {
                UriStatus *tempUris = new UriStatus(this);
                tempUris->setStatus(uris.toMap().value("status").toString());
                tempUris->setUri(uris.toMap().value("uri").toString());
                uriStatusList.push_back(tempUris);
            }
        }
        tempFile->setUris(uriStatusList);
        fileInfoList.push_back(tempFile);
    }

    status->setFiles(fileInfoList);
    return status;
}

void Aria2c::faultResponse(int faultCode, const QString &faultString)
{
    switch (faultCode){
    // Connection refused
    case -32300:
        if(!isAriaStarted()){
            startAria();
        }
        break;

    default:
        qDebug() << "Fault: " << faultCode << " - " << faultString;
    }
}

void Aria2c::setStatus(const Status *status)
{
    _status = status;
}

void Aria2c::setVersion(const DownloaderVersion *version)
{
    _version = version;
}
