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

};

#endif // ARIA2C_H
