#include "aria2c.h"

Aria2c::Aria2c(std::string url)
    :_client(&_transport), _carriageParm(url)
{
}

const QString Aria2c::addUri(const QVector<QString> &q_uris)
{
    std::vector<std::string> uris = fromQVector(q_uris);

    std::string const methodName = "aria2.addUri";
    xmlrpc_c::value result;
    xmlrpc_c::paramList params;
    std::vector<xmlrpc_c::value> v_uris;

    for (int i = 0, j = uris.size(); i < j; i++)
        v_uris.push_back(xmlrpc_c::value_string(uris[i].c_str()));

    xmlrpc_c::value_array a_uris(v_uris);

    params.add(a_uris);

    xmlrpc_c::rpcPtr rpc(methodName, params);
    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    throw rpc->getFault();

    return QString::fromStdString(xmlrpc_c::value_string(result));
}

const QString Aria2c::addUri(const QVector<QString> &q_uris, const QMap<QString, QString> &q_options)
{
    std::vector<std::string> uris = fromQVector(q_uris);
    std::map<std::string, std::string> options = fromQMap(q_options);

    std::string const methodName = "aria2.addUri";
    xmlrpc_c::value result;
    xmlrpc_c::paramList params;
    std::vector<xmlrpc_c::value> v_uris;

    for (int i = 0, j = uris.size(); i < j; i++)
        v_uris.push_back((xmlrpc_c::value_string(uris[i].c_str())));

    xmlrpc_c::value_array a_uris(v_uris);
    std::map<std::string, xmlrpc_c::value> m_options;

    for(std::map<std::string, std::string>::iterator iter = options.begin(); iter != options.end(); iter++)
    {
        std::pair<std::string, xmlrpc_c::value> p_option(iter->first, xmlrpc_c::value_string(iter->second));
        m_options.insert(p_option);
    }

    xmlrpc_c::value_struct s_options(m_options);

    params.add(a_uris);
    params.add(s_options);

    xmlrpc_c::rpcPtr rpc(methodName, params);
    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    else
        throw rpc->getFault();

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
        throw rpc->getFault();

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

const QString Aria2c::shutdown()
{
    return _forDoneSake("aria2.shutdown", QString());
}

const QString Aria2c::forceShutdown()
{
    return _forDoneSake("aria2.forceShutdown", QString());
}

const QString Aria2c::_forDoneSake(const QString q_methodName, const QString q_gid = "")
{
    std::string methodName = q_methodName.toStdString();
    std::string gid = q_gid.toStdString();
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

const std::vector<std::string> Aria2c::fromQVector(const QVector<QString> &q_vect)
{
    std::vector<std::string> std_vect;
    for (int i = 0; i < q_vect.size(); ++i) {
        std_vect.push_back(q_vect[i].toStdString());
    }
    return std_vect;
}

const std::map<std::string, std::string> Aria2c::fromQMap(const QMap<QString, QString> &q_map)
{
    std::map<std::string, std::string> std_map;
    QMap<QString, QString>::const_iterator i = q_map.constBegin();
    while (i != q_map.constEnd()) {
        std_map.insert(std::pair<std::string, std::string>(i.key().toStdString(), i.value().toStdString()));
    }

    return std_map;
}

