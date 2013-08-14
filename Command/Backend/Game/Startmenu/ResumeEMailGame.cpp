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

#include "ResumeEMailGame.h"

#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QCoreApplication>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"
#include "Game/Model/EMailGameModel.h"
#include "Game/Model/SaveGameFile.h"

ResumeEMailGame::ResumeEMailGame(QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("ResumeEMailGame");
}

bool ResumeEMailGame::execute()
{
    QString filePath;

    if(QCoreApplication::arguments().contains("-m"))
    {
        int failPathLocation = QCoreApplication::arguments().indexOf(QRegExp(QString("-m")));

        if(failPathLocation + 1 < QCoreApplication::arguments().size())
        {
            filePath = QCoreApplication::arguments().at(failPathLocation + 1);
        }
        else
        {
            PIDGIRL::showUsage();
            this->quit();
            return false;
        }
    }
    else
    {
        QDir dir(QDir::current());
        if(!dir.cd(PIDGIRL::EMAIL_FOLDER_NAME))
        {
            dir.mkdir(PIDGIRL::EMAIL_FOLDER_NAME);
            dir.cd(PIDGIRL::EMAIL_FOLDER_NAME);
        }

        filePath = QFileDialog::getOpenFileName(0, tr("Open a saved E-Mail Game..."),
                                                dir.absolutePath(),
                                                tr("PIDGIRL E-Mail Save Files (*").append(PIDGIRL::EMAIL_SUFFIX).append(")"));
    }

    if(filePath.isEmpty())
    {
        return false;
    }

    SaveGameFile saveGameFile(this->processor, this->worldModel, this->gameModel, this);
    if(!fileManager.deserialize(&saveGameFile, filePath))
    {
        return false;
    }

    MailGameInfo *mailGameInfo = qobject_cast<EMailGameModel *>(this->gameModel)->refMailGameInfo(this->gameModel->getPlayerID());

    if(!this->gameModel->refPlayerModel(this->gameModel->getPlayerID())->hasCharacterSpawned())
    {
        return true;
    }

    if(!mailGameInfo->authenticatePlayer())
    {
        QMessageBox::information(0, tr("It's not your turn."),
                                 tr("Sorry, but it is not your turn. It's %1's turn.\nIf you want to join, ask anyone playing to add a new player to the game.").arg(this->gameModel->refPlayer(this->gameModel->getPlayerID())->getObjectName()));
        return false;
    }

    return true;
}
