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

#ifndef NEW_MAP_FILE_H
#define NEW_MAP_FILE_H

#include <QModelIndexList>

#include "Command/Backend/NotUndoable.h"
#include "Common/FileManager.h"

/** \addtogroup Commands
  * \{
  * \class NewMapFile
  *
  * \brief Create a new map file.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class NewMapFile : public NotUndoable
{
    Q_OBJECT

private:
    QModelIndex     index;          ///< The index where to create a new map.
    FileManager     fileManager;    ///< The file manager to create the map with.
    QDir            dir;            ///< The directory in which to create the new map in.
    QString         file;           ///< The file name which to create.

public:
    NewMapFile(const QModelIndex &index, QObject *parent = 0);

    virtual bool execute();
};

#endif // NEW_MAP_FILE_H
