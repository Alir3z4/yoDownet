#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T23:54:04
#
#-------------------------------------------------

QT       += core gui sql xml network

TARGET = yoDownet
TEMPLATE = app
LIBS += -lmaia


SOURCES += main.cpp\
        mainwindow.cpp \
    preferencesdialog.cpp \
    prefdownloaderswidget.cpp \
    prefdatabasewidget.cpp \
    yoUtils/yomessage.cpp \
    importurls.cpp \
    yoDownloaders/aria2c.cpp \
    filebrowz.cpp \
    yoUtils/yodatabase.cpp \
    downloader.cpp \
    yoUtils/fileinfo.cpp \
    yoUtils/status.cpp \
    yoUtils/options.cpp \
    yoUtils/bittorrent.cpp \
    yoUtils/uristatus.cpp \
    yoUtils/downloaderversion.cpp \
    yoUtils/peer.cpp \
    yoUtils/fault.cpp \
    yoUtils/changeduris.cpp \
    uridialog.cpp \
    yoUtils/yosettings.cpp

HEADERS  += mainwindow.h \
    preferencesdialog.h \
    prefdownloaderswidget.h \
    prefdatabasewidget.h \
    yoUtils/yomessage.h \
    importurls.h \
    yoDownloaders/aria2c.h \
    filebrowz.h \
    yoUtils/yodatabase.h \
    downloader.h \
    yoUtils/fileinfo.h \
    yoUtils/status.h \
    yoUtils/options.h \
    yoUtils/bittorrent.h \
    yoUtils/uristatus.h \
    yoUtils/downloaderversion.h \
    yoUtils/peer.h \
    yoUtils/fault.h \
    yoUtils/changeduris.h \
    uridialog.h \
    yoUtils/yosettings.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    prefdownloaderswidget.ui \
    prefdatabasewidget.ui \
    importurls.ui \
    filebrowz.ui \
    uridialog.ui

TRANSLATIONS += translations/yoDownet_fa.ts

OTHER_FILES += \
    COPYING \
    LicenseTemplate \
    sql/yodownet_sqlite_db.sql \
    installers/archlinux/PKGBUILD \
    images/yoDownet_64.svg

RESOURCES += \
    icons.qrc
