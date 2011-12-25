#ifndef ARIA2C_H
#define ARIA2C_H

class Aria2c
{
public:
    Aria2c();
    string addUri(vector<string> uris);
    string addUri(vector<string> &uris);
    string addUri(vector<string> &uris, map<string, string> &options);

    string remove(string &gid);
    string forceRemove(string &gid);
    string pause(string &gid);
    string forcePause(string &gid);
    string unPause(string &gid);
    string pauseAll();
    string forcePauseAll();
    string unpauseAll();

    string shutdown();
    string forceShutdown();

private:
    // TODO: throw exception
    // void _throwException(xmlrpc_c::rpcPtr rpc);

    xmlrpc_c::clientXmlTransport_curl _transport;
    xmlrpc_c::client_xml _client;
    xmlrpc_c::carriageParm_curl0 _carriageParm;

    // make some noise :d
    string _nonParam(string methodName);
};

#endif // ARIA2C_H
