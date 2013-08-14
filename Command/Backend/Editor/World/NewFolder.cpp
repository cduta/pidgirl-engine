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

#include "NewFolder.h"

#include "Common/Common.h"

#include <QInputDialog>

NewFolder::NewFolder(const QModelIndex &index, QObject *parent)
    : NotUndoable(false, parent)
{
    this->setObjectName("NewFolder");
    this->index = index;
}

bool NewFolder::execute()
{
    PIDGIRL::writeLog("Creating new folder file");

    bool ok;
    QFileInfo fileInfo = QFileInfo(this->worldModel->filePath(this->index));
    QDir dir = fileInfo.dir();

    if(fileInfo.isDir())
    {
        dir.cd(fileInfo.fileName());
    }

    QString directoryName = QInputDialog::getText(0,
                                                  tr("New Folder..."),
                                                  tr("Enter the name of the new folder."),
                                                  QLineEdit::Normal,
                                                  tr("New Folder"),
                                                  &ok);

    if(!ok)
    {
        PIDGIRL::writeLogDone("[EXIT]");
        return true;
    }    

    int i = 1;
    QString newDirectoryName = directoryName;
    while(dir.exists(newDirectoryName))
    {
        newDirectoryName = directoryName;
        newDirectoryName = newDirectoryName.append(QString::number(i));
        ++i;
    }

    if(!dir.mkdir(newDirectoryName))
    {
        PIDGIRL::writeLogFail(QString("Creating the directory failed. DirectoryName: ").append(newDirectoryName));
        return false;
    }

    PIDGIRL::writeLogDone();

    return true;
}

