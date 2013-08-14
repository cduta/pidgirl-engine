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

#ifndef CLIENT_DISCONNECTED_H
#define CLIENT_DISCONNECTED_H

#include "Command/Backend/Network/Server/ServerCommand.h"

/** \addtogroup Commands
  * \{
  * \class ClientDisconnected
  *
  * \brief Command is triggered whenever a client is disconnected.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ClientDisconnected : public ServerCommand
{
    Q_OBJECT

public:
    ClientDisconnected(unsigned int playerID, QObject *parent = 0);

    virtual bool execute();
};

#endif // CLIENTDISCONNECTED_H
