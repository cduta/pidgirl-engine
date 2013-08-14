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

#include "ServerGameModel.h"

#include <QMessageBox>

#include "Command/Backend/Game/Ingame/FirstTurn.h"
#include "Command/Backend/Game/Ingame/YourTurnInformation.h"
#include "Command/Backend/Network/Server/SendToClientNextTurn.h"
#include "Command/Backend/Network/Server/Broadcast/BroadcastSpawnCharacter.h"
#include "Command/Backend/Network/Server/Broadcast/BroadcastUpdateCharacter.h"
#include "Command/Backend/Common/Quit.h"

ServerGameModel::ServerGameModel(Processor *processor, QObject *parent)
    : LocalGameModel(processor, parent), currentPlayerID(0)
{
}

void ServerGameModel::nextCurrentPlayer()
{
    unsigned int oldPlayerID = this->currentPlayerID;
    QList<unsigned int> keys = this->playerModels.keys();
    unsigned int playerID;
    int currentIndex = keys.indexOf(this->currentPlayerID);

    do
    {
        currentIndex++;

        if(currentIndex == keys.size())
        {
            currentIndex = 0;
        }

        playerID = keys[currentIndex];
    }
    while(!this->playerModels[playerID]->isActivePlayer() && playerID != oldPlayerID);

    if(playerID == oldPlayerID && !this->playerModels[playerID]->isActivePlayer())
    {
        qDebug("No more active players around. Going to quit the game...");

        QMessageBox::information(0,
                                 tr("No more players available..."),
                                 tr("No more players are available, therefore I'll quit the game."),
                                 QMessageBox::Ok);

        this->processor->execute(new Quit());
    }

    this->setCurrentPlayerID(playerID);

    return;
}

bool ServerGameModel::nextTurn()
{
    this->nextCurrentPlayer();
    return this->beginTurn();
}

bool ServerGameModel::beginTurn()
{
    if(this->currentPlayerID != this->playerID)
    {
        if(!this->processor->execute(new SendToClientNextTurn(this->currentPlayerID)))
        {
            return false;
        }
    }
    else
    {
        this->processor->execute(new YourTurnInformation());

        if(!this->refPlayerModel(this->currentPlayerID)->hasCharacterSpawned())
        {
            if(!this->processor->execute(new FirstTurn()))
            {
                return false;
            }
        }
        else
        {
            if(!this->loadMap(this->playerModels[this->playerID]->getLocalMapPath()))
            {
                qDebug() << "The current map could not be loaded for player with ID" << this->playerID << "\nClosing the game.";
                this->processor->execute(new Quit());
                return false;
            }
        }
    }

    return true;
}

bool ServerGameModel::firstTurn()
{
    return this->beginTurn();
}

bool ServerGameModel::endTurn()
{
    return this->nextTurn();
}

bool ServerGameModel::spawnCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &newCharacter)
{
    if(!this->GameModel::spawnCharacter(playerID, map, newCharacter))
    {
        return false;
    }

    return this->processor->execute(new BroadcastSpawnCharacter(playerID, this->playerModels.values(), map->getLocalMapPath(), newCharacter));
}

bool ServerGameModel::updateCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &oldCharacter, const ObjectCharacter &newCharacter)
{
    if(!this->GameModel::updateCharacter(playerID, map, oldCharacter, newCharacter))
    {
        return false;
    }

    return this->processor->execute(new BroadcastUpdateCharacter(playerID, this->playerModels.values(), map->getLocalMapPath(), oldCharacter, newCharacter));
}

void ServerGameModel::deavtivatePlayer(unsigned int playerID)
{
    this->playerModels[playerID]->setActivePlayer(false);
    if(this->currentPlayerID == playerID)
    {
        this->nextTurn();
    }
}

void ServerGameModel::convertFromDifferentGameModel(GameModel *gameModel)
{
    if(!gameModel)
    {
        qDebug() << "Given Game Model was 0.";
        return;
    }

    if(gameModel->getGameType() != PIDGIRL::HOTSEAT)
    {
        qDebug() << "Not a compatible game model used to update. Type was" << gameModel->getGameType();
        return;
    }

    this->LocalGameModel::convertFromDifferentGameModel(gameModel);

    this->setCurrentPlayerID(0);
    this->setPlayerID(0);

    QMap<unsigned int, PlayerModel *> playerModelMap = this->playerModels;
    playerModelMap.remove(0);
    QList<unsigned int> keyList = playerModelMap.keys();

    for(int i = 0; i < keyList.size(); ++i)
    {
        this->refPlayerModel(keyList[i])->setActivePlayer(false);
    }

    return;
}

bool ServerGameModel::isYourTurn() const
{
    return this->playerID == this->currentPlayerID;
}

PIDGIRL::GameType ServerGameModel::getGameType() const
{
    return PIDGIRL::NETWORK;
}

int ServerGameModel::getCurrentPlayerID() const
{
    return this->currentPlayerID;
}

MapModel *ServerGameModel::refCurrentMap() const
{
    return this->preloadedMaps.value(this->playerModels.value(this->currentPlayerID)->getLocalMapPath(), 0);
}

void ServerGameModel::setCurrentPlayerID(unsigned int currentPlayerID)
{
    this->currentPlayerID = currentPlayerID;
    qDebug(QString("Current Player: ").append(QString::number(this->currentPlayerID)).toStdString().c_str());
    return;
}

void ServerGameModel::serialize(QIODevice *device) const
{
    QDataStream dataStream(device);

    LocalGameModel::serialize(dataStream);

    dataStream << this->currentPlayerID;
    return;
}

void ServerGameModel::deserialize(QIODevice *device)
{
    QDataStream dataStream(device);

    LocalGameModel::deserialize(dataStream);

    int currentPlayerID;
    dataStream >> currentPlayerID;

    this->setCurrentPlayerID(currentPlayerID);
    return;
}
