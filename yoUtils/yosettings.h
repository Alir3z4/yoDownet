/****************************************************************************************
** yosettings.h is part of yoDownet
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
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#ifndef YOSETTINGS_H
#define YOSETTINGS_H

#include <QObject>
#include <QtCore/QVariantMap>

class yoSettings : public QObject
{
    Q_OBJECT
public:
    explicit yoSettings(QObject *parent = 0);

    enum Aria2ModeOption{
        AddUriOptions,
        StartOptions
    };

    QString saveDir() const;
    QString logFile() const;
    int maxDownloads() const;
    QString isContinue() const;
    QVariantMap aria2Options(const Aria2ModeOption &mode) const;
    
public slots:
    void load();
    
private slots:
    void setSaveDir(const QString &saveDir);
    void setLogFile(const QString &logFile);
    void setMaxDownloads(const int maxDownloads);
    void setContinue(const QString &isContinue);

private:
    QString _saveDir;
    QString _logFile;
    int _maxdownloads;
    QString _continue;
    
};

#endif // YOSETTINGS_H
