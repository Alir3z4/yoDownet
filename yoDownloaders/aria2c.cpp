#include "aria2c.h"
#include "yoUtils/fileinfo.h"
#include "yoUtils/fault.h"
#include "yoUtils/uristatus.h"

Aria2c::Aria2c(std::string url)
    :_client(&_transport), _carriageParm(url)
{
}

const QString Aria2c::addUri(const QVector<QString> &qUris)
{
    std::vector<std::string> uris = fromQVector(qUris);

    std::string const methodName = "aria2.addUri";
    xmlrpc_c::value result;
    xmlrpc_c::paramList params;
    std::vector<xmlrpc_c::value> vUris;

    for (int i = 0, j = uris.size(); i < j; i++)
        vUris.push_back(xmlrpc_c::value_string(uris[i].c_str()));

    xmlrpc_c::value_array aUris(vUris);

    params.add(aUris);

    xmlrpc_c::rpcPtr rpc(methodName, params);
    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    else
        throwException(rpc);

    return QString::fromStdString(xmlrpc_c::value_string(result));
}

const QString Aria2c::addUri(const QVector<QString> &qUris, const QMap<QString, QString> &qOptions)
{
    std::vector<std::string> uris = fromQVector(qUris);
    std::map<std::string, std::string> options = fromQMap(qOptions);

    std::string const methodName = "aria2.addUri";
    xmlrpc_c::value result;
    xmlrpc_c::paramList params;
    std::vector<xmlrpc_c::value> vUris;

    for (int i = 0, j = uris.size(); i < j; i++)
        vUris.push_back((xmlrpc_c::value_string(uris[i].c_str())));

    xmlrpc_c::value_array aUris(vUris);
    std::map<std::string, xmlrpc_c::value> mOptions;

    for(std::map<std::string, std::string>::iterator iter = options.begin(); iter != options.end(); iter++)
    {
        std::pair<std::string, xmlrpc_c::value> pOption(iter->first, xmlrpc_c::value_string(iter->second));
        mOptions.insert(pOption);
    }

    xmlrpc_c::value_struct sOptions(mOptions);

    params.add(aUris);
    params.add(sOptions);

    xmlrpc_c::rpcPtr rpc(methodName, params);
    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    else
        throwException(rpc);

    return QString::fromStdString(xmlrpc_c::value_string(result));
}

const QString Aria2c::remove(const QString q_gid)
{
    std::string gid = q_gid.toStdString();
    std::string const methodName = "aria2.remove";
    xmlrpc_c::value result;
    xmlrpc_c::paramList params;

    params.add(xmlrpc_c::value_string(gid));

    xmlrpc_c::rpcPtr rpc(methodName, params);
    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    else
        throwException(rpc);

    return QString::fromStdString(xmlrpc_c::value_string(result));
}

const QString Aria2c::forceRemove(const QString gid)
{
    return _forDoneSake(QString("aria2.forceRemove"), gid);
}

const QString Aria2c::pause(const QString gid)
{
    return _forDoneSake("aria2.pause", gid);
}

const QString Aria2c::forcePause(const QString gid)
{
    return _forDoneSake("aria2.forcePause", gid);
}

const QString Aria2c::unPause(const QString gid)
{
     return _forDoneSake("aria2.unpause", gid);
}

const QString Aria2c::pauseAll()
{
    return _forDoneSake("aria2.pauseAll", QString());
}

const QString Aria2c::forcePauseAll()
{
    return _forDoneSake("aria2.forcePauseAll", QString());
}

const QString Aria2c::unpauseAll()
{
    return _forDoneSake("aria2.unPauseAll", QString());
}

