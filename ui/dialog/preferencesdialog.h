/****************************************************************************************
** preferencesdialog.cpp is part of yoDownet
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

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "ui/prefwidget/prefdownloaderswidget.h"
#include "ui/prefwidget/prefinterfacewidget.h"

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();
    
private slots:
    void on_buttonBox_accepted();
    void saveSettings();
    void closeEvent(QCloseEvent *);

private:
    Ui::PreferencesDialog *ui;

    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *applyButton;

    PrefDownloadersWidget *prefDler;
    PrefInterfaceWidget *prefInt;

    void addSection(QWidget *w);

    // Load settings
    void loadSettings();
};

#endif // PREFERENCESDIALOG_H
