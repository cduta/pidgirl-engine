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

#include "TargetMoveState.h"

#include "MainView/Model/MouseInput/IdleGameMouseState.h"
#include "MainView/Model/MouseInput/TargetConfirmedState.h"
#include "Command/Backend/Game/Map/MoveCharacter.h"

TargetMoveState::TargetMoveState(Processor *processor, StackModel *target)
    : MouseState(processor, target)
{
}

MouseState *TargetMoveState::nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack, StackModel *fromStack)
{
    MouseState *nextState = this;

    switch(type)
    {
    case MouseState::RELEASED:
    {
        switch(event->button())
        {
        case Qt::LeftButton:
        {
            if(this->target == targetStack)
            {
                qDebug("TargetMove -> IdleMouse : Move");
                this->processor->execute(new MoveCharacter(fromStack, this->target));
                nextState = new IdleGameMouseState(this->processor, targetStack);
            }
            else
            {
                qDebug("TargetMove -> TargetConfirmed : Don't Move");
                nextState = new TargetConfirmedState(this->processor, this->target);
            }
        }
        default: break;
        }
        break;
    }
    default: break;
    }

    if(nextState != this)
    {
        delete this;
    }

    return nextState;
}
