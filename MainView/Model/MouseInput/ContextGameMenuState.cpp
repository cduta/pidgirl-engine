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

#include "ContextGameMenuState.h"

#include "Command/Backend/Game/Map/FindPath.h"
#include "MainView/Model/MouseInput/IdleGameMouseState.h"
#include "MainView/Model/MouseInput/TargetChosenState.h"

ContextGameMenuState::ContextGameMenuState(Processor *processor, StackModel *target)
    : MouseState(processor, target)
{
}

MouseState *ContextGameMenuState::nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack, StackModel *fromStack)
{
    MouseState *nextState = this;

    switch(type)
    {
    case MouseState::PRESSED:
    {
        switch(event->button())
        {
        case Qt::LeftButton:
        {
            if(this->processor->execute(new FindPath(fromStack, targetStack)))
            {
                qDebug("ContextMenu -> TargetChosen");
                nextState = new TargetChosenState(this->processor, targetStack);
            }
            else
            {
                qDebug("ContextMenu -> IdleMouse");
                nextState = new IdleGameMouseState(this->processor, targetStack);
            }
            break;
        }
        case Qt::RightButton:
        {
            qDebug("ContextMenu -> ContextMenu");
            break;
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

bool ContextGameMenuState::showContextMenu()
{
    return true;
}
