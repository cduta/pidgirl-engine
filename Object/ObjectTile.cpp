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

#include "Object/ObjectTile.h"

#include "Object/ObjectID.h"

ObjectTile::ObjectTile(const QString &name, const QString &description, TileType tileType, const QString &imagePath, bool isVisible, QObject *parent)
    : ObjectBase(name, description, imagePath, isVisible, parent)
{
    this->initObjectTile(tileType);
}

ObjectTile::ObjectTile(const ObjectTile &objectTile)
    : ObjectBase(objectTile)
{
    this->initObjectTile(objectTile.getTileType());
}

void ObjectTile::initObjectTile(TileType tileType)
{
    this->tileType = tileType;
    return;
}

ObjectBase *ObjectTile::copyBase() const
{
    return this->copy();
}

void ObjectTile::updateTile(const ObjectTile &tile)
{
    this->updateBase(tile);
    this->setTileType(tile.getTileType());

    return;
}

ObjectBase::ObjectType ObjectTile::getType() const
{
    return ObjectBase::TILE;
}

int ObjectTile::getObjectIDNumber() const
{
    return this->getObjectID();
}

ObjectTile::TileType ObjectTile::getTileType() const
{
    return this->tileType;
}

void ObjectTile::setTileType(TileType tileType)
{
    this->tileType = tileType;
    return;
}

void ObjectTile::serialize(QDataStream &dataStream) const
{
    ObjectBase::serialize(dataStream);
    dataStream << this->getTileType();
    return;
}

void ObjectTile::deserialize(QDataStream &dataStream)
{
    ObjectBase::deserialize(dataStream);

    int tileType;

    dataStream >> tileType;

    this->setTileType(ObjectTile::TileType(tileType));

    return;
}
