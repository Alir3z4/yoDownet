#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T23:54:04
#
#-------------------------------------------------

QT += core gui network sql

TARGET = yoDownet
TEMPLATE = app

unix{
    DEFINES += PREFIX=$${PREFIX}
    isEmpty(PREFIX){
        message(The PREFIX is empty. So the default value will be used.)
        PREFIX=/usr
        message(PREFIX defined as $$PREFIX)
    }

    target.path = $$PREFIX/bin
    translations.path = $$PREFIX/share/yodownet/translations/
    images.path = $$PREFIX/share/pixmaps
    desktop.path = $$PREFIX/share/applications
    doc.path = $$PREFIX/share/doc/yodownet
    license = $$PREFIX/share/licenses/yodownet/
}

images.files = resource/images/*
desktop.files = installers/yoDownet.desktop
doc.files = doc/C*
license = doc/COPYING
translations.files = translations/*.qm

DEFINES += TRANSLATION_PATH=$$translations.path
DEFINES += DOC_PATH=$$doc.path

INSTALLS += target\
    images \
    desktop \
    doc \
    license \
    translations

#QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    ui/dialog/preferencesdialog.cpp \
    ui/prefwidget/prefdownloaderswidget.cpp \
    util/yomessage.cpp \
    ui/widget/filebrowz.cpp \
    downloader/yodownet.cpp \
    util/fileinfo.cpp \
    ui/dialog/urldialog.cpp \
    util/urlmodel.cpp \
    ui/dialog/aboutdialog.cpp \
    ui/dialog/reportbugdialog.cpp \
    ui/prefwidget/prefinterfacewidget.cpp \
    util/paths.cpp \
    util/languages.cpp \
    ui/widget/systemtrayicon.cpp \
    core/validators/urlvalidator.cpp \
    plus/messages/basemessage.cpp \
    plus/messages/message.cpp \
    core/validators/basevalidator.cpp \
    download/download.cpp \
    download/uri.cpp \
    download/file.cpp \
    download/status.cpp

HEADERS  += ui/mainwindow.h \
    ui/dialog/preferencesdialog.h \
    ui/prefwidget/prefdownloaderswidget.h \
    util/yomessage.h \
    ui/widget/filebrowz.h \
    downloader/yodownet.h \
    util/fileinfo.h \
    ui/dialog/urldialog.h \
    util/urlmodel.h \
    ui/dialog/aboutdialog.h \
    ui/dialog/reportbugdialog.h \
    ui/prefwidget/prefinterfacewidget.h \
    util/paths.h \
    util/languages.h \
    ui/widget/systemtrayicon.h \
    core/validators/urlvalidator.h \
    plus/messages/basemessage.h \
    plus/messages/message.h \
    plus/messages/constants.h \
    core/validators/basevalidator.h \
    download/download.h \
    download/uri.h \
    download/file.h \
    download/status.h

contains(CONFIG, qtestlib){
    DEFINES += TESTING

    SOURCES += core/validators/tests/testurlvalidator.cpp

    HEADERS += core/validators/tests/testurlvalidator.h
}

FORMS    += ui/mainwindow.ui \
    ui/dialog/preferencesdialog.ui \
    ui/prefwidget/prefdownloaderswidget.ui \
    ui/prefwidget/prefdatabasewidget.ui \
    ui/widget/filebrowz.ui \
    ui/dialog/urldialog.ui \
    ui/dialog/aboutdialog.ui \
    ui/dialog/reportbugdialog.ui \
    ui/prefwidget/prefinterfacewidget.ui

TRANSLATIONS += translations/yodownet_en.ts \
    translations/yodownet_et.ts

OTHER_FILES += \
    doc/COPYING \
    LicenseTemplate \
    installers/archlinux/PKGBUILD \
    resource/images/yoDownet_64.svg \
    doc/ChangeLog

RESOURCES += \
    resource/icons.qrc
