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

void yoSettings::load()
{
    QSettings settings;
    settings.beginGroup("PreferencesDialog");

    settings.beginGroup("PrefDownloadersWidget");
    setSaveDir(settings.value("saveDir").toString());
    settings.endGroup();

    settings.endGroup();
}

void yoSettings::setSaveDir(const QString &saveDir)
{
    _saveDir = saveDir;
}

QVariantMap yoSettings::aria2Options() const
{
    QVariantMap options;
    options["dir"] = saveDir();
    options["continue"] = "true";

    return options;
}
