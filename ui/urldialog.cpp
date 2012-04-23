/****************************************************************************************
** urldialog.cpp is part of yoDownet
**
** Copyright 2011, 2012 Alireza Savand <alireza.savand@gmail.com>
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

#include "urldialog.h"
#include "ui_urldialog.h"

UrlDialog::UrlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UrlDialog)
{
    ui->setupUi(this);

    resetButton = ui->buttonBox->button(QDialogButtonBox::Reset);

    connect(resetButton, SIGNAL(clicked()), this, SLOT(on_resetButton_clicked()));
}

UrlDialog::~UrlDialog()
{
    delete ui;
}

QStringList UrlDialog::urls() const
{
    QStringList urlList;
    QString urlText = ui->urlsTextEdit->document()->toPlainText();
    QTextStream textStream(&urlText);
    while(!textStream.atEnd()){
        urlList << textStream.readLine();
    }
    return urlList;
}

void urlDialog::on_urlEdit_textChanged()
{
    if(!ui->urlEdit->text().isEmpty())
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setDisabled(true);
}

void UrlDialog::on_resetButton_clicked()
{
    ui->urlsTextEdit->document()->clear();
}
