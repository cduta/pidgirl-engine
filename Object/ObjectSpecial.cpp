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

#include "ObjectSpecial.h"

ObjectSpecial::ObjectSpecial(int maxAmountPerStack, bool visibleInGame, const QString &name, const QString &description, const QString &imagePath, bool isVisible, QObject *parent)
    : ObjectBase(name, description, imagePath, isVisible, parent)
{
    this->initObjectSpecial(maxAmountPerStack, visibleInGame);
}

ObjectSpecial::ObjectSpecial(const ObjectSpecial &objectSpecial)
    : ObjectBase(objectSpecial)
{
    this->initObjectSpecial(objectSpecial.getMaxAmountPerStack(), objectSpecial.isVisibleInGame());
}

void ObjectSpecial::initObjectSpecial(int maxAmountPerStack, bool visibleInGame)
{
    this->setMaxAmountPerStack(maxAmountPerStack);
    this->setVisibleInGame(visibleInGame);
    return;
}

ObjectBase *ObjectSpecial::copyBase() const
{
    return this->copy();
}

void ObjectSpecial::updateSpecial(const ObjectSpecial &special)
{
    this->updateBase(special);

    this->setMaxAmountPerStack(special.getMaxAmountPerStack());
    this->setIsVisible(special.getIsVisible());

    return;
}

ObjectBase::ObjectType ObjectSpecial::getType() const
{
    return ObjectBase::SPECIAL;
}

int ObjectSpecial::getObjectIDNumber() const
{
    return this->getObjectID();
}

int ObjectSpecial::getMaxAmountPerStack() const
{
    return this->maxAmountPerStack;
}

bool ObjectSpecial::isVisibleInGame() const
{
    return this->visibleInGame;
}

void ObjectSpecial::setMaxAmountPerStack(int maxAmountPerStack)
{
    this->maxAmountPerStack = maxAmountPerStack;
    return;
}

void ObjectSpecial::setVisibleInGame(bool visibleInGame)
{
    this->visibleInGame = visibleInGame;
    return;
}

void ObjectSpecial::serialize(QDataStream &dataStream) const
{
    ObjectBase::serialize(dataStream);

    dataStream << this->getMaxAmountPerStack();
    dataStream << this->isVisibleInGame();
}

void ObjectSpecial::deserialize(QDataStream &dataStream)
{
    ObjectBase::deserialize(dataStream);

    int maxAmountPerStack;
    bool visibleInGame;

    dataStream >> maxAmountPerStack;
    dataStream >> visibleInGame;

    this->initObjectSpecial(maxAmountPerStack, visibleInGame);
}
