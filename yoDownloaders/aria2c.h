#ifndef ARIA2C_H
#define ARIA2C_H

#include <QVector>
#include <QMap>
#include <QString>
#include <xmlrpc-c/client_simple.hpp>
#include "yoUtils/downloaderversion.h"
#include "yoUtils/status.h"

class Aria2c
{
public:
    Aria2c(std::string url);

    // Operations
    const QString addUri(const QVector<QString> &qUris);
    const QString addUri(const QVector<QString> &q_uris, const QMap<QString, QString> &q_options);

    // Aria2c actions
    // Remove
    const QString remove(const QString q_gid);
    const QString forceRemove(const QString gid);
    // Pause
    const QString pause(const QString gid);
    const QString forcePause(const QString gid);
    const QString unPause(const QString gid);
    const QString pauseAll();
    const QString forcePauseAll();
    const QString unpauseAll();

    // This tricky guy, version :~]
    const DownloaderVersion* getVersion();
    // This method returns download progress of the download denoted by gid. gid is of type string
    // keys is array of string. If it is specified, the response contains only keys in keys array.
    // If keys is empty or not specified, the response contains all keys.
    // This is useful when you just want specific keys and avoid unnecessary transfers.
    // For example, aria2.tellStatus("1", ["gid", "status"]) returns gid and status key.
    // The response is of type struct and it contains following keys. The value type is string.
    // ref: http://aria2.sourceforge.net/aria2c.1.html#aria2_rpc_aria2_tellStatus
    const Status* tellStatus(const QString q_gid);

    // Shutdown :|
    const QString shutdown();
    // Shut da fuck up, will ya!
    const QString forceShutdown();

    //Purges completed/error/removed downloads to free memory.
    //This method returns "OK"
    const QString purgeDownloadResult();


private:
    void throwException(const xmlrpc_c::rpcPtr &rpc);

    xmlrpc_c::clientXmlTransport_curl _transport;
    xmlrpc_c::client_xml _client;
    xmlrpc_c::carriageParm_curl0 _carriageParm;

    // make some noise :d
    const QString _forDoneSake(const QString qMethodname, const QString qGid);

    // fuck the disaster with this QVector<QString> => std::vector<string>
    // actually i opened a topic for it on [ qtcentre.org/threads/47074 ], but i can't w8 till this fellas
    // got what my point is
    // if i be success in it in future i'll take it away
    // but i think it's better to keep conversion between qvector->vector here in this aria2c class :|
    // who knows ?
    const std::vector<std::string> fromQVector(const QVector<QString> &qVect);
    const std::map<std::string, std::string> fromQMap(const QMap<QString, QString> &qMap);
};

#endif // ARIA2C_H
