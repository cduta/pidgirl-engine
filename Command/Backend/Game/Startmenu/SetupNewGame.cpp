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

#include "SetupNewGame.h"

#include <QPushButton>
#include <QRegExp>

#include "Command/Backend/Game/Startmenu/PreloadWorld.h"
#include "Command/Backend/Game/Ingame/PreloadAllMaps.h"
#include "Common/Common.h"
#include "Network/ServerModel.h"
#include "Game/Model/ServerGameModel.h"
#include "Game/Model/HotseatGameModel.h"
#include "Game/Model/EMailGameModel.h"
#include "Game/Model/PlayerModel.h"

#include <iostream>

SetupNewGame::SetupNewGame(GameModel **gameModelPointer, QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("SetupNewGame");
    this->gameSetupLayout = new OptionsLayout();

    this->gameModelPointer = gameModelPointer;

    this->gameSetupDialog.setLayout(this->gameSetupLayout);
    this->gameSetupDialog.setWindowTitle(tr("New Game..."));
    connect(&(this->gameSetupDialog), SIGNAL(rejected()),this, SLOT(quit()));

    this->generalSetupWidget = new GeneralSetupWidget(&this->gameSetupDialog);
    this->generalSetupWidget->playerChoosesStartLocation->setChecked(false);
    this->gameSetupLayout->addPropertyWidget(tr("General Options"), this->generalSetupWidget);

    this->soloHotseatSetupWidget = new SoloHotseatSetupWidget(&this->gameSetupDialog);
    connect(this->soloHotseatSetupWidget->gameStartButton, SIGNAL(clicked()), this, SLOT(initSoloHotseat()));
    this->gameSetupLayout->addPropertyWidget(tr("Solo / Hotseat"), this->soloHotseatSetupWidget);

    this->networkSetupWidget = new NetworkSetupWidget(&this->gameSetupDialog);
    connect(this->networkSetupWidget->gameStartButton, SIGNAL(clicked()), this, SLOT(initNetwork()));
    this->gameSetupLayout->addPropertyWidget(tr("Network"), this->networkSetupWidget);

    this->emailSetupWidget = new EMailSetupWidget(&this->gameSetupDialog);
    connect(this->emailSetupWidget->gameStartButton, SIGNAL(clicked()), this, SLOT(initEMailGame()));
    this->gameSetupLayout->addPropertyWidget(tr("Play By E-Mail"), this->emailSetupWidget);
}

bool SetupNewGame::execute()
{
    if(!this->initGameSetupDialog())
    {
        return false;
    }

    if(this->gameSetupDialog.exec() == QDialog::Rejected)
    {
        return false;
    }

    if(!this->processor->execute(new PreloadAllMaps()))
    {
        return false;
    }

    return true;
}

bool SetupNewGame::initGameSetupDialog()
{
    // Preload the world from the file.
    if(!this->processor->execute(new PreloadWorld()))
    {
        return false;
    }

    return true;
}

void SetupNewGame::applyGeneralProperties()
{
    this->gameModel->setPlayerChoosesStartLocation(this->generalSetupWidget->playerChoosesStartLocation->isChecked());
    return;
}


void SetupNewGame::initSoloHotseat()
{
    this->gameModel = new HotseatGameModel(this->processor, this);
    (*this->gameModelPointer) = this->gameModel;
    this->processor->setGameModel(this->gameModel);
    this->gameModel->addNewPlayer(0, new PlayerModel());
    this->applyGeneralProperties();

    this->gameSetupDialog.done(QDialog::Accepted);
    return;
}

void SetupNewGame::initNetwork()
{
    this->gameModel = new ServerGameModel(this->processor, this);
    (*this->gameModelPointer) = this->gameModel;
    this->processor->setGameModel(this->gameModel);
    this->gameModel->addNewPlayer(0, new PlayerModel());
    this->applyGeneralProperties();

    ServerModel *newServerModel = new ServerModel(this->networkSetupWidget->portEdit->text().toInt(), this->worldModel, this->processor);
    this->processor->setNetworkModel(newServerModel);
    newServerModel->listen();

    this->gameSetupDialog.done(QDialog::Accepted);
    return;
}

void SetupNewGame::initEMailGame()
{
    this->gameModel = new EMailGameModel(this->processor, this);
    (*this->gameModelPointer) = this->gameModel;
    this->processor->setGameModel(this->gameModel);
    this->gameModel->addNewPlayer(0, new PlayerModel());

    unsigned int newPlayerID;
    for(int i = 1; i < this->emailSetupWidget->playerCountSpinBox->value(); ++i)
    {
        newPlayerID = this->worldModel->refObjectID()->getNewSpawnIDFor(ObjectID::PLAYER);
        this->gameModel->addNewPlayer(newPlayerID, new PlayerModel(newPlayerID));
    }
    this->applyGeneralProperties();

    this->gameSetupDialog.done(QDialog::Accepted);
    return;
}
