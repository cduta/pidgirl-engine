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

#ifndef FIND_PATH_H
#define FIND_PATH_H

#include "Command/Backend/Game/GameCommand.h"
#include "MainView/Model/StackModel.h"
#include "AStar/AStarMap.h"

/** \addtogroup Commands
  * \{
  * \class FindPath
  *
  * \brief Creates a path that shows how to get from one stack to another.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class FindPath : public GameCommand
{
    Q_OBJECT

private:
    StackModel *from;       ///< The stack from where to start the path from.
    StackModel *to;         ///< The stack to where the path leads to.
    AStarMap    aStarMap;   ///< The A* Map where the path will be calculated with.

public:
    FindPath(StackModel *from, StackModel *to, QObject *parent = 0);

    virtual bool execute();
};

#endif // FIND_PATH_H
