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

#ifndef REPLY_TO_REQUEST_FOR_MAP_H
#define REPLY_TO_REQUEST_FOR_MAP_H

#include "Command/Backend/Network/Server/ServerCommand.h"

/** \addtogroup Commands
  * \{
  * \class ReplyToRequestForMap
  *
  * \brief Reply a requested map to a player.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ReplyToRequestForMap : public ServerCommand
{
    Q_OBJECT

public:
    ReplyToRequestForMap(unsigned int playerID, QObject *parent = 0);

    virtual bool execute();
};

#endif // REPLY_TO_REQUEST_FOR_MAP_H
