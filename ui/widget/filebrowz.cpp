/****************************************************************************************
** filebrowz.cpp is part of yoDownet
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

#include "filebrowz.h"
#include "ui_filebrowz.h"

FileBrowz::FileBrowz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileBrowz)
{
    ui->setupUi(this);

    // make GetFileName mode to default
    setBrowzType(GetFileName);
    setOptions(0);

    // set home directory on pathEdit
    ui->pathEdit->setText(QDir::homePath());
}

FileBrowz::~FileBrowz()
{
    delete ui;
}

QString FileBrowz::caption() const
{
    return _caption;
}

QString FileBrowz::filter() const
{
    return _filter;
}

QString FileBrowz::browzPath() const
{
    return ui->pathEdit->text();
}

FileBrowz::BrowzType FileBrowz::browzType() const
{
    return _type;
}

QFileDialog::Options FileBrowz::options() const
{
    return _options;
}

void FileBrowz::setCaption(const QString &caption)
{
    _caption = caption;
}

void FileBrowz::setFilter(const QString &filter)
{
    _filter = filter;
}

void FileBrowz::setBrowzType(FileBrowz::BrowzType type)
{
    _type = type;
}

void FileBrowz::setOptions(QFileDialog::Options options)
{
    _options = options;
}

void FileBrowz::setBrowzPath(const QString &browztPath)
{
    /* TODO: is writable or what ?
     * There is some refrences that can help to fix this issue.
     *
     * http://qt-project.org/forums/viewthread/645
     * http://lists.trolltech.com/qt-interest/2006-07/thread00412-0.html
     * http://www.qtforum.org/article/2169/folder-write-permission.html
     *
     *  For now I'm thinking about creating a temporary file just for test
     * to find out the seleted directory is writable or not.
     */
    ui->pathEdit->setText((browztPath.isEmpty()) ? QDir::homePath() : browztPath);
}

void FileBrowz::setPath(const QString &path)
{
    ui->pathEdit->setText(path);
}

void FileBrowz::on_browzButton_clicked()
{
    QString result;

    if(browzType() == GetDirectory) {
        result = QFileDialog::getExistingDirectory(
                    this, caption(), ui->pathEdit->text());

    } else if(browzType() == GetFileName) {
        result = QFileDialog::getOpenFileName(this, caption(), ui->pathEdit->text(), filter());
    }

    if(!result.isEmpty()) {
        QString oldFile = ui->pathEdit->text();
        ui->pathEdit->setText(result);
        if (oldFile != result) emit fileChanged(result);
    }
}
