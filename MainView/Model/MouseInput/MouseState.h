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

#ifndef MOUSE_STATE_H
#define MOUSE_STATE_H

#include <QMouseEvent>
#include "MainView/Model/StackModel.h"
#include "Command/Processor.h"

/** \addtogroup State
  * \{
  * \class MouseState
  *
  * \brief The interface used for any state concerning mouse inputs.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MouseState
{
public:
    enum MouseEventType {PRESSED = 0, RELEASED};

protected:
    Processor *     processor;
    StackModel *    target;

public:
    MouseState(Processor *processor, StackModel *target = 0);
    virtual ~MouseState();

    /**
     * @brief Determines which state is next, depending on the input. This method might destroy this state and changes occur.
     * @param event Holds the event that has been triggered.
     * @param stack The stack where this method has been invoked from.
     * @returns a pointer to the next state.
     */
    virtual MouseState *nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack, StackModel *fromStack = 0) = 0;

    // Get-Methods
    virtual bool showContextMenu();

    // Set-Methods
    void setTarget(StackModel *targetStack);

    // Ref-Methods
    StackModel *refTarget();
};

#endif // MOUSE_STATE_H
