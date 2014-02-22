/****************************************************************************************
** main.cpp is part of yoDownet
**
** Copyright 2011, 2012, 2013, 2014 Alireza Savand <alireza.savand@gmail.com>
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
#include "core/logme.h"
#include "util/paths.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    a.setApplicationName(QObject::tr("yoDownet"));
    a.setApplicationVersion("2014.02.21");
    a.setOrganizationName("Alir3z4");
    a.setOrganizationDomain("yodownet.sourceforge.net");
    a.setApplicationDisplayName(a.applicationName());

    LogMe logger;
    logger.setClassName("Main");
    logger.info("yoDownet Started");

    QIcon appIcon;
    appIcon.addFile(QString(":/icons/images/yoDownet_64.svg"), QSize(), QIcon::Normal, QIcon::Off);
    a.setWindowIcon(appIcon);

    QSettings settings;
    settings.beginGroup("PreferencesDialog");
    settings.beginGroup("PrefInterfaceWidget");
    QString language = settings.value("selectedLanguage", "en").toString();
    settings.endGroup();
    settings.endGroup();

    logger.info("Loading translations");
    QTranslator translator;
    translator.load(Paths::translationPath() + "yodownet_" + language);
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}

#endif
