/****************************************************************************************
** changeduris.h is part of yoDownet
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
** along with this program; if not, If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#ifndef CHANGEDURIS_H
#define CHANGEDURIS_H

#include <QObject>

class ChangedUris : public QObject
{
    Q_OBJECT
public:
    explicit ChangedUris(QObject *parent = 0);
    
    void setDeleted(const int &deleted);
    void setAdded(const int &added);

    int deleted() const;
    int added() const;

private:
    int _deleted;
    int _added;
    
};

#endif // CHANGEDURIS_H
