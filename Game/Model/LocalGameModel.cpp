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

#include "LocalGameModel.h"

LocalGameModel::LocalGameModel(Processor *processor, QObject *parent)
    : GameModel(parent)
{
    this->processor = processor;
}

bool LocalGameModel::addNewPlayer(unsigned int playerID, PlayerModel *playerModel)
{
    if(this->playerModels.contains(playerID))
    {
        qDebug(QString("Game Model already contained the ID: %1").arg(QString::number(playerID)).toStdString().c_str());
        return false;
    }

    playerModel->setParent(this);
    this->playerModels.insert(playerID, playerModel);

    return true;
}

void LocalGameModel::addtoPreloadedMaps(const QString &localMapPath, MapModel *map)
{
    if(!map)
    {
        qDebug("Could not add preloaded map, because it was 0.");
        return;
    }

    map->setParent(this);
    map->setLocalMapPath(localMapPath);
    this->preloadedMaps.insert(localMapPath, map);
    return;
}

bool LocalGameModel::loadMap(const QString &localMapPath)
{
    if(!this->preloadedMaps.contains(localMapPath))
    {
        qDebug("Requested preloaded map not found.");
        return false;
    }

    this->playerModels[this->playerID]->setPlayerMapPath(localMapPath);
    emit this->setNewMapSignal(this->preloadedMaps[localMapPath]);

    return true;
}

void LocalGameModel::deavtivatePlayer(unsigned int playerID)
{
    Q_UNUSED(playerID);
    qDebug("deactivatePlayer not implemented yet.");
    return;
}

void LocalGameModel::convertFromDifferentGameModel(GameModel *gameModel)
{
    this->GameModel::convertFromDifferentGameModel(gameModel);

    QList<MapModel *> preloadedMapList = this->preloadedMaps.values();

    for(int i = 0; i < preloadedMapList.size(); ++i)
    {
        preloadedMapList[i]->deleteLater();
    }

    this->preloadedMaps.clear();

    this->preloadedMaps = gameModel->getPreloadedMaps();

    preloadedMapList = this->preloadedMaps.values();

    for(int i = 0; i < preloadedMapList.size(); ++i)
    {
        preloadedMapList[i]->setParent(this);
    }

    return;
}

bool LocalGameModel::isYourTurn() const
{
    return true;
}

QMap<QString, MapModel *> LocalGameModel::getPreloadedMaps() const
{
    return QMap<QString, MapModel *>(this->preloadedMaps);
}

void LocalGameModel::setCurrentMap(MapModel *map)
{
    Q_UNUSED(map);
    qDebug("Current map always set through playerID, since maps are preloaded.");
    return;
}

PlayerModel *LocalGameModel::refPlayerModel(unsigned int playerID) const
{
    if(!this->playerModels.contains(playerID))
    {
        qDebug("Player Model not found.");
        return 0;
    }

    return this->playerModels[playerID];
}

MapModel *LocalGameModel::refCurrentMap() const
{
    PlayerModel *player = this->playerModels.value(this->playerID);

    if(!player)
    {
        qDebug("Player not found when loading current map.");
        return 0;
    }

    return this->preloadedMaps.value(player->getLocalMapPath(), 0);
}

MapModel *LocalGameModel::refPreloadedMap(const QString &localMapPath) const
{
    if(!this->preloadedMaps.contains(localMapPath))
    {
        qDebug("Preloaded map not found.");
        return 0;
    }

    return this->preloadedMaps.value(localMapPath, 0);
}

Player *LocalGameModel::refPlayer(unsigned int playerID) const
{
    PlayerModel *playerModel = this->refPlayerModel(playerID);

    if(!playerModel)
    {
        return 0;
    }

    MapModel *map = this->refPreloadedMap(playerModel->getLocalMapPath());

    if(!map)
    {
        return 0;
    }

    return qobject_cast<Player *>(map->refPlayerStack(playerID)->refCharacter());
}

void LocalGameModel::serialize(QDataStream &dataStream) const
{
    GameModel::serialize(dataStream);

    //QList<QString > localMapPaths = this->preloadedMaps.keys();
    QList<MapModel *> maps = this->preloadedMaps.values();

    dataStream << preloadedMaps.size();

    for(int i = 0; i < maps.size(); ++i)
    {
        maps[i]->serialize(dataStream);
    }

    return;
}

void LocalGameModel::deserialize(QDataStream &dataStream)
{
    GameModel::deserialize(dataStream);

    int preloadedMapCount;

    dataStream >> preloadedMapCount;

    MapModel *map;

    for(int i = 0; i < preloadedMapCount; ++i)
    {
        map = new MapModel(this);
        map->deserialize(dataStream);
        this->preloadedMaps.insert(map->getLocalMapPath(), map);
    }

    return;
}
