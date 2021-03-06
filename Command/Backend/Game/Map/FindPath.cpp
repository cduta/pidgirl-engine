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

#include "FindPath.h"

#include <iostream>

FindPath::FindPath(StackModel *from, StackModel *to, QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("FindPath");
    this->from = from;
    this->to = to;
}

bool FindPath::execute()
{
    this->setErrorEnabled(false);
    if(!this->from || !this->to || !this->gameModel->isYourTurn())
    {
        return false;
    }

    this->aStarMap = AStarMap();
    this->aStarMap.fromMapModel(this->mapModel);
    if(!this->aStarMap.calculatePath(this->from->getSquarePos(), this->to->getSquarePos())){
        return false;
    }

    this->mapModel->clearPath();
    this->mapModel->setConvertedPath(this->aStarMap.getPath());
    return true;
}
