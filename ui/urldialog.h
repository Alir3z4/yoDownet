/****************************************************************************************
** urldialog.h is part of yoDownet
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

#ifndef URLDIALOG_H
#define URLDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QPushButton>

namespace Ui {
class UrlDialog;
}

class UrlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UrlDialog(QWidget *parent = 0);
    ~UrlDialog();

    QStringList urls() const;

private slots:
    void on_urlsTextEdit_textChanged();
    void on_resetButton_clicked();

private:
    Ui::UrlDialog *ui;

    QPushButton *resetButton;
};

#endif // URLDIALOG_H
