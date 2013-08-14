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

#include "Quit.h"

#include <QDir>
#include <QFileInfo>
#include <QCoreApplication>
#include <QMessageBox>

#include "Command/Backend/Editor/AskForSave.h"
#include "Command/Backend/Common/RemoveFolder.h"
#include "Command/Backend/Game/Ingame/SaveGame.h"
#include "Common/FileNameConventions.h"
#include "Common/Common.h"
#include "MainWindow.h"

Quit::Quit(bool askToSaveGame, QObject *parent)
    : CommonCommand(parent), askToSaveGame(askToSaveGame)
{
    this->setObjectName("Quit");
}

bool Quit::execute()
{
    if(this->editorModel->getIsEditor())
    {
        if(this->processor->execute(new AskForSave()))
        {
            PIDGIRL::done = true;
            QCoreApplication::quit();
        }
    }
    else
    {
        if(this->askToSaveGame && this->gameModel)
        {
            QMessageBox messageBox;
            messageBox.setWindowTitle(tr("Quit the Game?"));
            messageBox.setIcon(QMessageBox::Question);

            QPushButton *saveQuit = 0;
            QPushButton *quit = 0;

            if(this->gameModel->getGameType() == PIDGIRL::HOTSEAT ||
               (this->gameModel->getGameType() == PIDGIRL::NETWORK && this->networkModel->isServer()))
            {
                messageBox.setText(tr("Do you want to save the game before quitting?"));
                saveQuit = messageBox.addButton(tr("Save and Quit"), QMessageBox::AcceptRole);
                quit = messageBox.addButton(tr("Quit"), QMessageBox::DestructiveRole);
                messageBox.addButton(tr("Cancel"), QMessageBox::RejectRole);
            }
            else
            {
                messageBox.setText(tr("Do you really want to quit?\nUnsaved progress will be lost."));
                quit = messageBox.addButton(tr("Quit"), QMessageBox::DestructiveRole);
                messageBox.addButton(tr("Cancel"), QMessageBox::RejectRole);
            }

            messageBox.exec();

            if(messageBox.clickedButton() == saveQuit)
            {
                if(!this->processor->execute(new SaveGame()))
                {
                    return false;
                }
            }
            else
            {
                if(messageBox.clickedButton() != quit)
                {
                    return false;
                }
            }
        }

        PIDGIRL::done = true;
        QCoreApplication::quit();
    }

    return true;
}
