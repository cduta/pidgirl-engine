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

#ifndef COPY_WALL_H
#define COPY_WALL_H

#include "Command/Backend/NotUndoable.h"
#include "MainView/Model/StackModel.h"
#include "Object/ObjectTile.h"

/** \addtogroup Commands
  * \{
  * \class CopyWall
  *
  * \brief Copy the wall to the clipboard.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class CopyWall : public NotUndoable
{
    Q_OBJECT

private:
    ObjectTile *wall; ///< The wall to be copied.

public:
    CopyWall(StackModel *stackModel, QObject *parent = 0);

    virtual bool execute();
};

#endif // COPY_WALL_H
