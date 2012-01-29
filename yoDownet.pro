#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T23:54:04
#
#-------------------------------------------------

QT       += core gui sql

TARGET = yoDownet
TEMPLATE = app
LIBS += -lxmlrpc++ \
    -lxmlrpc_client++


SOURCES += main.cpp\
        mainwindow.cpp \
    preferencesdialog.cpp \
    prefdownloaderswidget.cpp \
    prefdatabasewidget.cpp \
    yoUtils/yomessage.cpp \
    importurls.cpp \
    addurldialog.cpp \
    yoDownloaders/aria2c.cpp \
    filebrowz.cpp \
    yoUtils/yodatabase.cpp \
    downloader.cpp

HEADERS  += mainwindow.h \
    preferencesdialog.h \
    prefdownloaderswidget.h \
    prefdatabasewidget.h \
    yoUtils/yomessage.h \
    importurls.h \
    addurldialog.h \
    yoDownloaders/aria2c.h \
    filebrowz.h \
    yoUtils/yodatabase.h \
    downloader.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    prefdownloaderswidget.ui \
    prefdatabasewidget.ui \
    importurls.ui \
    addurldialog.ui \
    filebrowz.ui

OTHER_FILES += \
    sql/yodownet_sqlite_db_000.sql
