#include "fault.h"

Fault::Fault(QObject *parent) :
    QObject(parent)
{
}

void Fault::setFaultCode(const int &faultCode)
{
    _faultCode = faultCode;
}

void Fault::setFaultString(const QString &faultString)
{
   _faultString = faultString;
}

int Fault::faultCode() const
{
    return _faultCode;
}

QString Fault::faultString() const
{
    return _faultString;
}
