/****************************************************************************************
** urlmodel.cpp is part of yoDownet
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

#include "urlmodel.h"
#include <QTimer>

UrlModel::UrlModel(QObject *parent) :
    QSqlTableModel(parent)
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setTable("urls");
    select();

    QTimer *submitTimer = new QTimer(this);
    connect(submitTimer, SIGNAL(timeout()), this, SLOT(submitAll()));
    submitTimer->start(25000);
}

QVariant UrlModel::data(const QModelIndex &idx, int role) const
{
    QVariant value = QSqlTableModel::data(idx, role);
    if(role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;
    if(value.isValid() && role == Qt::DisplayRole){
        if(idx.column() == progress)
            return value.toString().append("%");
        else if(idx.column() == status)
            return downloadStatus(value.toInt());
    }
    return value;
}

QVariant UrlModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant value = QSqlTableModel::headerData(section, orientation, role);
    if(value.isValid() && role == Qt::DisplayRole){
        switch(section){
        case url:
            return tr("URL");
            break;
        case save_path:
            return tr("Save Path");
            break;
        case status:
            return tr("Status");
            break;
        case progress:
            return tr("Progress");
            break;
        case remaining_time:
            return tr("Remaining Time");
            break;
        case speed:
            return tr("Speed");
            break;
        case created_at:
            return tr("Added");
            break;
        case updated_at:
            return tr("Modified");
            break;
        }
    }
    return value;
}

QString UrlModel::downloadStatus(const int mode) const
{
    switch(mode){
    case 0:
        return tr("Idle");
        break;
    case 1:
        return tr("Starting");
        break;
    case 2:
        return tr("Downloading");
        break;
    case 3:
        return tr("Finished");
        break;
    case 4:
        return tr("Failed");
        break;
    }
    return tr("Unknown Status");
}
