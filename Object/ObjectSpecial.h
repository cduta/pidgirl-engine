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

#ifndef OBJECT_SPECIAL_H
#define OBJECT_SPECIAL_H

#include "Object/ObjectID.h"

/** \addtogroup Object
  * \{
  * \class ObjectTile
  *
  * \brief Represents a tile to be put into the mainView.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
#include "Object/ObjectBase.h"

class ObjectSpecial : public ObjectBase
{
    Q_OBJECT
    int maxAmountPerStack;
    bool visibleInGame;

public:
    explicit ObjectSpecial(int maxAmountPerStack = 1, bool visibleInGame = false, const QString &name = "", const QString &description = "", const QString &imagePath = "", bool isVisible = true, QObject *parent = 0);
    explicit ObjectSpecial(const ObjectSpecial& objectSpecial);

protected:
    /**
      * \brief Initialize Attributes
      */
    void initObjectSpecial(int maxAmountPerStack = 1, bool visibleInGame = false);

public:
    virtual ObjectSpecial *copy() const = 0;
    virtual ObjectBase *copyBase() const;

    virtual void update(const ObjectBase &object) = 0;
    void updateSpecial(const ObjectSpecial &special);

    // Get-Methods
    virtual ObjectBase::ObjectType getType() const;
    virtual ObjectID::SpecialID getObjectID() const = 0;
    virtual int getObjectIDNumber() const;
    int getMaxAmountPerStack() const;
    bool isVisibleInGame() const;

    // Set-Methods
    void setMaxAmountPerStack(int maxAmountPerStack);
    void setVisibleInGame(bool visibleInGame);

    // Serialize
    virtual void serialize(QDataStream &dataStream) const;
    virtual void serialize(QIODevice *device) const = 0;
    virtual void deserialize(QDataStream &dataStream);
    virtual void deserialize(QIODevice *device) = 0;
};

#endif // OBJECT_SPECIAL_H
