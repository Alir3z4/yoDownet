#include "testurlvalidator.h"

TestUrlValidator::TestUrlValidator(QObject *parent) :
    QObject(parent)
{
    _validator = new UrlValidator;
}

void TestUrlValidator::plainUrl()
{
    _validator->setUrl("http://www.qt-project.org");
    QCOMPARE(_validator->isValid(), true);
}

void TestUrlValidator::noDomainUrl()
{
    _validator->setUrl("http://");
    QCOMPARE(_validator->isValid(), true);
}

void TestUrlValidator::noProtocol()
{
    _validator->setUrl("qt-project.com");
    QCOMPARE(_validator->isValid(), true);
}

void TestUrlValidator::encodedUrl()
{
    _validator->setUrl("http://www.qt-project.com/List%20of%20holidays.xml");
    QCOMPARE(_validator->isValid(), true);
}

void TestUrlValidator::withSpaceUrl()
{
    _validator->setUrl("http://www.qt-project.com/List of holidays.xml");
    QCOMPARE(_validator->isValid(), true);
}

void TestUrlValidator::ftpUrl()
{
    _validator->setUrl("ftp://www.qt-project.com/somefile.tar.gz");
    QCOMPARE(_validator->isValid(), true);
}

void TestUrlValidator::httpUrl()
{
    _validator->setUrl("http://www.qt-project.com/somefile.tar.gz");
    QCOMPARE(_validator->isValid(), true);
}

void TestUrlValidator::sshUrl()
{
    _validator->setUrl("ssh://www.qt-project.com");
    QCOMPARE(_validator->isValid(), true);
}
