/****************************************************************************************
** main.cpp is part of yoDownet
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
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include "util/paths.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    QCoreApplication::setApplicationName("yoDownet");
    QCoreApplication::setApplicationVersion("2012.04.24");
    QCoreApplication::setOrganizationName("Alir3z4");
    QCoreApplication::setOrganizationDomain("yodownet.sourceforge.net");

    // FIXME move this from here to some other file
    QSettings settings;
    settings.beginGroup("PreferencesDialog");
    settings.beginGroup("PrefInterfaceWidget");
    QString language = settings.value("selectedLanguage", "en").toString();
    settings.endGroup();
    settings.endGroup();

    QTranslator translator;
    translator.load(Paths::translationPath() + "yodownet_" + language);
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
