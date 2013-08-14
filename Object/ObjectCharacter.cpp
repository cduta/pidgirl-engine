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

#include "Object/ObjectCharacter.h"

ObjectCharacter::ObjectCharacter(const QString &name, const QString &description, const QString &imagePath, bool isVisible, QObject *parent) :
    ObjectBase(name, description, imagePath, isVisible, parent)
{
    this->initObjectCharacter();
}

ObjectCharacter::ObjectCharacter(const ObjectCharacter &objectCharacter) :
    ObjectBase(objectCharacter)
{
    this->initObjectCharacter();
}

void ObjectCharacter::initObjectCharacter()
{
    return;
}

ObjectBase *ObjectCharacter::copyBase() const
{
    return this->copy();
}

void ObjectCharacter::updateCharacter(const ObjectCharacter &character)
{
    this->updateBase(character);
    return;
}

ObjectBase::ObjectType ObjectCharacter::getType() const
{
    return ObjectBase::CHARACTER;
}

int ObjectCharacter::getObjectIDNumber() const
{
    return this->getObjectID();
}

void ObjectCharacter::serialize(QDataStream &dataStream) const
{
    ObjectBase::serialize(dataStream);
    return;
}

void ObjectCharacter::deserialize(QDataStream &dataStream)
{
    ObjectBase::deserialize(dataStream);

    this->initObjectCharacter();

    return;
}
