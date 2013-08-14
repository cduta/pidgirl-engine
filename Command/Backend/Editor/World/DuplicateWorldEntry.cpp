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

#include "DuplicateWorldEntry.h"

#include "Common/Common.h"

DuplicateWorldEntry::DuplicateWorldEntry(const QModelIndex &index, QObject *parent)
    : NotUndoable(false, parent)
{
    this->setObjectName("DuplicateWorldEntry");
    this->index = index;
}

bool DuplicateWorldEntry::execute()
{
    PIDGIRL::writeLog("Duplicate world entry");

    QString oldEntry = this->worldModel->filePath(this->index);
    QFileInfo fileInfo = QFileInfo(oldEntry);
    QString entryName = fileInfo.fileName();

    while(fileInfo.dir().exists(entryName))
    {
        entryName = QString("Copy of ").append(entryName);
    }

    fileInfo = fileInfo.dir().filePath(entryName);

    if(!QFile::copy(oldEntry, fileInfo.absoluteFilePath()))
    {
        PIDGIRL::writeLogFail(QString("Duplicating a world entry failed. EntryName: ").append(entryName));
        return false;
    }

    PIDGIRL::writeLogDone();

    return true;
}
