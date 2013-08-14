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

#include "RemoveAllObjects.h"

RemoveAllObjects::RemoveAllObjects(StackModel *stackModel, QObject *parent)
    : Undoable(parent)
{
    this->setObjectName("RemoveAllObjects");
    this->stackModel = stackModel;
    this->undoCharacter = 0;
    this->undoWall = 0;
    this->undoFloor = 0;
}

bool RemoveAllObjects::execute()
{
    this->undoItemList = this->stackModel->takeAllItems();

    for(int i = 0; i < this->undoItemList.size(); ++i)
    {
        this->undoItemList[i]->setParent(this);
    }

    this->undoCharacter = this->stackModel->takeCharacter();
    if(this->undoCharacter)
    {
        this->undoCharacter->setParent(this);
    }

    this->undoWall = this->stackModel->takeWall();
    if(this->undoWall)
    {
        this->undoWall->setParent(this);
    }

    this->undoFloor = this->stackModel->takeFloor();
    if(this->undoFloor)
    {
        this->undoFloor->setParent(this);
    }

    this->undoSpecialList = this->stackModel->takeAllSpecial();
    for(int i = 0; i < this->undoSpecialList.size(); ++i)
    {
        this->undoSpecialList[i]->setParent(this);
    }

    return true;
}

void RemoveAllObjects::undo()
{
    this->stackModel->setItemList(this->undoItemList);
    this->stackModel->setCharacter(this->undoCharacter);
    this->stackModel->setWall(this->undoWall);
    this->stackModel->setFloor(this->undoFloor);
    this->stackModel->setSpecialList(this->undoSpecialList);
    return;
}

void RemoveAllObjects::redo()
{
    this->stackModel->removeAll();

    for(int i = 0; i < this->undoItemList.size(); ++i)
    {
        this->undoItemList[i]->setParent(this);
    }

    if(this->undoCharacter)
    {
        this->undoCharacter->setParent(this);
    }

    if(this->undoWall)
    {
        this->undoWall->setParent(this);
    }

    if(this->undoFloor)
    {
        this->undoFloor->setParent(this);
    }

    for(int i = 0; i < this->undoSpecialList.size(); ++i)
    {
        this->undoSpecialList[i]->setParent(this);
    }

    return;
}
