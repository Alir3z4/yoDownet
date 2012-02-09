/****************************************************************************************
** downloaderversion.cpp is part of yoDownet
**
** Copyright 2011, 2012 Alireza Savand <alireza.savand@gmail.com>
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
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "downloaderversion.h"

DownloaderVersion::DownloaderVersion(QObject *parent) :
    QObject(parent)
{
}

void DownloaderVersion::setVersion(const QString &version)
{
    _version = version;
}

void DownloaderVersion::setEnabledFeatures(const QStringList &enabledFeatures)
{
    _enabledFeatures = enabledFeatures;
}

QString DownloaderVersion::version() const
{
    return _version;
}

QStringList DownloaderVersion::enabledFeatures() const
{
    return _enabledFeatures;
}

