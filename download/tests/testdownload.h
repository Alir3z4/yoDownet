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

/*! \file TestDownload.h
 *  \brief Test Download class
 *
 *  Unit testing Download class.
 */

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
    /*!
     * \brief Initialize TestCase class and required variables.
     */
    void initTestCase();
    /*!
     * \brief Should add new download.
     */
    void testAddDownload();
    /*!
     * \brief Should add new download with custom UUID.
     */
    void testAddDownloadPreUuid();
    /*!
     * \brief Should add new download with pre-defined or custom name.
     */
    void testAddDownloadPreName();
    /*!
     * \brief Should add new download with pre-defined or custom file path.
     */
    void testAddDownloadPrePath();
    /*!
     * \brief Download UUID should not be null after adding new download.
     */
    void testDownloadUuid();
    /*!
     * \brief Should add new download with pre-defined UUID.
     */
    void testDownloadPreUuid();
    void testDownloadName();
    /*!
     * \brief Should get download path after adding new download.
     */
    void testDownloadPath();
    /*!
     * \brief Should have not-null, Open file after adding new download.
     */
    void testDownloadFile();
    /*!
     * \brief Should get absolute file path after adding new download.
     */
    void testDownloadFileAbsolutePath();
    /*!
     * \brief Should get download URL after adding new download.
     */
    void testDownloadUrl();

private:
    /*!
     * \brief A string to hold our boring sample/fake url.
     */
    QString url;
};

DECLARE_TEST(TestDownload)
#endif // TESTDOWNLOAD_H
