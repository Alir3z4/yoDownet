/****************************************************************************************
** prefdownloaderswidget.h is part of yoDownet
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

#ifndef PREFDOWNLOADERSWIDGET_H
#define PREFDOWNLOADERSWIDGET_H

#include <QWidget>

namespace Ui {
class PrefDownloadersWidget;
}

class PrefDownloadersWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrefDownloadersWidget(QWidget *parent = 0);
    ~PrefDownloadersWidget();

    QString saveDir()const;
    QString logFile() const;
    int maxDownloads() const;
    bool isContinue() const;

public slots:
    void setSaveDir(const QString &saveDir);
    void setLogFile(const QString &logFile);
    void setMaxDownloads(const int maxDownloads);
    void setContinue(bool isContinue);

    
private:
    Ui::PrefDownloadersWidget *ui;
};

#endif // PREFDOWNLOADERSWIDGET_H
