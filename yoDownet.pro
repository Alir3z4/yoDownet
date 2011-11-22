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
    preferencesdialog.cpp

HEADERS  += mainwindow.h \
    preferencesdialog.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui

OTHER_FILES += \
    sql/yodownet_mysql_model.mwb \
    sql/yodownet_mysql_db_000.sql
