#include "changeduris.h"

ChangedUris::ChangedUris(QObject *parent) :
    QObject(parent)
{
}

void ChangedUris::setDeleted(const int &deleted)
{
    _deleted = deleted;
}

void ChangedUris::setAdded(const int &added)
{
    _added = added;
}

int ChangedUris::deleted() const
{
    return _deleted;
}

int ChangedUris::added() const
{
    return _added;
}
