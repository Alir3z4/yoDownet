/****************************************************************************************
** testdownload.cpp is part of yoDownet
**
** Copyright 2013 Alireza Savand <alireza.savand@gmail.com>
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

#include "testdownload.h"

TestDownload::TestDownload(QObject *parent) :
    QObject(parent)
{
}

void TestDownload::initTestCase()
{
    url = "http://www.qt-project.com/somefile.tar.gz";
}

void TestDownload::testAddDownload()
{
    Download download;

    QCOMPARE(download.newDownload(QUrl(url)), true);
}

void TestDownload::testAddDownloadPreUuid()
{
    Download download;

    QCOMPARE(download.newDownload(url, QUuid::createUuid()), true);
}

void TestDownload::testDownloadUuid()
{
    QFAIL("");

void TestDownload::testDownloadPreUuid()
{
    Download download;

    QUuid preUuid = QUuid::createUuid();
    download.newDownload(url, preUuid);

    QCOMPARE(download.uuid(), preUuid);
}

void TestDownload::testDownloadName()
{
    QFAIL("");
}

void TestDownload::testDownloadPath()
{
    QFAIL("");
}

void TestDownload::testDownloadUrl()
{
    QFAIL("");
}
