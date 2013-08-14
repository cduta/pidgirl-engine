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

#include "ObjectID.h"

#include "Common/Common.h"

#include <QDataStream>

ObjectID::ObjectID()
{
}

unsigned int ObjectID::getNewSpawnIDFor(ObjectID::CharacterID id)
{
    return this->getNewSpawnIDFromMap(this->characterSpawnIDMap, id);
}

unsigned int ObjectID::getNewSpawnIDFor(ObjectID::ItemID id)
{
    return this->getNewSpawnIDFromMap(this->itemSpawnIDMap, id);
}

unsigned int ObjectID::getNewSpawnIDFor(ObjectID::SpecialID id)
{
    return this->getNewSpawnIDFromMap(this->specialSpawnIDMap, id);
}

unsigned int ObjectID::getNewSpawnIDFor(ObjectID::TileID id)
{
    return this->getNewSpawnIDFromMap(this->tileSpawnIDMap, id);
}

unsigned int ObjectID::getNewSpawnIDFromMap(QMap<int, unsigned int> &map, int id)
{
    if(map.contains(id))
    {
        map[id] = PIDGIRL::nextID(map[id], 1);
    }
    else
    {
        map[id] = 1;
    }

    return map[id];
}

void ObjectID::serialize(const QMap<int, unsigned int> &map, QDataStream &stream) const
{
    stream << map.size();

    for(int i = 0; i < map.size(); ++i)
    {
        stream << map.keys().at(i);
        stream << map.values().at(i);
    }
    return;
}

void ObjectID::deserialize(QMap<int, unsigned int> &map, QDataStream &stream)
{
    int key;
    unsigned int value;
    int size;

    stream >> size;

    for(int i = 0; i < size; ++i)
    {
        stream >> key;
        stream >> value;
        map.insert(key, value);
    }

    return;
}

void ObjectID::serialize(QDataStream &stream) const
{
    this->serialize(this->characterSpawnIDMap, stream);
    this->serialize(this->itemSpawnIDMap, stream);
    this->serialize(this->specialSpawnIDMap, stream);
    this->serialize(this->tileSpawnIDMap, stream);

    return;
}

void ObjectID::deserialize(QDataStream &stream)
{
    this->deserialize(this->characterSpawnIDMap, stream);
    this->deserialize(this->itemSpawnIDMap, stream);
    this->deserialize(this->specialSpawnIDMap, stream);
    this->deserialize(this->tileSpawnIDMap, stream);

    return;
}
