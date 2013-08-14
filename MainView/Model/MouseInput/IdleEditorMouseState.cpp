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

#include "IdleEditorMouseState.h"

#include "MainView/Model/MouseInput/PlaceObjectsState.h"
#include "MainView/Model/MouseInput/RemoveObjectsState.h"
#include "MainView/Model/MouseInput/ContextEditorMenuState.h"

IdleEditorMouseState::IdleEditorMouseState(Processor *processor, StackModel *targetStack)
    : MouseState(processor, targetStack)
{
}

MouseState *IdleEditorMouseState::nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack, StackModel *fromStack)
{
    Q_UNUSED(fromStack);

    MouseState *nextState = this;

    switch(type)
    {
    case MouseState::PRESSED:
    {
        switch(event->button())
        {
        case Qt::LeftButton:
        {
            qDebug("IdleMouse -> PlaceObjects");
            nextState = new PlaceObjectsState(this->processor, targetStack);
            break;
        }
        case Qt::MiddleButton:
        {
            qDebug("IdleMouse -> RemoveObjects");
            nextState = new RemoveObjectsState(this->processor, targetStack);
            break;
        }
        case Qt::RightButton:
        {
            qDebug("IdleMouse -> ContextMenu");
            nextState = new ContextEditorMenuState(this->processor, targetStack);
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
