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

#include "RemoveWall.h"

RemoveWall::RemoveWall(StackModel *stackModel, QObject *parent)
    : Undoable(parent)
{
    this->setObjectName("RemoveWall");
    this->stackModel = stackModel;
    this->oldWall = 0;
}

bool RemoveWall::execute()
{
    this->oldWall = this->stackModel->replaceWall(0);
    this->oldWall->setParent(this);

    return this->stackModel->refWall() == 0;
}

void RemoveWall::undo()
{
    this->stackModel->setWall(this->oldWall);
    return;
}

void RemoveWall::redo()
{
    this->stackModel->removeWall();
    this->oldWall->setParent(this);

    return;
}
