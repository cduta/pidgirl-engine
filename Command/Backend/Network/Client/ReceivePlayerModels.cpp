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

#include "ReceivePlayerModels.h"

ReceivePlayerModels::ReceivePlayerModels(QObject *parent)
    : ClientCommand(parent)
{
    this->setObjectName("ReceivePlayerModels");
}

bool ReceivePlayerModels::execute()
{
    int playerModelAmount;

    this->networkModel->receiveData(playerModelAmount);

    qDebug() << "PlayerModelAmount:" << playerModelAmount;

    PlayerModel *player;
    QMap<unsigned int, PlayerModel *> playerModels;

    for(int i = 0; i < playerModelAmount; ++i)
    {
        player = new PlayerModel(this->gameModel);
        this->networkModel->receiveData(*player);

        playerModels.insert(player->getID(), player);
    }

    this->gameModel->setPlayerModels(playerModels);

    return true;
}
