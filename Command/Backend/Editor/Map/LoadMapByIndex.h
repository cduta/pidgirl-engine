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

#ifndef LOAD_MAP_BY_INDEX_H
#define LOAD_MAP_BY_INDEX_H

#include <QModelIndex>

#include "Command/Backend/NotUndoable.h"

/** \addtogroup Commands
  * \{
  * \class LoadMapByIndex
  *
  * \brief Load a map according to the given path in a model index.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class LoadMapByIndex : public NotUndoable
{
    Q_OBJECT

private:
    QModelIndex     modelIndex; ///< The model index from which to load the map from.
    bool            ask;        ///< True, if before loading a new map it should ask for changes to be saved.

public:
    LoadMapByIndex(const QModelIndex &modelIndex, bool ask = true, QObject *parent = 0);

    virtual bool execute();
};

#endif // LOAD_MAP_BY_INDEX_H
