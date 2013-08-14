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

#include "GameModel.h"

#include <QDebug>

#include "Object/ObjectFromID.h"

GameModel::GameModel(QObject *parent)
    : QObject(parent)
{
    this->playerChoosesStartLocation = false;
    this->playerID = 0;
    this->requestedData = 0;
    this->requestedObject = 0;
}

bool GameModel::loadMap(MapModel *map)
{
    if(!map)
    {
        return false;
    }

    emit this->setNewMapSignal(map);

    return true;
}

bool GameModel::spawnCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &newCharacter)
{
    Q_UNUSED(playerID);

    if(!map)
    {
        qDebug("Spawning character failed because:\nNo map was given.");
        return false;
    }

    ObjectCharacter *character = ObjectFromID::objectFrom(newCharacter.getObjectID());
    character->update(newCharacter);
    character->setSpawnID(newCharacter.getSpawnID());

    map->refStackModel(newCharacter.getX(), newCharacter.getY(), newCharacter.getZ())->setCharacter(character);

    this->playerModels[playerID]->setCharacterSpwawned(true);

    return true;
}

bool GameModel::updateCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &oldCharacter, const ObjectCharacter &newCharacter)
{
    Q_UNUSED(playerID);

    if(!map)
    {
        qDebug("Updating character failed because:\nNo map was given.");
        return false;
    }

    ObjectCharacter *character = map->refStackModel(oldCharacter.getX(), oldCharacter.getY(), oldCharacter.getZ())->takeCharacter();

    if(!character)
    {
        qDebug("Updating character failed because:\nThe actual character was not found on the given map.");
        return false;
    }

    character->update(newCharacter);

    map->refStackModel(character->getX(), character->getY(), character->getZ())->setCharacter(character);

    return true;
}

void GameModel::deletePlayerModels()
{
    QList<PlayerModel *> playerModelList = this->playerModels.values();

    for(int i = 0; i < playerModelList.size(); ++i)
    {
        playerModelList[i]->deleteLater();
    }

    playerModelList.clear();

    return;
}

void GameModel::changePlayerID(unsigned int newID)
{
    this->playerID = newID;
    qDebug() << "Your ID changed to" << this->playerID;
    return;
}

void GameModel::convertFromDifferentGameModel(GameModel *gameModel)
{
    QList<PlayerModel *> playerModelList = this->playerModels.values();
    for(int i = 0; i < playerModelList.size(); ++i)
    {
        playerModelList[i]->deleteLater();
    }

    this->playerModels.clear();

    this->playerModels = gameModel->getPlayerModels();
    playerModelList = this->playerModels.values();

    for(int i = 0; i < playerModelList.size(); ++i)
    {
        playerModelList[i]->setParent(this);
    }

    this->setPlayerChoosesStartLocation(gameModel->getPlayerChoosesStartLocation());
    this->setPlayerID(gameModel->getPlayerID());

    return;
}

bool GameModel::getPlayerChoosesStartLocation() const
{
    return this->playerChoosesStartLocation;
}

unsigned int GameModel::getPlayerID() const
{
    return this->playerID;
}

int GameModel::getCurrentPlayerID() const
{
    return this->getPlayerID();
}

QMap<unsigned int, PlayerModel *> GameModel::getPlayerModels() const
{
    return this->playerModels;
}

void GameModel::setPlayerChoosesStartLocation(bool playerChoosesStartLocation)
{
    this->playerChoosesStartLocation = playerChoosesStartLocation;
    return;
}

void GameModel::setPlayerID(unsigned int playerID)
{
    this->playerID = playerID;
    return;
}

void GameModel::setPlayerModels(const QMap<unsigned int, PlayerModel *> playerModels)
{
    this->deletePlayerModels();
    this->playerModels = playerModels;
    return;
}

void GameModel::setRequestedData(QVariant data)
{
    this->requestedData = data;
    return;
}

void GameModel::setRequestedObject(QObject *object)
{
    if(this->requestedObject)
    {
        this->requestedObject->deleteLater();
    }

    object->setParent(this);
    this->requestedObject = object;
    return;
}

void GameModel::serialize(QDataStream &dataStream) const
{
    dataStream << this->playerID;
    dataStream << this->getPlayerChoosesStartLocation();

    QList<PlayerModel *> players = this->playerModels.values();

    dataStream << players.size();

    for(int i = 0; i < players.size(); ++i)
    {
        players[i]->serialize(&dataStream);
    }

    return;
}

void GameModel::deserialize(QDataStream &dataStream)
{
    unsigned int playerID;
    dataStream >> playerID;
    this->setPlayerID(playerID);

    bool playerChoosesStartLocation;

    dataStream >> playerChoosesStartLocation;

    this->setPlayerChoosesStartLocation(playerChoosesStartLocation);

    PlayerModel *player;
    int playerCount;

    dataStream >> playerCount;

    for(int i = 0; i < playerCount; ++i)
    {
        player = new PlayerModel(this);
        player->deserialize(&dataStream);
        this->playerModels.insert(player->getID(), player);
    }
}