const DownloaderVersion* Aria2c::getVersion()
{
    std::string const methodName = "aria2.getVersion";
    xmlrpc_c::value result;

    xmlrpc_c::paramList params;
    xmlrpc_c::rpcPtr rpc(methodName, params);

    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    else
        throwException(rpc);

    xmlrpc_c::value_struct structResult(result);
    std::map<std::string, xmlrpc_c::value> mapResult(static_cast< std::map<std::string, xmlrpc_c::value> >(structResult));

    DownloaderVersion *version = NULL;

    std::map<std::string, xmlrpc_c::value>::iterator itProp;

    itProp = mapResult.find("version");
    if(itProp != mapResult.end())
        version->setVersion(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("enabledFeatures");
    if(itProp != mapResult.end()){
        // Just watch gonna happen with this little bastard
        // It's little bit tricky-freaky, so here is the thing
        // That thing e retreive back from 'getVersion' is an 'array'
        // So basicaly we cast it to a 'vector'
        // ref: http://aria2.sourceforge.net/aria2c.1.html#aria2_rpc_aria2_getVersion
        std::vector<xmlrpc_c::value> vEnabledFeatures(xmlrpc_c::value_array(itProp->second).vectorValueValue());
        // So we cast it to a vector already, now what?
        // Okay, it's time to create an mothe'fucker 'iterator' for that son of bitch 'vector'
        std::vector<xmlrpc_c::value>::iterator itEnabledFeatures = vEnabledFeatures.begin();

        // Now for each fuck'n 'enabledFeature'
        QVector<QString> tempVector;
        for (; itEnabledFeatures != vEnabledFeatures.end(); itEnabledFeatures++) {
            tempVector.push_back(QString::fromStdString(xmlrpc_c::value_string(*itEnabledFeatures)));
        }
        version->setEnabledFeatures(tempVector);
    }
    return version;
}

const Status *Aria2c::tellStatus(const QString q_gid)
{
    std::string const methodName = "aria2.tellStatus";
    std::string gid = q_gid.toStdString();
    xmlrpc_c::value result;

    xmlrpc_c::paramList params;
    params.add(xmlrpc_c::value_string(gid));

    xmlrpc_c::rpcPtr rpc(methodName, params);

    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    else
        throwException(rpc);

    // So here's the movie story
    // the result type now is an XML struct
    // Shoulda to be converted to C++ map ;)
    // This is gonna be fun! [ actually noth'n funny here, just eeeeh!!! ]
    xmlrpc_c::value_struct structResult(result);
    std::map<std::string, xmlrpc_c::value> mapResult(
                static_cast< std::map<std::string, xmlrpc_c::value> >(structResult));

    Status *status = NULL;

    std::map<std::string, xmlrpc_c::value>::iterator itProp;

    itProp = mapResult.find("status");
    if(itProp != mapResult.end())
        status->setStatus(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("gid");
    if(itProp != mapResult.end())
        status->setGid(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("totalLength");
    if(itProp != mapResult.end())
        status->setTotalLength(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("completedLength");
    if(itProp != mapResult.end())
        status->setCompletedLength(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("uploadLength");
    if(itProp != mapResult.end())
        status->setUploadLength(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("bitField");
    if(itProp != mapResult.end())
        status->setBitField(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("downloadSpeed");
    if(itProp != mapResult.end())
        status->setDownloadSpeed(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("uploadSpeed");
    if(itProp != mapResult.end())
        status->setUploadSpeed(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("infoHash");
    if(itProp != mapResult.end())
        status->setInfoHash(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("numSeeders");
    if(itProp != mapResult.end())
        status->setNumSeeders(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("pieceLength");
    if(itProp != mapResult.end())
        status->setPieceLength(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("numPieces");
    if(itProp != mapResult.end())
        status->setNumPieces(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("connections");
    if(itProp != mapResult.end())
        status->setConnections(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("errorCode");
    if(itProp != mapResult.end())
        status->setErrorCode(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("followedBy");
    if(itProp != mapResult.end())
        status->setFollowedBy(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("belongsTo");
    if(itProp != mapResult.end())
        status->setBelongsTo(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("dir");
    if(itProp != mapResult.end())
        status->setDir(QString::fromStdString(xmlrpc_c::value_string(itProp->second)));

    itProp = mapResult.find("files");
    if(itProp != mapResult.end()){
        // So basicaly we cast it to a 'vector'
        std::vector<xmlrpc_c::value> vFiles(xmlrpc_c::value_array(itProp->second).vectorValueValue());
        // Then we create an iterator for the 'vector'
        std::vector<xmlrpc_c::value>::iterator itFiles = vFiles.begin();

        // So here fo each fuck'n 'files'
        for(; itFiles != vFiles.end(); itFiles++) {
            // Convert it to an xml struct
            xmlrpc_c::value_struct structFile(*itFiles);
            // Then to a C++ map
            std::map<std::string, xmlrpc_c::value> mapFile(
                        static_cast< std::map<std::string, xmlrpc_c::value> > (structFile));

            std::map<std::string, xmlrpc_c::value>::iterator itFile;
            FileInfo *tempFileInfo = NULL;

            itFile = mapFile.find("index");
            if(itFile != mapFile.end())
                tempFileInfo->setIndex(QString::fromStdString(xmlrpc_c::value_string(itFile->second)));

            itFile = mapFile.find("path");
            if(itFile != mapFile.end())
                tempFileInfo->setPath(QString::fromStdString(xmlrpc_c::value_string(itFile->second)));

            itFile = mapFile.find("length");
            if(itFile != mapFile.end())
                tempFileInfo->setLength(QString::fromStdString(xmlrpc_c::value_string(itFile->second)));

            itFile = mapFile.find("selected");
            if(itFile != mapFile.end())
                tempFileInfo->setSelected(QString::fromStdString(xmlrpc_c::value_string(itFile->second)));

            // Then an 'array' of uri's
            // :|
            itFile = mapFile.find("uris");
            if(itFile != mapFile.end()){
                // So it's old
                // Again dealing with an xml array
                // then converting to c++ map :|
                std::vector<xmlrpc_c::value> vUris(xmlrpc_c::value_array(itFile->second).vectorValueValue());
                std::vector<xmlrpc_c::value>::iterator itUris = vUris.begin();
                for(; itUris != vUris.end(); itUris++){
                    xmlrpc_c::value_struct structUri(*itUris);
                    std::map<std::string, xmlrpc_c::value> mapUri(
                                static_cast< std::map<std::string, xmlrpc_c::value> > (structUri));

                    std::map<std::string, xmlrpc_c::value>::iterator itUri;

                    UriStatus *tempUriStatus;

                    itUri = mapUri.find("uri");
                    if(itUri != mapUri.end())
                        tempUriStatus->setUri(QString::fromStdString(xmlrpc_c::value_string(itUri->second)));

                    itUri = mapUri.find("status");
                    if(itUri != mapUri.end())
                        tempUriStatus->setStatus(QString::fromStdString(xmlrpc_c::value_string(itUri->second)));

                    QVector<UriStatus*> tempUriStatusVector;
                    tempUriStatusVector.push_back(tempUriStatus);

                    tempFileInfo->setUris(tempUriStatusVector);
                }
            }

            QVector<FileInfo*> tempFileInfoVector;
            tempFileInfoVector.push_back(tempFileInfo);

            status->setFiles(tempFileInfoVector);
        }
    }

    itProp = mapResult.find("bittorrent");
    if(itProp != mapResult.end()){
        // TODO: add bittorrent information to "status"
    }

    return status;
}

const QString Aria2c::shutdown()
{
    return _forDoneSake("aria2.shutdown", QString());
}

const QString Aria2c::forceShutdown()
{
    return _forDoneSake("aria2.forceShutdown", QString());
}

const QString Aria2c::purgeDownloadResult()
{
    return _forDoneSake("aria2.purgeDownloadResult", QString());
}

void Aria2c::throwException(const xmlrpc_c::rpcPtr &rpc)
{
    xmlrpc_c::fault tempFault;
    tempFault = rpc->getFault();

    Fault *fault = NULL;

    fault->setFaultCode(tempFault.getCode());
    fault->setFaultString(QString::fromStdString(tempFault.getDescription()));

    throw fault;
}

const QString Aria2c::_forDoneSake(const QString qMethodname, const QString qGid = "")
{
    std::string methodName = qMethodname.toStdString();
    std::string gid = qGid.toStdString();
    xmlrpc_c::value result;
    xmlrpc_c::paramList params; // Just initial, not used :D

    if(gid != "")
        params.add(xmlrpc_c::value_string(gid));

    xmlrpc_c::rpcPtr rpc(methodName, params);
    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    else
        throw rpc->getFault();

    return QString::fromStdString(xmlrpc_c::value_string(result));
}

const std::vector<std::string> Aria2c::fromQVector(const QVector<QString> &qVect)
{
    std::vector<std::string> stdVect;
    for (int i = 0; i < qVect.size(); ++i) {
        stdVect.push_back(qVect[i].toStdString());
    }
    return stdVect;
}

const std::map<std::string, std::string> Aria2c::fromQMap(const QMap<QString, QString> &qMap)
{
    std::map<std::string, std::string> stdMap;
    QMap<QString, QString>::const_iterator i = qMap.constBegin();
    while (i != qMap.constEnd()) {
        stdMap.insert(std::pair<std::string, std::string>(i.key().toStdString(), i.value().toStdString()));
    }

    return stdMap;
}

