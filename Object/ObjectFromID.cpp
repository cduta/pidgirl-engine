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

#include "ObjectFromID.h"

#include "Object/Character/Player.h"

#include "Object/Special/StartPosition.h"

#include "Object/Tile/BrickWall.h"

ObjectCharacter *ObjectFromID::objectFrom(ObjectID::CharacterID id, QObject *parent)
{
    ObjectCharacter *character = 0;

    switch(id)
    {
        case ObjectID::PLAYER: character = new Player(); break;
        default: break;
    }

    if(character)
    {
        character->setParent(parent);
    }

    return character;
}

ObjectItem *ObjectFromID::objectFrom(ObjectID::ItemID id, QObject *parent)
{
    ObjectItem *item = 0;

    switch(id)
    {
        case ObjectID::KNIFE: break;
        default: break;
    }

    if(item)
    {
        parent->setParent(parent);
    }

    return item;
}

ObjectSpecial *ObjectFromID::objectFrom(ObjectID::SpecialID id, QObject *parent)
{
    ObjectSpecial *special = 0;

    switch(id)
    {
        case ObjectID::START_POSITION: special = new StartPosition(); break;
        default: break;
    }

    if(special)
    {
        special->setParent(parent);
    }

    return special;
}

ObjectTile *ObjectFromID::objectFrom(ObjectID::TileID id, QObject *parent)
{
    ObjectTile *tile = 0;

    switch(id)
    {
        case ObjectID::BRICK_WALL: tile = new BrickWall(); break;
        default: break;
    }

    if(tile)
    {
        tile->setParent(parent);
    }

    return tile;
}
