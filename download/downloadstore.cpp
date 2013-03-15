/****************************************************************************************
** downloadstore.cpp is part of yoDownet
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

#include "downloadstore.h"
#include <QtCore/QSettings>

DownloadStore::DownloadStore(QObject *parent) :
    QObject(parent)
{
}

/*
 * Loading download data from settings.
 * This function may called from DownloadStore initializer.
 *
 */
void DownloadStore::loadDownloadData()
{

}

/*
 * Saving download data into settings.
 *  Download data normally should be a List of `Download`, And data won't
 * Saved on-by-one, Saving idea here is to save all the list object in ByteArray format.
 * This way will give more performance for both saving/loading time.
 *
 */
void DownloadStore::saveDownloadData()
{

}
