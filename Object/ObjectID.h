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

#ifndef OBJECT_ID_H
#define OBJECT_ID_H

#include <QMap>

/** \addtogroup Object
  * \{
  * \class ObjectID
  *
  * \brief Information and management of spawnIDs for the corresponding ObjectIDs.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ObjectID
{
public:
    enum CharacterID
    {
        PLAYER = 0
    };

    enum ItemID
    {
        KNIFE = 0
    };

    enum TileID
    {
        BRICK_WALL = 0
    };

    enum SpecialID
    {
        START_POSITION = 0
    };

private:
    QMap<int, unsigned int> characterSpawnIDMap; ///< Contains all the possible spawnIDs for characters. Start at 1, if no ID existed before.
    QMap<int, unsigned int> itemSpawnIDMap;      ///< Contains all the possible spawnIDs for items. Start at 1, if no ID existed before.
    QMap<int, unsigned int> specialSpawnIDMap;   ///< Contains all the possible spawnIDs for specials. Start at 1, if no ID existed before.
    QMap<int, unsigned int> tileSpawnIDMap;      ///< Contains all the possible spawnIDs for tiles. Start at 1, if no ID existed before.

public:
    ObjectID();

    unsigned int getNewSpawnIDFor(ObjectID::CharacterID id);
    unsigned int getNewSpawnIDFor(ObjectID::ItemID id);
    unsigned int getNewSpawnIDFor(ObjectID::SpecialID id);
    unsigned int getNewSpawnIDFor(ObjectID::TileID id);

private:
    unsigned int getNewSpawnIDFromMap(QMap<int, unsigned int> &map, int id);
    void serialize(const QMap<int, unsigned int> &map, QDataStream &stream) const;
    void deserialize(QMap<int, unsigned int> &map, QDataStream &stream);

public:
    // Serialize
    virtual void serialize(QDataStream &stream) const;
    virtual void deserialize(QDataStream &stream);
};

#endif // OBJECT_ID_H
