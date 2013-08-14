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

#include "SaveGame.h"

#include <QMessageBox>
#include <QDir>
#include <QFileDialog>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"
#include "Game/Model/SaveGameFile.h"

SaveGame::SaveGame(QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("SaveGame");
}

bool SaveGame::execute()
{
    PIDGIRL::writeLog("Saving game");

    SaveGameFile saveGameFile(this->processor, this->worldModel, this->gameModel);

    QDir saveDir(QDir::current());
    if(!saveDir.cd(PIDGIRL::SAVE_FOLDER_NAME))
    {
        saveDir.mkdir(PIDGIRL::SAVE_FOLDER_NAME);
        saveDir.cd(PIDGIRL::SAVE_FOLDER_NAME);
    }

    QString saveFilePath = QFileDialog::getSaveFileName
            (
                0,
                tr("Choose a File to Save the game in..."),
                saveDir.absolutePath(),
                tr("PIDGIRL Save Files (*").append(PIDGIRL::SAVE_SUFFIX).append(")")
            );

    if(saveFilePath.isEmpty())
    {
        PIDGIRL::writeLogFail("No file was specified. The string where the path should've been was empty.");
        return false;
    }

    if(!saveFilePath.endsWith(PIDGIRL::SAVE_SUFFIX))
    {
        saveFilePath.append(PIDGIRL::SAVE_SUFFIX);
    }

    saveGameFile.setFileInfo(saveFilePath);

    if(!this->fileManager.serialize(&saveGameFile, saveGameFile.getFileInfo().absoluteFilePath()))
    {
        QMessageBox::critical(0, tr("Failed to save the game..."), tr("Saving the game has failed."));
        PIDGIRL::writeLogFail("The saving process of the E-Mail Game failed.");
        return false;
    }

    PIDGIRL::writeLogDone();

    return true;
}
