#ifndef CHANGEDURIS_H
#define CHANGEDURIS_H

#include <QObject>

class ChangedUris : public QObject
{
    Q_OBJECT
public:
    explicit ChangedUris(QObject *parent = 0);
    
    void setDeleted(const int &deleted);
    void setAdded(const int &added);

    int deleted() const;
    int added() const;

private:
    int _deleted;
    int _added;
    
};

#endif // CHANGEDURIS_H
