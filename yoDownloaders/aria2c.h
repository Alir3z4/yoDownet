#ifndef ARIA2C_H
#define ARIA2C_H

class Aria2c
{
public:
    Aria2c();
    string addUri(vector<string> uris);
    string addUri(vector<string> &uris);
    string remove(string &gid);
};

#endif // ARIA2C_H
