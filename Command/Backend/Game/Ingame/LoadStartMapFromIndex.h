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

#ifndef LOAD_START_MAP_FROM_INDEX_H
#define LOAD_START_MAP_FROM_INDEX_H

#include "Command/Backend/Game/GameCommand.h"

/** \addtogroup Commands
  * \{
  * \class LoadStartMapFromIndex
  *
  * \brief Load the map depending on the index given. Can be random as well.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class LoadStartMapFromIndex : public GameCommand
{
    Q_OBJECT

    int startMapIndex; ///< The index from which to load the start map from looked up in the world model. If -1 or anything invalid, choose a random map from the starter maps.

public:
    LoadStartMapFromIndex(int startMapIndex, QObject *parent = 0);

    virtual bool execute();
};

#endif // LOAD_START_MAP_FROM_INDEX_H
