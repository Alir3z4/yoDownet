/****************************************************************************************
** downloadtablemodel.cpp is part of yoDownet
**
** Copyright 2013 Alireza Savand <alireza.savand@gmail.com>
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

#include "downloadtablemodel.h"

DownloadTableModel::DownloadTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

DownloadTableModel::DownloadTableModel(QList<Download> downloadList, QObject *parent)
{
    _downloadList = downloadList;
}

int DownloadTableModel::rowCount(const QModelIndex &parent) const
{
}

int DownloadTableModel::columnCount(const QModelIndex &parent) const
{
}

QVariant DownloadTableModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QAbstractTableModel::data(index, role);

    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    if (value.isValid() && role == Qt::DisplayRole) {
        if (index.column() == Progress) {
            if (value.toInt() >= 100)
                value = 100;
            return value.toString().append("%");
        } else if (index.column() == Status) {
            int prg = index.sibling(index.row(), 5).data().toString().remove("%").toInt();
            if (prg  >= 100)
                return downloadStatus(3);
            return downloadStatus(value.toInt());
        }
    }

    return value;
}

QVariant DownloadTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant value = QAbstractTableModel::headerData(section, orientation, role);

    if (value.isValid() && role == Qt::DisplayRole) {
        switch (section) {
        case Uuid:
            return tr("Uuid");
            break;
        case URL:
            return tr("URL");
            break;
        case SavePath:
            return tr("Save Path");
            break;
        case FileName:
            return tr("File Name");
            break;
        case Status:
            return tr("Status");
            break;
        case Progress:
            return tr("Progress");
            break;
        case RemainingTime:
            return tr("Remaining Time");
            break;
        case Speed:
            return tr("Speed");
            break;
        case Added:
            return tr("Added");
            break;
        case Downloaded:
            return tr("Downloaded");
            break;
        }
    }

    return value;
}

Qt::ItemFlags DownloadTableModel::flags(const QModelIndex &index) const
{
}

bool DownloadTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
}

bool DownloadTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
}

bool DownloadTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
}

QString DownloadTableModel::downloadStatus(const int status) const
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
    case 5:
        return tr("Paused");
        break;
    }
    return tr("Unknown Status");
}
