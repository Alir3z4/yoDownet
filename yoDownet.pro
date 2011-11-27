#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T23:54:04
#
#-------------------------------------------------

QT       += core gui

TARGET = yoDownet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    preferencesdialog.cpp \
    prefdownloaderswidget.cpp \
    prefdatabasewidget.cpp \
    yoUtils/yomessage.cpp \
    importurls.cpp

HEADERS  += mainwindow.h \
    preferencesdialog.h \
    prefdownloaderswidget.h \
    prefdatabasewidget.h \
    yoUtils/yomessage.h \
    importurls.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    prefdownloaderswidget.ui \
    prefdatabasewidget.ui \
    importurls.ui

OTHER_FILES += \
    sql/yodownet_mysql_model.mwb \
    sql/yodownet_mysql_db_000.sql
