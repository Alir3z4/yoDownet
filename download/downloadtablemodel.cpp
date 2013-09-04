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

int DownloadTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _downloadList.size();
}

int DownloadTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return parent.isValid() ? 0 : DownloadConstants::Attributes::Downloaded;
}

QVariant DownloadTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || _downloadList.isEmpty()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    QVariant value = QVariant();

    if (index.isValid() && role == Qt::DisplayRole) {
        DownloadHolder *download = _downloadList.at(index.row());

        switch (index.column()) {
        case DownloadConstants::Attributes::Uuid:
            value = download->uuid();
            break;
        case DownloadConstants::Attributes::URL:
            value = download->url();
            break;
        case DownloadConstants::Attributes::SavePath:
            value = download->savePath();
            break;
        case DownloadConstants::Attributes::FileName:
            value = download->fileName();
            break;
        case DownloadConstants::Attributes::Status:
            int progress;
            progress = index.sibling(index.row(), DownloadConstants::Attributes::Progress).data().toString().remove("%").toInt();
            if (progress >= 100) {
                value = this->downloadStatus(3);
            } else {
                value = this->downloadStatus(download->status());
            }
            break;
        case DownloadConstants::Attributes::Progress:
            value = download->progress();
            if (value.toInt() >= 100) {
                value = 100;
            }
            value = value.toString().append("%");
            break;
        case DownloadConstants::Attributes::RemainingTime:
            value = download->remainingTime();
            break;
        case DownloadConstants::Attributes::Speed:
            value = download->speed();
            break;
        case DownloadConstants::Attributes::Added:
            value = download->added();
            break;
        case DownloadConstants::Attributes::Downloaded:
            value = download->downloaded();
            break;
        default:
            break;
        }
    }

    return value;
}

QVariant DownloadTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant value = QAbstractTableModel::headerData(section, orientation, role);

    if (value.isValid() && role == Qt::DisplayRole) {
        switch (section) {
        case DownloadConstants::Attributes::Uuid:
            return tr("Uuid");
            break;
        case DownloadConstants::Attributes::URL:
            return tr("URL");
            break;
        case DownloadConstants::Attributes::SavePath:
            return tr("Save Path");
            break;
        case DownloadConstants::Attributes::FileName:
            return tr("File Name");
            break;
        case DownloadConstants::Attributes::Status:
            return tr("Status");
            break;
        case DownloadConstants::Attributes::Progress:
            return tr("Progress");
            break;
        case DownloadConstants::Attributes::RemainingTime:
            return tr("Remaining Time");
            break;
        case DownloadConstants::Attributes::Speed:
            return tr("Speed");
            break;
        case DownloadConstants::Attributes::Added:
            return tr("Added");
            break;
        case DownloadConstants::Attributes::Downloaded:
            return tr("Downloaded");
            break;
        }
    }

    return value;
}


int DownloadTableModel::downloadListCount() const
{
    return _downloadList.size();
}
int DownloadTableModel::downloadAttributeCount() const
{
    return DownloadConstants::Attributes::Downloaded;
}

Qt::ItemFlags DownloadTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    if (index.row() != index.column()) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

bool DownloadTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        DownloadHolder *download = _downloadList.value(index.row());

        switch (index.column()) {
        case DownloadConstants::Attributes::Uuid:
            download->setUuid(value.toString());
            break;
        case DownloadConstants::Attributes::URL:
            download->setUrl(value.toString());
            break;
        case DownloadConstants::Attributes::SavePath:
            download->setSavePath(value.toString());
            break;
        case DownloadConstants::Attributes::FileName:
            download->setFileName(value.toString());
            break;
        case DownloadConstants::Attributes::Status:
            download->setStatus(value.toInt());
            break;
        case DownloadConstants::Attributes::Progress:
            download->setProgress(value.toInt());
            break;
        case DownloadConstants::Attributes::RemainingTime:
            download->setRemainingTime(value.toString());
            break;
        case DownloadConstants::Attributes::Speed:
            download->setSpeed(value.toString());
            break;
        case DownloadConstants::Attributes::Added:
            download->setAdded(value.toString());
            break;
        case DownloadConstants::Attributes::Downloaded:
            download->setDownloaded(value.toString());
            break;
        default:
            break;
        }

        QModelIndex transposedIndex = createIndex(index.column(), index.row());

        emit dataChanged(index, index);
        emit dataChanged(transposedIndex, transposedIndex);

        return true;
    }

    return false;
}

bool DownloadTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index)
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; row++) {
        DownloadHolder *download = new DownloadHolder(this);
        _downloadList.insert(position, download);
    }

    endInsertRows();
    return true;
}

bool DownloadTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index)
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        // TODO: What out, this needs real implementation.
        _downloadList.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QString DownloadTableModel::downloadStatus(const int status) const
{
    switch(status){
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
