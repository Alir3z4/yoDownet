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
    url = "http://www.qt-project.org/somefile.tar.gz";
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

void TestDownload::testAddDownloadPreName()
{
    QFAIL("");
}

void TestDownload::testAddDownloadPrePath()
{
    QFAIL("");
}

void TestDownload::testDownloadUuid()
{
    Download download;

    download.newDownload(url);

    QCOMPARE(download.uuid().isNull(), false);
}

void TestDownload::testDownloadPreUuid()
{
    Download download;

    QUuid preUuid = QUuid::createUuid();
    download.newDownload(url, preUuid);

    QCOMPARE(download.uuid(), preUuid);
}

void TestDownload::testDownloadName()
{
    Download download;

    download.newDownload(url);

    QCOMPARE(download.name().isEmpty(), false);
    QCOMPARE(download.name().isNull(), false);
    QCOMPARE(download.name(), QString("somefile.tar.gz"));
}

void TestDownload::testDownloadPath()
{
    Download download;

    download.newDownload(url);
    QString defaultPath = QString(QDir::homePath() + QDir::toNativeSeparators("/"));

    QCOMPARE(download.path(), defaultPath);

}

void TestDownload::testDownloadFile()
{
    Download download;
    download.newDownload(url);

    QCOMPARE(download.file()->isOpen(), true);
    QCOMPARE(download.file()->size(), qint64(0));
}

void TestDownload::testDownloadFileAbsolutePath()
{
    QFAIL("");
}

void TestDownload::testDownloadUrl()
{
    Download download;

    download.newDownload(url);

    QCOMPARE(download.url().isEmpty(), false);
    QCOMPARE(download.url().isValid(), true);
    QCOMPARE(download.url().path(), QString("/somefile.tar.gz"));
    QCOMPARE(download.url(), QUrl(url));
}
