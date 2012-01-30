#ifndef FAULT_H
#define FAULT_H

#include <QObject>

class Fault : public QObject
{
    Q_OBJECT
public:
    explicit Fault(QObject *parent = 0);

    void setFaultCode(const int &faultCode);
    void setFaultString(const QString &faultString);

    int faultCode() const;
    QString faultString() const;

private:
    int _faultCode;
    QString _faultString;
    
};

#endif // FAULT_H
