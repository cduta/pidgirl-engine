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

#ifndef PRELOAD_ALL_MAPS_H
#define PRELOAD_ALL_MAPS_H

#include "Command/Backend/Game/GameCommand.h"

#include "Common/FileManager.h"

/** \addtogroup Commands
  * \{
  * \class PreloadAllMaps
  *
  * \brief Preload the maps if it's a local game or a server.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class PreloadAllMaps : public GameCommand
{
    Q_OBJECT

    FileManager fileManager; ///< The file manager to preload all the maps in the world folder.

public:
    PreloadAllMaps(QObject *parent = 0);

    virtual bool execute();

private:
    /**
      * @brief Preload maps from a list of files.
      * @param Entries in the current folder.
      * @return New list of files in found sub folders.
      */
    QList<QFileInfoList> preload(QFileInfoList entries);
};

#endif // PRELOAD_ALL_MAPS_H
