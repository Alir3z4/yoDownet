#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T23:54:04
#
#-------------------------------------------------

QT += core network


message(Compiling against Qt version: $$QT_MAJOR_VERSION)

greaterThan(QT_MAJOR_VERSION, 4) {
    message(Adding widgets module)
    QT += widgets
}


DEFINES +=QT_MAJOR_VERSION=$$QT_MAJOR_VERSION

TARGET = yoDownet
TEMPLATE = app

unix{
    DEFINES += PREFIX=$${PREFIX}
    isEmpty(PREFIX){
        message(The PREFIX is empty. The default value will be used.)
        PREFIX=/usr
        message(PREFIX defined as $$PREFIX)
    }

    target.path = $$PREFIX/bin
    translations.path = $$PREFIX/share/yodownet/translations/
    images.path = $$PREFIX/share/pixmaps
    desktop.path = $$PREFIX/share/applications
    doc.path = $$PREFIX/share/doc/yodownet
    license.path = $$PREFIX/share/licenses/yodownet/

    message(Target: $$target.path)
    message(Translations: $$translations.path)
    message(Images: $$images.path)
    message(Desktop: $$desktop.path)
    message(Documents: $$doc.path)
    message(License: $$license.path)
}

images.files = resource/images/*
desktop.files = installers/yoDownet.desktop
doc.files = doc/C*
license.files = doc/COPYING
translations.files = translations/*.qm


DEFINES += TRANSLATION_PATH=$$translations.path
DEFINES += DOC_PATH=$$doc.path

INSTALLS += target\
    images \
    desktop \
    doc \
    license \
    translations

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    ui/dialog/preferencesdialog.cpp \
    ui/prefwidget/prefdownloaderswidget.cpp \
    ui/widget/filebrowz.cpp \
    downloader/yodownet.cpp \
    ui/dialog/urldialog.cpp \
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
    download/status.cpp \
    download/downloadtablemodel.cpp \
    download/downloadholder.cpp \
    core/logme.cpp \
    downloader/ratecontroller.cpp \
    downloader/ratecontrollertcpsocket.cpp

HEADERS  += ui/mainwindow.h \
    ui/dialog/preferencesdialog.h \
    ui/prefwidget/prefdownloaderswidget.h \
    ui/widget/filebrowz.h \
    downloader/yodownet.h \
    ui/dialog/urldialog.h \
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
    download/status.h \
    download/downloadtablemodel.h \
    download/downloadholder.h \
    core/logme.h \
    download/downloadconstants.h \
    downloader/ratecontroller.h \
    downloader/ratecontrollertcpsocket.h

contains(CONFIG, testlib){
    DEFINES += TESTING

    SOURCES += core/validators/tests/testurlvalidator.cpp \
        download/tests/testdownload.cpp

    HEADERS += core/autotest.h \
        core/validators/tests/testurlvalidator.h \
        download/tests/testdownload.h
}

FORMS    += ui/mainwindow.ui \
    ui/dialog/preferencesdialog.ui \
    ui/prefwidget/prefdownloaderswidget.ui \
    ui/widget/filebrowz.ui \
    ui/dialog/urldialog.ui \
    ui/dialog/aboutdialog.ui \
    ui/dialog/reportbugdialog.ui \
    ui/prefwidget/prefinterfacewidget.ui

TRANSLATIONS += translations/yodownet_en.ts \
    translations/yodownet_et.ts \
    translations/yodownet_fa.ts \
    translations/yodownet_tr.ts \
    translations/yodownet_vi.ts \
    translations/yodownet_nl.ts \
    translations/yodownet_cs.ts

OTHER_FILES += \
    doc/COPYING \
    LicenseTemplate \
    installers/archlinux/PKGBUILD \
    resource/images/yoDownet_64.png \
    doc/ChangeLog \
    README.md

RESOURCES += \
    resource/icons.qrc
