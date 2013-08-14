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

#ifndef BROADCAST_COMMAND_H
#define BROADCAST_COMMAND_H

#include "Command/Backend/Network/Server/ServerCommand.h"

/** \addtogroup Commands
  * \{
  * \class BroadcastCommand
  *
  * \brief Broadcast information to all clients on the same map the information was sent from.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class BroadcastCommand : public ServerCommand
{
    Q_OBJECT

protected:
    QList<unsigned int> broadcastPlayerIDs; ///< The Player IDs to which information has to be sent to. The IDs are all from the same player map where the information changed.

public:
    /**
      * @brief Broadcast the command
      * @param receivedByID The ID from which the command was received and does not have to be sent to.
      * @param playerList The list of players.
      * @param localMapPath The map that the information changed in.
      */
    BroadcastCommand(unsigned int receivedByID,
                     const QList<PlayerModel *> &playerList,
                     const QString &localMapPath,
                     QObject *parent = 0);

    virtual bool execute() = 0;
};

#endif // BROADCAST_COMMAND_H
