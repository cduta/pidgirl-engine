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

#ifndef OBJECT_ITEM_H
#define OBJECT_ITEM_H

#include "Object/ObjectBase.h"

#include "Object/ObjectID.h"

/** \addtogroup Object
  * \{
  * \class ObjectItem
  *
  * \brief The baseclass for the Items to be placed into the game's mainView.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ObjectItem : public ObjectBase
{
    Q_OBJECT

public:
    explicit ObjectItem(const QString &name = "", const QString &description = "", const QString &imagePath = "", bool isVisible = true, QObject *parent = 0);
    explicit ObjectItem(const ObjectItem &objectItem);

protected:
    /**
      * \brief Initialize Attributes
      */
    void initObjectItem();

public:
    virtual ObjectItem *copy() const = 0;
    virtual ObjectBase *copyBase() const;

    virtual void update(const ObjectBase &object) = 0;
    void updateItem(const ObjectItem &item);

    // Get-Methods
    virtual ObjectBase::ObjectType getType() const;
    virtual ObjectID::ItemID getObjectID() const = 0;
    virtual int getObjectIDNumber() const;

    // Serialize
    virtual void serialize(QDataStream &dataStream) const;
    virtual void serialize(QIODevice *device) const = 0;
    virtual void deserialize(QDataStream &dataStream);
    virtual void deserialize(QIODevice *device) = 0;
};

#endif // OBJECT_ITEM_H
