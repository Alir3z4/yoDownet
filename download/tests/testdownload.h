/****************************************************************************************
** testdownload.h is part of yoDownet
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

#ifndef TESTDOWNLOAD_H
#define TESTDOWNLOAD_H

#include <QObject>
#include <QtTest/QtTest>
#include "download/download.h"
#include "core/autotest.h"

class TestDownload : public QObject
{
    Q_OBJECT
public:
    explicit TestDownload(QObject *parent = 0);

private slots:
    void initTestCase();
    void testAddDownload();
    void testAddDownloadPreUuid();
    void testDownloadUuid();
    void testDownloadPreUuid();
    void testDownloadName();
    void testDownloadPath();
    void testDownloadUrl();

private:
    QString url;
};

DECLARE_TEST(TestDownload)
#endif // TESTDOWNLOAD_H
