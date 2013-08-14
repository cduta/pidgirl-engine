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

#ifndef RECEIVE_UPDATE_CHARACTER_FROM_H
#define RECEIVE_UPDATE_CHARACTER_FROM_H

#include "Command/Backend/Network/NetworkCommand.h"

/** \addtogroup Commands
  * \{
  * \class ReceiveUpdateCharacterFrom
  *
  * \brief Receive the Updated Character from any given sender ID.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ReceiveUpdateCharacterFrom : public NetworkCommand
{
    Q_OBJECT
    unsigned int senderID; ///< The sender ID that the character sent by.

public:
    ReceiveUpdateCharacterFrom(unsigned int senderID, QObject *parent = 0);

    virtual bool execute();
};

#endif // RECEIVE_UPDATE_CHARACTER_FROM_H
