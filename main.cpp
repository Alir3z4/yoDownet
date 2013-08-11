/****************************************************************************************
** main.cpp is part of yoDownet
**
** Copyright 2011, 2012, 2013 Alireza Savand <alireza.savand@gmail.com>
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

#ifdef TESTING
#include "core/autotest.h"
TEST_MAIN
#else

#include <QtWidgets/QApplication>
#include <QtCore/QSettings>
#include <QtCore/QTranslator>
#include <QtGui/QIcon>
#include "util/paths.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    a.setApplicationName(QObject::tr("yoDownet"));
    a.setApplicationVersion("2012.05.11");
    a.setOrganizationName("Alir3z4");
    a.setOrganizationDomain("yodownet.sourceforge.net");
    a.setApplicationDisplayName(a.applicationName());

    QIcon appIcon;
    appIcon.addFile(QStringLiteral(":/icons/images/yoDownet_64.svg"), QSize(), QIcon::Normal, QIcon::Off);
    a.setWindowIcon(appIcon);

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

#endif
