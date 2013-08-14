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

#include "PlaceWall.h"

PlaceWall::PlaceWall(ObjectTile *wall, StackModel *stackModel, QObject *parent) :
    Undoable(parent)
{
    this->setObjectName("PlaceWall");
    this->wall = wall;
    this->oldWall = 0;
    this->stackModel = stackModel;
}

bool PlaceWall::execute()
{
    if(!this->wall || this->wall->getTileType() != ObjectTile::WALL)
    {
        return false;
    }

    if(this->stackModel->refCharacter() || this->stackModel->specialIDExists(ObjectID::START_POSITION))
    {
        this->setErrorEnabled(false);
        return false;
    }

    this->wall->setSpawnID(this->worldModel->refObjectID()->getNewSpawnIDFor(this->wall->getObjectID()));

    this->oldWall = this->stackModel->replaceWall(this->wall);

    if(this->oldWall)
    {
        this->oldWall->setParent(this);
    }

    return this->stackModel->refWall() != 0;
}

void PlaceWall::undo()
{
    this->stackModel->setWall(this->oldWall);
    this->wall->setParent(this);

    return;
}

void PlaceWall::redo()
{
    this->stackModel->setWall(this->wall);

    if(this->oldWall)
    {
        this->oldWall->setParent(this);
    }

    return;
}
