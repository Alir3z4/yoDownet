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
    filebrowz.cpp \
    yoUtils/yodatabase.cpp \
    uridialog.cpp

HEADERS  += mainwindow.h \
    preferencesdialog.h \
    prefdownloaderswidget.h \
    prefdatabasewidget.h \
    yoUtils/yomessage.h \
    importurls.h \
    filebrowz.h \
    yoUtils/yodatabase.h \
    uridialog.h

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
