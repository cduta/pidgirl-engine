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

#include "MoveFile.h"

#include <QFileInfo>
#include <QFile>

#include "Common/Common.h"
#include "Command/Backend/Editor/World/RemoveWorldEntry.h"

MoveFile::MoveFile(const QModelIndex &fromIndex, const QModelIndex &toIndex, QObject *parent)
    : NotUndoable(false, parent)
{
    this->setObjectName("MoveFile");
    this->fromIndex = fromIndex;
    this->toIndex = toIndex;
}

bool MoveFile::execute()
{
    PIDGIRL::writeLog("Moving file");

    QFileInfo fromFileInfo = QFileInfo(this->worldModel->filePath(this->fromIndex));
    QFileInfo toFileInfo = QFileInfo(this->worldModel->filePath(this->toIndex));
    QDir toDir = toFileInfo.dir();
    QString toFileName = fromFileInfo.fileName();

    if(fromFileInfo.isDir())
    {
        PIDGIRL::writeLogDone("[EXIT]");
        return true;
    }

    if(toFileInfo.isDir())
    {
        toDir.cd(toFileInfo.fileName());
    }

    if(fromFileInfo.dir() != toDir)
    {
        while(toDir.exists(toFileName))
        {
            toFileName = QString("Moved To ").append(toFileName);
        }

        toFileInfo = QFileInfo(toDir, toFileName);

        if(!QFile::copy(fromFileInfo.absoluteFilePath(), toFileInfo.absoluteFilePath()))
        {
            PIDGIRL::writeLogFail("Moving the file failed.");
            return false;
        }

        PIDGIRL::writeLogDone();

        this->processor->execute(new RemoveWorldEntry(this->fromIndex, false));
    }
    else
    {
        PIDGIRL::writeLogDone();
    }

    return true;
}


