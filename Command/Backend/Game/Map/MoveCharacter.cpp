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

#include "MoveCharacter.h"

MoveCharacter::MoveCharacter(StackModel *from, StackModel *to, QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("MoveCharacter");
    this->from = from;
    this->to = to;
}

bool MoveCharacter::execute()
{
    if(!this->from || !this->to || !this->gameModel->isYourTurn())
    {
        return false;
    }

    ObjectCharacter *oldCharacter = this->from->refCharacter()->copy();
    oldCharacter->setParent(this);
    ObjectCharacter *newCharacter = this->from->refCharacter()->copy();
    newCharacter->setParent(this);

    newCharacter->setPosition(to->getSquarePos().x(), to->getSquarePos().y(), to->getHeight());

    this->mapModel->clearPath();

    return this->gameModel->updateCharacter(this->gameModel->getPlayerID(),
                                            this->mapModel,
                                            *oldCharacter,
                                            *newCharacter);
}
