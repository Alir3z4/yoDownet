#ifndef ARIA2C_H
#define ARIA2C_H

#include <vector>
#include <string>
#include <map>
#include <xmlrpc-c/client_simple.hpp>

using namespace std;
class Aria2c
{
public:
    Aria2c(string &url);

    // Operations
    string addUri(vector<string> &uris);
    string addUri(vector<string> &uris, map<string, string> &options);

    // Aria2c actions
    // Remove
    string remove(string &gid);
    string forceRemove(string &gid);
    // Pause
    string pause(string &gid);
    string forcePause(string &gid);
    string unPause(string &gid);
    string pauseAll();
    string forcePauseAll();
    string unpauseAll();

    // Shutdown :|
    string shutdown();
    // Shut da fuck up, will ya!
    string forceShutdown();

private:
    // TODO: throw exception
    // void _throwException(xmlrpc_c::rpcPtr rpc);

    xmlrpc_c::clientXmlTransport_curl _transport;
    xmlrpc_c::client_xml _client;
    xmlrpc_c::carriageParm_curl0 _carriageParm;

    // make some noise :d
    string _forDoneSake(string methodName);
};

#endif // ARIA2C_H
