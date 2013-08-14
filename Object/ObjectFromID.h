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

#ifndef OBJECT_FROM_ID_H
#define OBJECT_FROM_ID_H

#include "Object/ObjectID.h"
#include "Object/ObjectCharacter.h"
#include "Object/ObjectItem.h"
#include "Object/ObjectTile.h"
#include "Object/ObjectSpecial.h"

namespace ObjectFromID
{
    /**
     * @brief Create object from an enum.
     * @param id The id the character gets.
     * @param parent The parent to be set for that object.
     * @return Returns the created object.
     */
    ObjectCharacter *objectFrom(ObjectID::CharacterID id, QObject *parent = 0);
    ObjectItem *objectFrom(ObjectID::ItemID id, QObject *parent = 0);
    ObjectSpecial *objectFrom(ObjectID::SpecialID id, QObject *parent = 0);
    ObjectTile *objectFrom(ObjectID::TileID id, QObject *parent = 0);
}

#endif // OBJECT_FROM_ID_H
