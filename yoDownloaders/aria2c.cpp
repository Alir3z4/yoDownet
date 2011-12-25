#include "aria2c.h"

Aria2c::Aria2c()
{
}

string Aria2c::addUri(vector<string> uris)
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
