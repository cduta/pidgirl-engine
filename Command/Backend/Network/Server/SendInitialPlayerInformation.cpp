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

#include "SendInitialPlayerInformation.h"

#include <QVector>

#include "Game/Model/PlayerModel.h"

SendInitialPlayerInformation::SendInitialPlayerInformation(unsigned int playerID, QObject *parent)
    : ServerCommand(playerID, parent)
{
    this->setObjectName("SendNewPlayerInformation");
}

bool SendInitialPlayerInformation::execute()
{
    this->gameModel->addNewPlayer(this->playerID, new PlayerModel(this->playerID));

    this->networkModel->sendData(RECEIVE_INITIAL_PLAYER_INFORMATION, this->playerID);
    this->networkModel->sendData(*this->worldModel, this->playerID);
    this->networkModel->sendData(this->gameModel->getPlayerChoosesStartLocation(), this->playerID);
    this->networkModel->sendData(this->playerID, this->playerID);

    return true;
}
