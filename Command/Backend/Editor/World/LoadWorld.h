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

#ifndef LOAD_WORLD_H
#define LOAD_WORLD_H

#include "Command/Backend/NotUndoable.h"
#include "Common/FileManager.h"

/** \addtogroup Commands
  * \{
  * \class LoadWorld
  *
  * \brief Choose the name of a file and load the world from this file.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class LoadWorld : public NotUndoable
{
    Q_OBJECT

private:
    FileManager     fileManager;        ///< The file manager to load the world with.
    bool            mayAsk;             ///< True, if it should be asked for unsaved changes to be saved.
    bool            resetToStandardMap; ///< True, if a standard map is to be loaded to the current map model when loading a world.

public:
    LoadWorld(bool resetToStandardMap = true, bool mayAsk = true, QObject *parent = 0);

    bool execute();

private:
    /**
      * \brief Load a new world from a file loaded with the filemanager.
      * \returns True, if successful. Otherwise, false.
      */
    bool loadWorld();
};

#endif // LOAD_WORLD_H
