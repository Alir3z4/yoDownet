#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T23:54:04
#
#-------------------------------------------------

QT += core gui sql network

TARGET = yoDownet
TEMPLATE = app

DEFINES +=TRANSLATION_PATH=$${TRANSLATION_PATH}
DEFINES +=LICENSE_PATH=$${LICENSE_PATH}
DEFINES +=SQLSCRIPT_PATH=$${SQLSCRIPT_PATH}

REQUIRED_MSG = is required :|

isEmpty(TRANSLATION_PATH){
    error(TRANSLATION_PATH $$REQUIRED_MSG)
}
isEmpty(LICENSE_PATH){
    error(LICENSE_PATH $$REQUIRED_MSG)
}
isEmpty(SQLSCRIPT_PATH){
    error(SQLSCRIPT_PATH $$REQUIRED_MSG)
}

for(define, DEFINES){
    message($$define)
}

unix{

    target.path = /usr/bin

    images.path = /usr/share/pixmaps
    images.files = resource/images/*

    desktop.path = /usr/share/applications
    desktop.files = installers/yoDownet.desktop

    doc.path = /usr/share/doc/yodownet
    doc.files = doc/ChangeLog
}

license.path = $$LICENSE_PATH
license.files = doc/COPYING

translations.path = $$TRANSLATION_PATH
translations.files = translations/*.qm

sqlscript.path = $$SQLSCRIPT_PATH
sqlscript.files = resource/sql/*

INSTALLS += target\
    images \
    desktop \
    license \
    doc \
    translations \
    sqlscript

#QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    ui/preferencesdialog.cpp \
    ui/prefwidget/prefdownloaderswidget.cpp \
    ui/prefwidget/prefdatabasewidget.cpp \
    util/yomessage.cpp \
    ui/widget/filebrowz.cpp \
    util/yodatabase.cpp \
    downloader/yodownet.cpp \
    util/fileinfo.cpp \
    util/status.cpp \
    ui/urldialog.cpp \
    util/urlmodel.cpp \
    ui/aboutdialog.cpp \
    ui/reportbugdialog.cpp \
    ui/prefwidget/prefinterfacewidget.cpp \
    util/paths.cpp \
    util/languages.cpp \
    ui/widget/systemtrayicon.cpp \
    core/validators/regexvalidator.cpp \
    core/validators/urlvalidator.cpp

HEADERS  += ui/mainwindow.h \
    ui/preferencesdialog.h \
    ui/prefwidget/prefdownloaderswidget.h \
    ui/prefwidget/prefdatabasewidget.h \
    util/yomessage.h \
    ui/widget/filebrowz.h \
    util/yodatabase.h \
    downloader/yodownet.h \
    util/fileinfo.h \
    util/status.h \
    ui/urldialog.h \
    util/urlmodel.h \
    ui/aboutdialog.h \
    ui/reportbugdialog.h \
    ui/prefwidget/prefinterfacewidget.h \
    util/paths.h \
    util/languages.h \
    ui/widget/systemtrayicon.h \
    core/validators/regexvalidator.h \
    core/validators/urlvalidator.h

    SOURCES += core/validators/tests/testurlvalidator.cpp

    HEADERS += core/validators/tests/testurlvalidator.h
FORMS    += ui/mainwindow.ui \
    ui/preferencesdialog.ui \
    ui/prefwidget/prefdownloaderswidget.ui \
    ui/prefwidget/prefdatabasewidget.ui \
    ui/widget/filebrowz.ui \
    ui/urldialog.ui \
    ui/aboutdialog.ui \
    ui/reportbugdialog.ui \
    ui/prefwidget/prefinterfacewidget.ui

TRANSLATIONS += translations/yodownet_en.ts \
    translations/yodownet_et.ts

OTHER_FILES += \
    doc/COPYING \
    LicenseTemplate \
    installers/archlinux/PKGBUILD \
    resource/images/yoDownet_64.svg \
    doc/ChangeLog \
    resource/sql/sqlite_0.sql \
    resource/sql/sqlite_1.sql \
    resource/sql/sqlite_2.sql

RESOURCES += \
    resource/icons.qrc
