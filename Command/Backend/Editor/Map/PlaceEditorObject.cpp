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

#include "PlaceEditorObject.h"

#include "Command/Backend/Editor/Map/PlaceWall.h"
#include "Command/Backend/Editor/Map/PlaceSpecial.h"
#include "Object/Character/Player.h"

#include <iostream>

PlaceEditorObject::PlaceEditorObject(StackModel *stackModel, ObjectBase *object, QObject *parent)
    : NotUndoable(false, parent)
{
    this->setObjectName("PlaceObject");
    this->setErrorEnabled(false);
    this->placeableObject = object;
    this->stackModel = stackModel;
}

bool PlaceEditorObject::execute()
{
    this->placeableObject = this->editorModel->refMainObject()->copyBase();

    if(!this->placeableObject)
    {
        std::cout << "Error placing an object on a mainview stack: object was 0." << std::endl;
        return false;
    }

    switch(this->placeableObject->getType())
    {
        case ObjectBase::ITEM:
        {
            ObjectItem *item = qobject_cast<ObjectItem *>(this->placeableObject);
            Q_UNUSED(item);

            // Command PrependItem

            break;
        }
        case ObjectBase::CHARACTER:
        {
            ObjectCharacter *character = qobject_cast<ObjectCharacter *>(this->placeableObject);
            Q_UNUSED(character);

            // Command PlaceCharacter

            break;
        }
        case ObjectBase::TILE:
        {
            ObjectTile *tile = qobject_cast<ObjectTile *>(this->placeableObject);
            Q_UNUSED(tile);

            switch(tile->getTileType())
            {
                case ObjectTile::WALL:
                {
                    return this->processor->execute(new PlaceWall(tile, this->stackModel));
                }
                case ObjectTile::FLOOR:
                {
                    // Command PlaceFloor
                }
                default: break;
            }
            break;
        }
        case ObjectBase::SPECIAL:
        {
            ObjectSpecial *special = qobject_cast<ObjectSpecial *>(this->placeableObject);

            return this->processor->execute(new PlaceSpecial(special, this->stackModel));

            break;
        }
        default: break;
    }

    std::cout << "Error placing an object on a mainview stack: Unexpected type of object to be placed." << std::endl;
    return false;
}
