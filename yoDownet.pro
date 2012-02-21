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

INSTALLS += target\
    images \
    desktop \
    license

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    preferencesdialog.cpp \
    prefdownloaderswidget.cpp \
    prefdatabasewidget.cpp \
    yoUtils/yomessage.cpp \
    importurls.cpp \
    filebrowz.cpp \
    yoUtils/yodatabase.cpp \
    yodownet.cpp \
    yoUtils/fileinfo.cpp \
    yoUtils/status.cpp \
    urldialog.cpp \
    urlmodel.cpp \
    aboutdialog.cpp \
    reportbugdialog.cpp

HEADERS  += mainwindow.h \
    preferencesdialog.h \
    prefdownloaderswidget.h \
    prefdatabasewidget.h \
    yoUtils/yomessage.h \
    importurls.h \
    filebrowz.h \
    yoUtils/yodatabase.h \
    yodownet.h \
    yoUtils/fileinfo.h \
    yoUtils/status.h \
    urldialog.h \
    urlmodel.h \
    aboutdialog.h \
    reportbugdialog.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    prefdownloaderswidget.ui \
    prefdatabasewidget.ui \
    importurls.ui \
    filebrowz.ui \
    urldialog.ui \
    aboutdialog.ui \
    reportbugdialog.ui

OTHER_FILES += \
    COPYING \
    LicenseTemplate \
    sql/yodownet_sqlite_db.sql \
    installers/archlinux/PKGBUILD \
    images/yoDownet_64.svg

RESOURCES += \
    icons.qrc
