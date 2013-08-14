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

#include "ClientGameModel.h"

#include "Common/Common.h"

#include "Command/Backend/Game/Ingame/FirstTurn.h"
#include "Command/Backend/Game/Ingame/YourTurnInformation.h"
#include "Command/Backend/Network/Client/RequestMapFromServer.h"
#include "Command/Backend/Network/Client/SendSpawnCharacterToServer.h"
#include "Command/Backend/Network/Client/SendUpdateCharacterToServer.h"
#include "Command/Backend/Network/Client/SendToServerEndTurn.h"
#include "Command/Backend/Network/Client/RequestPlayerModelsFromServer.h"
#include "Command/Backend/Network/Client/RequestPlayerFromServer.h"
#include "Command/Backend/Network/Client/ChangePlayerIDOnServer.h"

ClientGameModel::ClientGameModel(Processor *processor, QObject *parent)
    : GameModel(parent)
{
    this->currentMap = 0;
    this->processor = processor;
    this->yourTurn = false;
}

bool ClientGameModel::addNewPlayer(unsigned int playerID, PlayerModel *playerModel)
{
    Q_UNUSED(playerID);
    Q_UNUSED(playerModel);
    qDebug("A Client cannot add a new player.");
    return false;
}

bool ClientGameModel::nextTurn()
{
    return this->beginTurn();
}

bool ClientGameModel::beginTurn()
{
    this->setYourTurn(true);
    this->processor->execute(new YourTurnInformation());
    return true;
}

bool ClientGameModel::firstTurn()
{
    return this->processor->execute(new FirstTurn());
}

bool ClientGameModel::endTurn()
{
    this->setYourTurn(false);
    return this->processor->execute(new SendToServerEndTurn());
}

void ClientGameModel::deavtivatePlayer(unsigned int playerID)
{
    Q_UNUSED(playerID);
    qDebug("Client cannot deactivate player.");
    return;
}

PIDGIRL::GameType ClientGameModel::getGameType() const
{
    return PIDGIRL::NETWORK;
}

void ClientGameModel::addtoPreloadedMaps(const QString &localMapPath, MapModel *map)
{
    Q_UNUSED(localMapPath);
    Q_UNUSED(map);
    qDebug("Client can not preload maps.");
    return;
}

void ClientGameModel::setCurrentMap(MapModel *map)
{
    this->currentMap = map;
    return;
}

bool ClientGameModel::loadMap(const QString &localMapPath)
{
    return this->processor->execute(new RequestMapFromServer(localMapPath));
}

bool ClientGameModel::loadMap(MapModel *map)
{
    this->setCurrentMap(map);
    return this->GameModel::loadMap(map);
}

bool ClientGameModel::spawnCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &newCharacter)
{
    if(!this->GameModel::spawnCharacter(playerID, map, newCharacter))
    {
        return false;
    }

    if(playerID != PIDGIRL::SERVER_PLAYER_ID)
    {
        return this->processor->execute(new SendSpawnCharacterToServer(newCharacter));
    }

    return true;
}

bool ClientGameModel::updateCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &oldCharacter, const ObjectCharacter &newCharacter)
{
    if(!GameModel::updateCharacter(playerID, map, oldCharacter, newCharacter))
    {
        return false;
    }

    if(playerID != PIDGIRL::SERVER_PLAYER_ID)
    {
        return this->processor->execute(new SendUpdateCharacterToServer(oldCharacter, newCharacter));
    }

    return true;
}

void ClientGameModel::changePlayerID(unsigned int newID)
{
    this->GameModel::changePlayerID(newID);

    this->processor->execute(new ChangePlayerIDOnServer(newID));
    return;
}

void ClientGameModel::convertFromDifferentGameModel(GameModel *gameModel)
{
    Q_UNUSED(gameModel);
    qDebug("Cannot convert a Game Model with a different Game Model as EMail Game.");
    return;
}

void ClientGameModel::setYourTurn(bool yourTurn)
{
    this->yourTurn = yourTurn;
    return;
}

bool ClientGameModel::isYourTurn() const
{
    return this->yourTurn;
}

QMap<unsigned int, PlayerModel *> ClientGameModel::getPlayerModels() const
{
    if(!this->processor->execute(new RequestPlayerModelsFromServer()))
    {
        return QMap<unsigned int, PlayerModel *>();
    }

    return this->GameModel::getPlayerModels();
}

QMap<QString, MapModel *> ClientGameModel::getPreloadedMaps() const
{
    qDebug("Clients do not hold any preloaded Maps.");
    return QMap<QString, MapModel *>();
}


PlayerModel *ClientGameModel::refPlayerModel(unsigned int playerID) const
{
    Q_UNUSED(playerID);
    // this->processor->execute(new RequestPlayerModel(unsigned int playerID));

    return 0;
}

MapModel *ClientGameModel::refPreloadedMap(const QString &localMapPath) const
{
    Q_UNUSED(localMapPath);
    qDebug("Clients do not hold any preloaded maps to be referenced.");
    return 0;
}

MapModel *ClientGameModel::refCurrentMap() const
{
    return this->currentMap;
}

Player *ClientGameModel::refPlayer(unsigned int playerID) const
{
    if(!this->processor->execute(new RequestPlayerFromServer(playerID)))
    {
        return 0;
    }

    return qobject_cast<Player *>(this->requestedObject);
}

void ClientGameModel::serialize(QIODevice *device) const
{
    Q_UNUSED(device);
    qDebug("No need to serialize a client game model.");
    return;
}

void ClientGameModel::deserialize(QIODevice *device)
{
    Q_UNUSED(device);
    qDebug("No need to deserialize a client game model.");
    return;
}
