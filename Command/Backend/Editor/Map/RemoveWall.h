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

#ifndef REMOVE_WALL_H
#define REMOVE_WALL_H

#include "Command/Backend/Undoable.h"
#include "MainView/Model/StackModel.h"
#include "Object/ObjectTile.h"

/** \addtogroup Commands
  * \{
  * \class RemoveWall
  *
  * \brief Remove a wall from a chosen stack.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class RemoveWall : public Undoable
{
    Q_OBJECT

    StackModel *stackModel; ///< The stack from which to remove the wall from.
    ObjectTile *oldWall;    ///< The wall which has been removed.

public:
    explicit RemoveWall(StackModel *stackModel, QObject *parent = 0);

    virtual bool execute();
    virtual void undo();
    virtual void redo();
};

#endif // REMOVE_WALL_H
