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

#include "RenameWorldEntry.h"

#include <QInputDialog>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"

RenameWorldEntry::RenameWorldEntry(const QModelIndex &index, QObject *parent)
    : NotUndoable(false, parent)
{
    this->setObjectName("RenameWorldEntry");
    this->index = index;
}

bool RenameWorldEntry::execute()
{
    PIDGIRL::writeLog("Rename world entry");

    bool ok;
    QString filePath = this->worldModel->filePath(this->index);
    QFileInfo fileInfo = QFileInfo(filePath);
    QString oldName = fileInfo.fileName();
    QString renamableName = oldName;

    if(!fileInfo.isDir())
    {
        renamableName = renamableName.remove(renamableName.size() - PIDGIRL::MAP_SUFFIX.size(), PIDGIRL::MAP_SUFFIX.size());
    }

    QString newName = QInputDialog::getText(0,
                                            tr("Rename..."),
                                            tr("Rename the entry."),
                                            QLineEdit::Normal,
                                            renamableName,
                                            &ok);

    if(!ok)
    {
        PIDGIRL::writeLogDone("[EXIT]");
        return true;
    }

    if(!fileInfo.isDir())
    {
        if(!newName.endsWith(PIDGIRL::MAP_SUFFIX))
        {
            newName.append(PIDGIRL::MAP_SUFFIX);
        }
    }

    while(QDir(fileInfo.dir()).exists(newName))
    {
        newName = QString("Renamed ").append(newName);
    }

    if(!fileInfo.dir().rename(oldName, newName))
    {
        PIDGIRL::writeLogFail(QString("Renaming world entry failed. OldName: ").append(fileInfo.fileName()).append(" NewName: ").append(newName));
        return false;
    }

    QFileInfo newFileInfo(fileInfo.dir().filePath(newName));

    if(!newFileInfo.isDir() && this->mapModel->getFileInfo().absoluteFilePath() != newFileInfo.absoluteFilePath())
    {
        this->mapModel->setFileInfo(QFileInfo(newFileInfo.absoluteFilePath()));
    }

    PIDGIRL::writeLogDone();

    return true;
}
