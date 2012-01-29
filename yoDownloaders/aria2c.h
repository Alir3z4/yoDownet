#ifndef ARIA2C_H
#define ARIA2C_H

#include <vector>
#include <string>
#include <map>
#include <xmlrpc-c/client_simple.hpp>
#include <QVector>
#include <QMap>
#include <QString>

class Aria2c
{
public:
    Aria2c(std::string url);

    // Operations
    const QString addUri(const QVector<QString> &q_uris);
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

    // Shutdown :|
    const QString shutdown();
    // Shut da fuck up, will ya!
    const QString forceShutdown();

private:
    // TODO: throw exception
    // void _throwException(xmlrpc_c::rpcPtr rpc);

    xmlrpc_c::clientXmlTransport_curl _transport;
    xmlrpc_c::client_xml _client;
    xmlrpc_c::carriageParm_curl0 _carriageParm;

    // make some noise :d
    const QString _forDoneSake(const QString q_methodName, const QString q_gid);

    // fuck the disaster with this QVector<QString> => std::vector<string>
    // actually i opened an topic for it on [ qtcentre.org/threads/47074 ], but i can't w8 till this fellas
    // got what my point is
    // if i be success in it in future i'll take it away
    // but i think it's better to keep conversion between qvector->vector here in this aria2c class :|
    // who knows ?
    const std::vector<std::string> fromQVector(const QVector<QString> &q_vect);
    const std::map<std::string, std::string> fromQMap(const QMap<QString, QString> &q_map);
};

#endif // ARIA2C_H
