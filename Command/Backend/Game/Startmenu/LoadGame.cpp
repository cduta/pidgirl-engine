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

#include "LoadGame.h"

#include <QDir>
#include <QFileDialog>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"
#include "Game/Model/HotseatGameModel.h"
#include "Game/Model/ServerGameModel.h"
#include "Network/ServerModel.h"

LoadGame::LoadGame(GameModel **gameModelPointer, QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("LoadGame");

    this->gameModelPointer = gameModelPointer;

    this->loadSetupLayout = new OptionsLayout(&this->loadSetupDialog);
    this->loadSetupDialog.setLayout(this->loadSetupLayout);
    this->loadSetupDialog.setWindowTitle(tr("New Game..."));
    this->loadSetupLayout->refApplyButton()->setVisible(false);
    this->loadSetupLayout->refOkButton()->setVisible(false);
    connect(&(this->loadSetupDialog), SIGNAL(rejected()),this, SLOT(quit()));

    this->soloHotseatSetupWidget = new SoloHotseatSetupWidget(&this->loadSetupDialog);
    connect(this->soloHotseatSetupWidget->gameStartButton, SIGNAL(clicked()), this, SLOT(loadSoloHotseatGame()));
    this->loadSetupLayout->addPropertyWidget(tr("Solo / Hotseat"), this->soloHotseatSetupWidget);

    this->networkSetupWidget = new NetworkSetupWidget(&this->loadSetupDialog);
    connect(this->networkSetupWidget->gameStartButton, SIGNAL(clicked()), this, SLOT(loadNetworkGame()));
    this->loadSetupLayout->addPropertyWidget(tr("Network"), this->networkSetupWidget);
}

bool LoadGame::execute()
{
    if(!this->init())
    {
        return false;
    }

    if(this->loadSetupDialog.exec() != QDialog::Accepted)
    {
        return false;
    }

    return true;
}

bool LoadGame::init()
{
    QDir saveDir(QDir::current());
    if(!saveDir.cd(PIDGIRL::SAVE_FOLDER_NAME))
    {
        saveDir.mkdir(PIDGIRL::SAVE_FOLDER_NAME);
        saveDir.cd(PIDGIRL::SAVE_FOLDER_NAME);
    }

    this->saveFilePath = QFileDialog::getOpenFileName
            (
                0,
                tr("Choose a Save File to load the game from..."),
                saveDir.absolutePath(),
                tr("PIDGIRL Save Files (*").append(PIDGIRL::SAVE_SUFFIX).append(")")
            );

    if(this->saveFilePath.isEmpty())
    {
        return false;
    }

    return true;
}

void LoadGame::loadSoloHotseatGame()
{
    this->gameModel = new HotseatGameModel(this->processor, this);
    (*this->gameModelPointer) = this->gameModel;
    this->processor->setGameModel(this->gameModel);

    SaveGameFile saveGameFile(this->processor, this->worldModel, this->gameModel, this);
    if(fileManager.deserialize(&saveGameFile, this->saveFilePath))
    {
        this->loadSetupDialog.done(QDialog::Accepted);
    }
    else
    {
        this->loadSetupDialog.done(QDialog::Rejected);
    }

    return;
}

void LoadGame::loadNetworkGame()
{
    this->gameModel = new ServerGameModel(this->processor, this);
    (*this->gameModelPointer) = this->gameModel;
    this->processor->setGameModel(this->gameModel);

    ServerModel *newServerModel = new ServerModel(this->networkSetupWidget->portEdit->text().toInt(), this->worldModel, this->processor);
    this->processor->setNetworkModel(newServerModel);
    newServerModel->listen();

    SaveGameFile saveGameFile(this->processor, this->worldModel, this->gameModel, this);
    if(fileManager.deserialize(&saveGameFile, this->saveFilePath))
    {
        this->loadSetupDialog.done(QDialog::Accepted);
    }
    else
    {
        this->loadSetupDialog.done(QDialog::Rejected);
    }
    return;
}
