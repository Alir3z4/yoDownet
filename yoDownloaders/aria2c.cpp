#include "aria2c.h"

Aria2c::Aria2c()
{
}

string Aria2c::addUri(vector<string> &uris)
{
    string const methodName = "aria2.addUri";
    xmlrpc_c::value result;
    vector<xmlrpc_c::value> v_uris;

    for (int i = 0, j = uris.size(); i < j; i++)
        v_uris.push_back(xmlrpc_c::value_string(uris[i].c_str()));

    xmlrpc_c::value_array a_uris(v_uris);

    xmlrpc_c::paramList params;
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
    string const methodName = "aria2.forceRemove";
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

string Aria2c::pause(string &gid)
{
    string const methodName = "aria2.pause";
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

string Aria2c::forcePause(string &gid)
{
    string const methodName = "aria2.forcePause";
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

string Aria2c::unPause(string &gid)
{
    string const methodName = "aria2.unpause";
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

