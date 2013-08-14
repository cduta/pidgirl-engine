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

#include "LoadWorld.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"
#include "Common/YesNoCancelDialog.h"
#include "Command/Backend/Editor/World/SaveWorld.h"
#include "Command/Backend/Editor/AskForSave.h"

LoadWorld::LoadWorld(bool resetToStandardMap, bool mayAsk, QObject *parent)
    : NotUndoable(true, parent), fileManager(parent)
{
    this->setObjectName("LoadWorld");
    this->mayAsk = mayAsk;
    this->resetToStandardMap = resetToStandardMap;
}

bool LoadWorld::execute()
{
    if(this->mayAsk && !this->processor->execute(new AskForSave()))
    {
        return false;
    }

    PIDGIRL::writeLog("Loading World");

    QDir worldDir(QDir::current());
    worldDir.mkdir(PIDGIRL::WORLD_FOLDER_NAME);
    worldDir.cd(PIDGIRL::WORLD_FOLDER_NAME);

    QString fileName = QFileDialog::getOpenFileName
            (
                0,
                tr("Load World..."),
                worldDir.absolutePath(),
                tr("PIDGIRL World Files (*").append(PIDGIRL::WORLD_SUFFIX).append(")")
            );

    if(fileName.isEmpty())
    {
        PIDGIRL::writeLogFail("No file was specified. The string where the path should've been was empty.");
        return false;
    }

    this->worldModel->setWorldFileInfo(QFileInfo(fileName));
    this->fileManager.setFilePath(this->worldModel->refWorldFileInfo()->absoluteFilePath());

    if(!this->loadWorld())
    {
        QMessageBox::critical(0, tr("Failed to load a world..."), tr("Loading a world has failed."));
        PIDGIRL::writeLogFail("The loading process of the world failed.");
        return false;
    }

    if(this->resetToStandardMap)
    {
        this->mapModel->setNewStandardMap();
    }

    this->undoRedo->setOnlySavedWorldChanges(true);

    PIDGIRL::writeLogDone();
    return true;
}

bool LoadWorld::loadWorld()
{
    if(!this->fileManager.fileExists())
    {
        return false;
    }

    if(!this->fileManager.fileOpen(QIODevice::ReadOnly))
    {
        return false;
    }

    this->worldModel->deserialize(this->fileManager.refFile());

    this->fileManager.fileClose();

    return true;
}
