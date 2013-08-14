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

#include "SaveEMailGame.h"

#include <QDir>
#include <QFileInfo>
#include <QMessageBox>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"
#include "Game/Model/SaveGameFile.h"

SaveEMailGame::SaveEMailGame(MailGameInfo *mailGameInfo, const QString &playerName, unsigned int turnCount, QObject *parent)
    : GameCommand(parent), mailGameInfo(mailGameInfo), playerName(playerName), turnCount(turnCount)
{
    this->setObjectName("SaveEMailGame");
}

bool SaveEMailGame::execute()
{
    PIDGIRL::writeLog("Saving E-Mail Game");

    if(!this->mailGameInfo->hasEMailGameDirSet())
    {
        if(!this->mailGameInfo->initializeMailGameInfo())
        {
            PIDGIRL::writeLogFail("Mail Game Info could not be initialized.");
            return false;
        }
    }

    QDir saveDir = this->mailGameInfo->getSaveDir();

    QString saveFileName;

    if(this->playerName.isEmpty())
    {
        saveFileName = QString("%1").arg(this->turnCount,6,10,QChar('0'));
        saveFileName.append("-").append("A_New_Player_Is_Next").append(PIDGIRL::EMAIL_SUFFIX);
        this->playerName = QString("A New Player");
    }
    else
    {
        saveFileName = QString("%1").arg(this->turnCount,6,10,QChar('0'));
        saveFileName.append("-").append(this->playerName).append("_Is_Next").append(PIDGIRL::EMAIL_SUFFIX);
    }

    SaveGameFile saveGameFile(this->processor, this->worldModel, this->gameModel);

    saveGameFile.setFileInfo(QFileInfo(saveDir, saveFileName));

    if(!this->fileManager.serialize(&saveGameFile, saveGameFile.getFileInfo().absoluteFilePath()))
    {
        QMessageBox::critical(0, tr("Failed to save the E-Mail game..."), tr("Saving the E-Mail game has failed."));
        PIDGIRL::writeLogFail("The saving process of the E-Mail Game failed.");
        return false;
    }

    PIDGIRL::writeLogDone();

    QMessageBox::information(0, tr("E-Mail Game saved..."), tr("The Game has been successfully saved."), QMessageBox::Ok);

    QMessageBox::information(0,
                             tr("E-Mail Game saved..."),
                             tr("The E-Mail Game for the next turn has been saved to\n\n%1\n\nNext Turn: %2").arg(saveGameFile.getFileInfo().absoluteFilePath(), this->playerName),
                             QMessageBox::Ok);

    return true;
}
