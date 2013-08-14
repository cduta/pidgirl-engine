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

#include "SaveMap.h"

#include <QFileDialog>
#include <QMessageBox>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"
#include "Command/Backend/Editor/World/SaveWorld.h"

SaveMap::SaveMap(QObject *parent)
    : NotUndoable(false, parent), fileManager(parent)
{
    this->setObjectName("SaveMap");
}

bool SaveMap::execute()
{
    PIDGIRL::writeLog("Saving Map");

    QString fileNamePath = this->mapModel->getFileInfo().absoluteFilePath();

    if(fileNamePath.isEmpty())
    {
        fileNamePath = QFileDialog::getSaveFileName
            (
                0,
                tr("Save Map As..."),
                this->worldModel->refWorldFileInfo()->absolutePath(),
                tr("PIDGIRL Map Files (*").append(PIDGIRL::MAP_SUFFIX).append(")")
            );
    }

    // Still empty?
    if(fileNamePath.isEmpty())
    {
        PIDGIRL::writeLogFail("No file was specified. The string, where the path should've been, was empty.");
        return false;
    }

    if(!fileNamePath.endsWith(PIDGIRL::MAP_SUFFIX))
    {
        fileNamePath.append(PIDGIRL::MAP_SUFFIX);
    }

    this->mapModel->setLocalMapPath(this->worldModel->absoluteMapPathToLocalMapPath(fileNamePath));

    if(!this->fileManager.serialize(this->mapModel, fileNamePath))
    {
        QMessageBox::critical(0, tr("Failed to save the map..."), tr("Saving the map has failed."));
        PIDGIRL::writeLogFail("The saving process of the map failed.");
        return false;
    }

    this->undoRedo->setSavedStates();

    PIDGIRL::writeLogDone();

    this->processor->execute(new SaveWorld());

    return true;
}
