#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T23:54:04
#
#-------------------------------------------------

QT       += core gui sql network

TARGET = yoDownet
TEMPLATE = app


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
    urlmodel.cpp

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
    urlmodel.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    prefdownloaderswidget.ui \
    prefdatabasewidget.ui \
    importurls.ui \
    filebrowz.ui \
    urldialog.ui

TRANSLATIONS += translations/yoDownet_fa.ts

OTHER_FILES += \
    COPYING \
    LicenseTemplate \
    sql/yodownet_sqlite_db.sql \
    installers/archlinux/PKGBUILD \
    images/yoDownet_64.svg

RESOURCES += \
    icons.qrc
