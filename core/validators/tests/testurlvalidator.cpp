/****************************************************************************************
** testurlvalidator.cpp is part of yoDownet
**
** Copyright 2012 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

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
