/****************************************************************************************
** yosettings.cpp is part of yoDownet
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
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "yosettings.h"
#include <QtCore/QSettings>

yoSettings::yoSettings(QObject *parent) :
    QObject(parent)
{
    // load settings
    load();
}

QString yoSettings::saveDir() const
{
    return _saveDir;
}

QString yoSettings::logFile() const
{
    return _logFile;
}

int yoSettings::maxDownloads() const
{
    return _maxdownloads;
}

QString yoSettings::isContinue() const
{
    return _continue;
}

void yoSettings::load()
{
    QSettings settings;
    settings.beginGroup("PreferencesDialog");

    settings.beginGroup("PrefDownloadersWidget");
    setSaveDir(settings.value("saveDir").toString());
    setLogFile(settings.value("log", "").toString());
    setMaxDownloads(settings.value("max-concurrent-downloads", 5).toInt());
    setContinue(settings.value("continue", "true").toString());
    settings.endGroup();

    settings.endGroup();
}

void yoSettings::setSaveDir(const QString &saveDir)
{
    _saveDir = saveDir;
}

void yoSettings::setLogFile(const QString &logFile)
{
    _logFile= logFile;
}

void yoSettings::setMaxDownloads(const int maxDownloads)
{
    _maxdownloads = maxDownloads;
}

void yoSettings::setContinue(const QString &isContinue)
{
    _continue = isContinue;
}

QVariantMap yoSettings::aria2Options(const Aria2ModeOption &mode) const
{
    QVariantMap addOptions, startOptions;
    addOptions["dir"] = saveDir();
    addOptions["continue"] = isContinue();
    startOptions["log"] = logFile();
    startOptions["max-concurrent-downloads"] = maxDownloads();

    if(mode == AddUriOptions)
        return addOptions;
    else
        return startOptions;
}
