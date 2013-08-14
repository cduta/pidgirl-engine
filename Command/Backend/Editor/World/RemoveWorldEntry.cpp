/*
 * A flexible rogue-like engine with easy-to-use mouse interface, editor,
 * solo, hotseat, network multiplayer and E-Mail game functionality in mind.
 * Copyright (C) 2013  Ryoga Unryu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RemoveWorldEntry.h"

#include <QMessageBox>

#include "Common/Common.h"

RemoveWorldEntry::RemoveWorldEntry(const QModelIndex &index, bool ask, QObject *parent)
    : NotUndoable(false, parent)
{
    this->setObjectName("RemoveWorldEntry");
    this->index = index;
    this->mayAsk = ask;
}

bool RemoveWorldEntry::execute()
{
    PIDGIRL::writeLog("Removing World Entry");

    QFileInfo fileInfo = QFileInfo(this->worldModel->filePath(this->index));
    QString entryName = fileInfo.fileName();
    QDir dir = fileInfo.dir();

    if(!dir.exists(entryName))
    {
        PIDGIRL::writeLogFail(QString("World Entry doesn't exist. Entry Name: ").append(entryName));
        return false;
    }

    QString type;

    if(fileInfo.isDir())
    {
        type = tr("Folder");
    }
    else
    {
        type = tr("File");
    }

    if(this->mayAsk)
    {
        int clicked = QMessageBox::question(0,
                                            tr("Removing ").append(type).append("..."),
                                            tr("Do you really want to remove this ").append(type).append(tr("?")),
                                            tr("Yes"),
                                            tr("No"));
        if(clicked != 0)
        {
            PIDGIRL::writeLogDone("[EXIT]");
            return true;
        }
    }

    if(fileInfo.isDir())
    {
        if(!(this->worldModel->remove(this->index)))
        {
            PIDGIRL::writeLogFail(QString("Removing the directory failed. Entry Name: ").append(entryName));
            return false;
        }
    }
    else
    {
        if(!dir.remove(entryName))
        {
            PIDGIRL::writeLogFail(QString("Removing the file failed. Entry Name: ").append(entryName));
            return false;
        }
    }

    PIDGIRL::writeLogDone();

    return true;
}
