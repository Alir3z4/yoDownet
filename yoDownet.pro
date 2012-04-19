#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T23:54:04
#
#-------------------------------------------------

QT       += core gui sql network

TARGET = yoDownet
TEMPLATE = app

target.path = /usr/bin

images.path = /usr/share/pixmaps
images.files = images/*

desktop.path = /usr/share/applications
desktop.files = installers/yoDownet.desktop

license.path = /usr/share/licenses/yodownet
license.files = COPYING

doc.path = /usr/share/doc/yodownet
doc.files = ChangeLog

INSTALLS += target\
    images \
    desktop \
    license \
    doc

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    preferencesdialog.cpp \
    prefdownloaderswidget.cpp \
    prefdatabasewidget.cpp \
    utils/yomessage.cpp \
    importurls.cpp \
    filebrowz.cpp \
    utils/yodatabase.cpp \
    yodownet.cpp \
    utils/fileinfo.cpp \
    utils/status.cpp \
    urldialog.cpp \
    urlmodel.cpp \
    aboutdialog.cpp \
    reportbugdialog.cpp \
    application.cpp \
    prefinterfacewidget.cpp \
    utils/paths.cpp
    utils/paths.cpp \
    utils/languages.cpp
    util/version.cpp

HEADERS  += mainwindow.h \
    preferencesdialog.h \
    prefdownloaderswidget.h \
    prefdatabasewidget.h \
    utils/yomessage.h \
    importurls.h \
    filebrowz.h \
    utils/yodatabase.h \
    yodownet.h \
    utils/fileinfo.h \
    utils/status.h \
    urldialog.h \
    urlmodel.h \
    aboutdialog.h \
    reportbugdialog.h
    prefinterfacewidget.h \
    utils/paths.h
    utils/paths.h \
    utils/languages.h
    util/version.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    prefdownloaderswidget.ui \
    prefdatabasewidget.ui \
    importurls.ui \
    filebrowz.ui \
    urldialog.ui \
    aboutdialog.ui \
    reportbugdialog.ui

TRANSLATIONS += translations/yodownet_en.ts \
    translations/yodownet_et.ts

OTHER_FILES += \
    COPYING \
    LicenseTemplate \
    installers/archlinux/PKGBUILD \
    images/yoDownet_64.svg \
    ChangeLog \
    sql/sqlite_0.sql \
    sql/sqlite_1.sql

RESOURCES += \
    icons.qrc \
    DatabaseMigrations.qrc
