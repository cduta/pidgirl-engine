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

#include "NewWorld.h"

#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtCore/QFileInfo>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"
#include "Common/YesNoCancelDialog.h"
#include "Command/Backend/Editor/World/SaveWorld.h"
#include "Command/Backend/Editor/AskForSave.h"

NewWorld::NewWorld(QObject *parent)
    : NotUndoable(true, parent), fileManager(parent)
{
    this->setObjectName("NewWorld");
}

bool NewWorld::execute()
{
    if(!this->processor->execute(new AskForSave()))
    {
        return false;
    }

    PIDGIRL::writeLog("Creating New World");

    QDir worldDir(QDir::current());
    worldDir.mkdir(PIDGIRL::WORLD_FOLDER_NAME);
    worldDir.cd(PIDGIRL::WORLD_FOLDER_NAME);

    QString fileName = QFileDialog::getSaveFileName
            (
                0,
                tr("Create New World..."),
                worldDir.absolutePath(),
                tr("PIDGIRL World Files (*").append(PIDGIRL::WORLD_SUFFIX).append(")")
            );

    if(fileName.isEmpty())
    {
        PIDGIRL::writeLogFail("No file was specified. The string, where the path should've been, was empty.");
        return false;
    }

    if(!fileName.endsWith(PIDGIRL::WORLD_SUFFIX))
    {
        fileName = fileName.append(PIDGIRL::WORLD_SUFFIX);
    }

    QFileInfo fileInfo = QFileInfo(fileName);
    QString worldDirName = fileName;
    worldDirName.remove(fileName.size() - PIDGIRL::WORLD_SUFFIX.size(),PIDGIRL::WORLD_SUFFIX.size());
    QDir dir = fileInfo.dir();

    if(!dir.mkdir(worldDirName))
    {
        PIDGIRL::writeLogFail("Creating the folder for the world failed.");
        return false;
    }

    if(!dir.cd(worldDirName))
    {
        PIDGIRL::writeLogFail("Changing the directory to the world folder failed.");
        return false;
    }

    this->worldModel->setWorldFileInfo(QFileInfo(dir, fileInfo.fileName()));

    if(!this->fileManager.serialize(this->worldModel, this->worldModel->refWorldFileInfo()->absoluteFilePath()))
    {
        QMessageBox::critical(0, tr("Failed to create a new world..."), tr("Creating a new world has failed."));
        PIDGIRL::writeLogFail(QString("The creating process of the map failed. Filepath was: ").append(this->worldModel->refWorldFileInfo()->absoluteFilePath()));
        return false;
    }

    if(this->mapModel)
    {
        this->mapModel->setNewStandardMap();
    }
    this->undoRedo->setOnlySavedWorldChanges(true);

    PIDGIRL::writeLogDone();
    return true;
}
