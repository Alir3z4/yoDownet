#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T23:54:04
#
#-------------------------------------------------

QT += core gui sql network

TARGET = yoDownet
TEMPLATE = app

DEFINES += TRANSLATION_PATH=$${TRANSLATION_PATH}

# Messages
message(Translation path : $$TRANSLATION_PATH)

target.path = /usr/bin

images.path = /usr/share/pixmaps
images.files = resource/images/*

desktop.path = /usr/share/applications
desktop.files = installers/yoDownet.desktop

license.path = /usr/share/licenses/yodownet
license.files = doc/COPYING

doc.path = /usr/share/doc/yodownet
doc.files = doc/ChangeLog

translations.path = $$TRANSLATION_PATH
translations.files = translations/*.qm

INSTALLS += target\
    images \
    desktop \
    license \
    doc \
    translations

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
    util/version.cpp

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
    util/version.h

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
    resource/icons.qrc \
    resource/DatabaseMigrations.qrc
