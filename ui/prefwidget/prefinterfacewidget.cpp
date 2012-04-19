/****************************************************************************************
** prefinterfacewidget.cpp is part of yoDownet
**
** Copyright 2012 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "prefinterfacewidget.h"
#include "ui_prefinterfacewidget.h"
#include "util/languages.h"
#include "util/paths.h"
#include <QDir>

PrefInterfaceWidget::PrefInterfaceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrefInterfaceWidget)
{
    ui->setupUi(this);

    // Fill the language comboFuck :|
    createLanguageComboBox();
}

PrefInterfaceWidget::~PrefInterfaceWidget()
{
    delete ui;
}

QString PrefInterfaceWidget::selectedLanguage() const
{
    QRegExp rx("\\((.*)\\)");
    int pos = 0;
    QString selectedLang;
    while ((pos = rx.indexIn(ui->languageComboBox->currentText(), pos)) != -1) {
        selectedLang = rx.cap(1);
        pos += rx.matchedLength();
    }
    return selectedLang;
}

int PrefInterfaceWidget::languageComboBoxCurrentIndex() const
{
    return ui->languageComboBox->currentIndex();
}

void PrefInterfaceWidget::setLanguageComboBoxCurrentIndex(const int &currentIndex)
{
    ui->languageComboBox->setCurrentIndex(currentIndex);
}

void PrefInterfaceWidget::createLanguageComboBox()
{
    QMap<QString, QString> m = Languages::translations();

    // Language ComboFuck
    QDir translationDir = Paths::translationPath();
    QStringList languages = translationDir.entryList(QStringList() << "*.qm");
    QRegExp rxLang("yodownet_(.*)\\.qm");
    ui->languageComboBox->clear();
    for(int n=0; n < languages.count(); n++){
        if(rxLang.indexIn(languages[n]) > -1){
            QString l = rxLang.cap(1);
            QString text = l;
            if(m.contains(l)) text = m[l] + " ("+l+")";
            ui->languageComboBox->addItem(text, l);
        }
    }
}
