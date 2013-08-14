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

#include "SpawnGameObject.h"

#include <iostream>

SpawnGameObject::SpawnGameObject(ObjectBase *spawnableObject, StackModel *stackModel, QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("SpawnGameObject");
    this->spawnableObject = spawnableObject;
    this->stackModel = stackModel;
}

bool SpawnGameObject::execute()
{
    if(!this->spawnableObject)
    {
        std::cout << "Error placing an object on a mainview stack: object was 0." << std::endl;
        return false;
    }

    switch(this->spawnableObject->getType())
    {
        case ObjectBase::ITEM:
        {
            ObjectItem *item = qobject_cast<ObjectItem *>(this->spawnableObject);
            Q_UNUSED(item);

            // Command SpawnItem

            break;
        }
        case ObjectBase::CHARACTER:
        {
            ObjectCharacter *character = qobject_cast<ObjectCharacter *>(this->spawnableObject);
            Q_UNUSED(character);

            // Command SpawnCharacter

            break;
        }
        case ObjectBase::TILE:
        {
            ObjectTile *tile = qobject_cast<ObjectTile *>(this->spawnableObject);
            Q_UNUSED(tile);

            switch(tile->getTileType())
            {
                case ObjectTile::WALL:
                {
                    // Command SpawnWall
                }
                case ObjectTile::FLOOR:
                {
                    // Command SpawnFloor
                }
                default: break;
            }
            break;
        }
        case ObjectBase::SPECIAL:
        {
            ObjectSpecial *special = qobject_cast<ObjectSpecial *>(this->spawnableObject);
            Q_UNUSED(special);

            // Command SpawnSpecial

            break;
        }
        default: break;
    }

    std::cout << "Error placing an object on a mainview stack: Unexpected type of object to be placed." << std::endl;
    return false;

    return true;
}
