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

#include "PlayerModel.h"

#include <QDataStream>

PlayerModel::PlayerModel(unsigned int ID, const QString &localMapPath, bool activePlayer, QObject *parent)
    : QObject(parent)
{
    this->init(ID, localMapPath, activePlayer);
}

PlayerModel::PlayerModel(QObject *parent)
    : QObject(parent)
{
    this->init();
}

void PlayerModel::init(unsigned int ID, const QString &localMapPath, bool activePlayer, bool characterSpawned)
{
    this->ID = ID;
    this->setPlayerMapPath(localMapPath);
    this->setActivePlayer(activePlayer);
    this->setCharacterSpwawned(characterSpawned);
    return;
}

QString PlayerModel::getLocalMapPath() const
{
    return this->playerMapPath;
}

bool PlayerModel::isActivePlayer() const
{
    return this->activePlayer;
}

bool PlayerModel::hasCharacterSpawned() const
{
    return this->characterSpawned;
}

unsigned int PlayerModel::getID() const
{
    return this->ID;
}

void PlayerModel::setPlayerMapPath(const QString &currentMapPath)
{
    this->playerMapPath = currentMapPath;
    return;
}

void PlayerModel::setActivePlayer(bool activePlayer)
{
    this->activePlayer = activePlayer;
    return;
}

void PlayerModel::setCharacterSpwawned(bool characterSpawned)
{
    this->characterSpawned = characterSpawned;
    return;
}

void PlayerModel::serialize(QIODevice *device) const
{
    QDataStream dataStream(device);

    this->serialize(&dataStream);

    return;
}

void PlayerModel::serialize(QDataStream *dataStream) const
{
    (*dataStream) << this->ID;
    (*dataStream) << this->playerMapPath;
    (*dataStream) << this->activePlayer;
    (*dataStream) << this->characterSpawned;

    return;
}

void PlayerModel::deserialize(QIODevice *device)
{
    QDataStream dataStream(device);

    this->deserialize(&dataStream);

    return;
}

void PlayerModel::deserialize(QDataStream *dataStream)
{
    unsigned int ID;
    QString playerMapPath;
    bool activePlayer;
    bool characterSpawned;

    (*dataStream) >> ID;
    (*dataStream) >> playerMapPath;
    (*dataStream) >> activePlayer;
    (*dataStream) >> characterSpawned;

    this->init(ID, playerMapPath, activePlayer, characterSpawned);
}
