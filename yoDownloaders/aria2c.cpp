#include "aria2c.h"

Aria2c::Aria2c(string &url)
    :_client(&_transport), _carriageParm(url)
{
}

string Aria2c::addUri(vector<string> &uris)
{
    string const methodName = "aria2.addUri";
    xmlrpc_c::value result;
    xmlrpc_c::paramList params;
    vector<xmlrpc_c::value> v_uris;

    for (int i = 0, j = uris.size(); i < j; i++)
        v_uris.push_back(xmlrpc_c::value_string(uris[i].c_str()));

    xmlrpc_c::value_array a_uris(v_uris);

    params.add(a_uris);

    xmlrpc_c::rpcPtr rpc(methodName, params);
    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    throw rpc->getFault();

    return xmlrpc_c::value_string(result);
}

string Aria2c::addUri(vector<string> &uris, map<string, string> &options)
{
    string const methodName = "aria2.addUri";
    xmlrpc_c::value result;
    xmlrpc_c::paramList params;
    vector<xmlrpc_c::value> v_uris;

    for (int i = 0, j = uris.size(); i < j; i++)
        v_uris.push_back((xmlrpc_c::value_string(uris[i].c_str())));

    xmlrpc_c::value_array a_uris(v_uris);
    map<string, xmlrpc_c::value> m_options;

    for(map<string, string>::iterator iter = options.begin(); iter != options.end(); iter++)
    {
        pair<string, xmlrpc_c::value> p_option(iter->first, xmlrpc_c::value_string(iter->second));
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

    return xmlrpc_c::value_string(result);
}

string Aria2c::remove(string &gid)
{
    string const methodName = "aria2.remove";
    xmlrpc_c::value result;
    xmlrpc_c::paramList params;

    params.add(xmlrpc_c::value_string(gid));

    xmlrpc_c::rpcPtr rpc(methodName, params);
    rpc->call(&_client, &_carriageParm);

    if(rpc->isSuccessful())
        result = rpc->getResult();
    else
        throw rpc->getFault();

    return xmlrpc_c::value_string(result);
}

string Aria2c::forceRemove(string &gid)
{
    return _forDoneSake("aria2.forceRemove", gid);
}

string Aria2c::pause(string &gid)
{
    return _forDoneSake("aria2.pause", gid);
}

string Aria2c::forcePause(string &gid)
{
    return _forDoneSake("aria2.forcePause", gid);
}

string Aria2c::unPause(string &gid)
{
     return _forDoneSake("aria2.unpause", gid);
}

string Aria2c::pauseAll()
{
    return _forDoneSake("aria2.pauseAll", string());
}

string Aria2c::forcePauseAll()
{
    return _forDoneSake("aria2.forcePauseAll", string());
}

string Aria2c::unpauseAll()
{
    return _forDoneSake("aria2.unPauseAll", string());
}

string Aria2c::shutdown()
{
    return _forDoneSake("aria2.shutdown", string());
}

string Aria2c::forceShutdown()
{
    return _forDoneSake("aria2.forceShutdown", string());
}

string Aria2c::_forDoneSake(string methodName, const string &gid)
{
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

    return xmlrpc_c::value_string(result);
}
