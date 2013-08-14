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

#include "NewMapFile.h"

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>
#include <QtCore/QFileInfo>

#include "Command/Backend/Editor/AskForSave.h"
#include "MainView/Model/MapModel.h"
#include "Common/FileNameConventions.h"
#include "Common/Common.h"

NewMapFile::NewMapFile(const QModelIndex &index, QObject *parent)
    : NotUndoable(false, parent), fileManager(parent)
{
    this->setObjectName("NewMapFile");
    this->index = index;
}

bool NewMapFile::execute()
{
    PIDGIRL::writeLog("Creating new map file");

    bool ok = false;
    QFileInfo fileInfo = QFileInfo(this->worldModel->filePath(this->index));
    this->dir = fileInfo.dir();

    if(fileInfo.isDir())
    {
        dir.cd(fileInfo.fileName());
    }

    this->file = QInputDialog::getText(0,
                                       tr("New Map..."),
                                       tr("Enter the name of the new map."),
                                       QLineEdit::Normal,
                                       tr("New Map"),
                                       &ok);

    if(!ok)
    {
        PIDGIRL::writeLogDone("[EXIT]");
        return true;
    }

    if(this->file.isEmpty())
    {
        PIDGIRL::writeLogFail("No file was specified. The string, where the path should've been, was empty.");
        return false;
    }

    if(this->file.endsWith(PIDGIRL::MAP_SUFFIX))
    {
        this->file.remove(this->file.size() - PIDGIRL::MAP_SUFFIX.size(), PIDGIRL::MAP_SUFFIX.size());
    }

    int i = 1;
    QString newFile = this->file;
    while(dir.exists(newFile.append(PIDGIRL::MAP_SUFFIX)))
    {
        newFile = this->file;
        newFile = newFile.append(QString::number(i));
        ++i;
    }

    MapModel tempMap;
    QString mapPath = QFileInfo(this->dir, newFile).absoluteFilePath();

    tempMap.setLocalMapPath(this->worldModel->absoluteMapPathToLocalMapPath(mapPath));

    if(!this->fileManager.serialize(&tempMap, mapPath))
    {
        QMessageBox::critical(0, tr("Failed to create a map file..."), tr("Creating a map file has failed."));
        PIDGIRL::writeLogFail("The creating process of the map failed.");
        return false;
    }

    PIDGIRL::writeLogDone();

    return true;
}
