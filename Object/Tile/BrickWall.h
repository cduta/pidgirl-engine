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

#ifndef BRICK_WALL_H
#define BRICK_WALL_H

#include "Object/ObjectTile.h"
#include "Object/ObjectID.h"

/** \addtogroup Object
  * \{
  * \class BrickWall
  *
  * \brief A wall of bricks.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class BrickWall : public ObjectTile
{
    Q_OBJECT

public:
    BrickWall(QObject *parent = 0);
    BrickWall(const BrickWall &brickWall);

    QWidget *createInformationWidget(QWidget *parent) const;

    virtual ObjectTile *copy() const;
    virtual void update(const ObjectBase &object);

    // Get-Methods
    virtual ObjectID::TileID getObjectID() const;
    virtual QMap<QString, BaseCommand *> getCommandList() const;

    // Serialize
    virtual void serialize(QDataStream &dataStream) const;
    virtual void serialize(QIODevice *device) const;
    virtual void deserialize(QDataStream &dataStream);
    virtual void deserialize(QIODevice *device);
};

#endif // BRICK_WALL_H
