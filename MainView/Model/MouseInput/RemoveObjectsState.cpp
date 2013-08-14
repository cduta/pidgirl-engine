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

#include "RemoveObjectsState.h"

#include "MainView/Model/MouseInput/IdleEditorMouseState.h"

#include "Command/Backend/Editor/Map/RemoveAllObjects.h"

RemoveObjectsState::RemoveObjectsState(Processor *processor, StackModel *targetStack)
    : MouseState(processor, targetStack)
{
    if(this->processor->execute(new RemoveAllObjects(targetStack)))
    {
        this->alreadyPlaced.insert(targetStack);
    }
}

MouseState *RemoveObjectsState::nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack, StackModel *fromStack)
{
    Q_UNUSED(fromStack);

    MouseState *nextState = this;

    switch(type)
    {
    case MouseState::PRESSED:
    {
        switch(event->button())
        {
        case Qt::MiddleButton:
        {
            if(!this->alreadyPlaced.contains(targetStack) &&
               this->processor->execute(new RemoveAllObjects(targetStack)))
            {
                qDebug("RemoveObjects -> RemoveObjects : Remove Object");
                this->alreadyPlaced.insert(targetStack);
            }
            break;
        }
        default: break;
        }
        break;
    }
    case MouseState::RELEASED:
    {
        switch(event->button())
        {
        case Qt::MiddleButton:
        {
            qDebug("RemoveObjects -> IdleMouse");
            nextState = new IdleEditorMouseState(this->processor, targetStack);
            break;
        }
        default: break;
        }
    }
    default: break;
    }

    if(nextState != this)
    {
        delete this;
    }

    return nextState;
}
