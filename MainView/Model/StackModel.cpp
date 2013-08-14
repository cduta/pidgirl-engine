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

#include "StackModel.h"

#include <iostream>

#include "Object/Character/Player.h"
#include "Object/ObjectFromID.h"

StackModel::StackModel(int xPos, int yPos, int height, QObject *parent) :
    QObject(parent)
{
    this->initStack(QPoint(xPos, yPos), height);
}

StackModel::StackModel(QPoint pos, int height, QObject *parent) :
    QObject(parent)
{
    this->initStack(pos, height);
}

StackModel::StackModel(const StackModel &stackModel)
    : QObject(stackModel.parent())
{
    QPoint point = stackModel.getSquarePos();
    int z = stackModel.getHeight();
    this->setPosition(point.x(), point.y(), z);

    this->resetPathDirection();

    for(int i = stackModel.itemListSize() - 1; i >= 0; --i)
    {
        this->prependItem(stackModel.refItem(i)->copy());
    }

    for(int i = stackModel.specialListSize() - 1; i >= 0; --i)
    {
        this->prependSpecial(stackModel.refSpecial(i)->copy());
    }

    this->setCharacter(stackModel.refCharacter()->copy());
    this->setWall(stackModel.refWall()->copy());
    this->setFloor(stackModel.refFloor()->copy());
}

bool StackModel::specialIDExists(ObjectID::SpecialID id) const
{
    for(int i = 0; i < this->specialList.size(); ++i)
    {
        if(this->specialList[i]->getObjectID() == id)
        {
            return true;
        }
    }

    return false;
}

void StackModel::removeAll()
{
    this->removeAllItems();
    this->removeAllSpecials();
    this->removeCharacter();
    this->removeWall();
    this->removeFloor();
    return;
}

void StackModel::deleteAll()
{
    this->deleteAllItems();
    this->deleteAllSpecials();
    this->deleteCharacter();
    this->deleteWall();
    this->deleteFloor();
}

void StackModel::initStack(const QPoint &squarePos, int height)
{
    this->squarePos = squarePos;
    this->height = height;

    this->character = 0;
    this->wall = 0;
    this->floor = 0;
    this->pathIndication = StackModel::NONE;

    return;
}

void StackModel::resetPathDirection()
{
    this->setPathIndication(StackModel::NONE);
    return;
}

void StackModel::prependItem(ObjectItem *item)
{
    if(!item)
    {
        return;
    }

    this->itemList.prepend(item);
    item->setParent(this);
    item->setPosition(this->squarePos.x(), this->squarePos.y(), this->height);
    emit this->itemListChanged();

    return;
}

void StackModel::removeItem(int i)
{
    this->itemList[i]->unsetPosition();
    this->itemList.removeAt(i);
    emit this->itemListChanged();

    return;
}

ObjectItem *StackModel::takeItem(int i)
{
    ObjectItem *item = this->refItem(i);

    this->removeItem(i);

    return item;
}

void StackModel::deleteItem(int i)
{
    ObjectItem *item = this->takeItem(i);
    item->deleteLater();
    return;
}

void StackModel::removeAllItems()
{
    for(int i = 0; i < this->itemList.size(); ++i)
    {
        this->removeItem(i);
    }
    return;
}

QList<ObjectItem *> StackModel::takeAllItems()
{
    QList<ObjectItem *> itemList = this->itemList;

    this->removeAllItems();

    return itemList;
}

void StackModel::deleteAllItems()
{
    for(int i = 0; i < this->itemList.size(); ++i)
    {
        this->deleteItem(i);
    }

    return;
}

int StackModel::itemListSize() const
{
    return this->itemList.size();
}

void StackModel::prependSpecial(ObjectSpecial *special)
{
    if(!special)
    {
        return;
    }

    this->specialList.prepend(special);
    special->setPosition(this->squarePos.x(), this->squarePos.y(), this->height);
    special->setParent(this);
    emit this->specialListChanged();

    if(special->getObjectID() == ObjectID::START_POSITION)
    {
        emit this->startPositionSet(this);
    }

    return;
}

void StackModel::removeSpecial(int i)
{
    if(this->specialList[i]->getObjectID() == ObjectID::START_POSITION)
    {
        emit this->startPositionRemoved(this);
    }

    this->specialList[i]->unsetPosition();
    this->specialList.removeAt(i);
    emit this->specialListChanged();

    return;
}

ObjectSpecial *StackModel::takeSpecial(int i)
{
    ObjectSpecial *special = this->refSpecial(i);

    this->removeSpecial(i);

    return special;
}

void StackModel::deleteSpecial(int i)
{
    ObjectSpecial *special = this->takeSpecial(i);
    special->deleteLater();
    return;
}

void StackModel::removeAllSpecials()
{
    for(int i = 0; i < this->specialList.size(); ++i)
    {
        this->removeSpecial(i);
    }
    return;
}

QList<ObjectSpecial *> StackModel::takeAllSpecial()
{
    QList<ObjectSpecial *> specialList = this->specialList;

    this->removeAllSpecials();

    return specialList;
}

void StackModel::deleteAllSpecials()
{
    for(int i = 0; i < this->specialList.size(); ++i)
    {
        this->deleteSpecial(i);
    }

    return;
}

int StackModel::specialListSize() const
{
    return this->specialList.size();
}

bool StackModel::hasSpaceForSpecial(ObjectSpecial *special) const
{
    int specialCount = 0;

    for(int i = 0; i < this->specialList.size(); ++i)
    {
        if(this->refSpecial(i)->getObjectID() == special->getObjectID())
        {
            specialCount++;
        }
    }

    return specialCount < special->getMaxAmountPerStack();
}

ObjectCharacter *StackModel::replaceCharacter(ObjectCharacter *character)
{
    ObjectCharacter *oldCharacter = this->takeCharacter();
    this->setCharacter(character);
    return oldCharacter;
}

ObjectCharacter *StackModel::takeCharacter()
{
    ObjectCharacter *character = this->refCharacter();
    this->removeCharacter();
    return character;
}

void StackModel::removeCharacter()
{
    if(this->character)
    {
        if(this->character->getObjectID() == ObjectID::PLAYER)
        {
            emit this->playerRemoved(this);
        }

        this->character->unsetPosition();
    }

    this->character = 0;
    emit this->characterChanged();
    return;
}

void StackModel::deleteCharacter()
{
    if(this->character)
    {
        ObjectCharacter *character = this->takeCharacter();
        character->deleteLater();
    }
    return;
}

bool StackModel::hasCharacter() const
{
    return this->character != 0;
}

bool StackModel::characterExists(ObjectCharacter *character) const
{
    return this->characterExists(character->getObjectID(), character->getSpawnID());
}

bool StackModel::characterExists(ObjectID::CharacterID characterID, unsigned int spawnID) const
{
    return this->character != 0 && this->character->getObjectID() == characterID && this->character->getSpawnID() == spawnID;
}

ObjectTile *StackModel::replaceWall(ObjectTile *wall)
{
    ObjectTile *oldWall = this->takeWall();
    this->setWall(wall);
    return oldWall;
}

ObjectTile *StackModel::takeWall()
{
    ObjectTile *wall = this->refWall();
    this->removeWall();
    return wall;
}

void StackModel::removeWall()
{
    if(this->wall)
    {
        this->wall->unsetPosition();
    }

    this->wall = 0;
    emit this->wallChanged();
    return;
}

void StackModel::deleteWall()
{
    if(this->wall)
    {
        ObjectTile *wall = this->takeWall();
        wall->deleteLater();
    }
    return;
}

bool StackModel::hasWall() const
{
    return this->wall != 0;
}

ObjectTile *StackModel::replaceFloor(ObjectTile *floor)
{
    ObjectTile *oldFloor = this->takeFloor();
    this->setFloor(floor);
    return oldFloor;
}

ObjectTile *StackModel::takeFloor()
{
    ObjectTile *floor = this->refFloor();
    this->removeFloor();
    return floor;
}

void StackModel::removeFloor()
{
    if(this->floor)
    {
        this->floor->unsetPosition();
    }
    this->floor = 0;
    emit this->floorChanged();
    return;
}

void StackModel::deleteFloor()
{
    if(this->floor)
    {
        ObjectTile *floor = this->takeFloor();
        floor->deleteLater();
    }

    return;
}

bool StackModel::hasFloor() const
{
    return this->floor != 0;
}

QPoint StackModel::getSquarePos() const
{
    return this->squarePos;
}

int StackModel::getHeight() const
{
    return this->height;
}

bool StackModel::isEmpty() const
{
    return !this->wall && !this->floor && !this->character &&
            this->itemList.isEmpty();
}

void StackModel::setPosition(int x, int y, int z)
{
    if(x < 0)
    {
        std::cout << "Error in setPosition: x was < 0." << std::endl;
        return;
    }

    if(y < 0)
    {
        std::cout << "Error in setPosition: y was < 0." << std::endl;
        return;
    }

    if(z < 0)
    {
        std::cout << "Error in setPosition: z was < 0." << std::endl;
        return;
    }

    this->squarePos = QPoint(x,y);
    this->height = z;
    return;
}

void StackModel::setItemList(const QList<ObjectItem *> &itemList)
{
    for(int i = itemList.size() - 1; i >= 0; --i)
    {
        this->prependItem(itemList[i]);
    }

    return;
}

void StackModel::setSpecialList(const QList<ObjectSpecial *> &specialList)
{
    for(int i = specialList.size() - 1; i >= 0; --i)
    {
        this->prependSpecial(specialList[i]);
    }

    return;
}

void StackModel::setPathIndication(StackModel::PathIndication pathIndication)
{
    this->pathIndication = pathIndication;
    emit this->pathIndicationChanged();
    return;
}

void StackModel::setCharacter(ObjectCharacter *character)
{
    if(this->hasCharacter())
    {
        qDebug("Cannot set a character on an occupied stack with another character.");
        return;
    }

    this->character = character;

    if(this->character)
    {
        this->character->setPosition(this->squarePos.x(), this->squarePos.y(), this->height);
        this->character->setParent(this);

        if(this->character->getObjectID() == ObjectID::PLAYER)
        {
            emit this->playerSet(this);
        }
    }

    emit this->characterChanged();

    return;
}

void StackModel::setWall(ObjectTile *wall)
{
    if(this->hasWall())
    {
        qDebug("Cannot set a wall on an occupied stack with another wall.");
        return;
    }

    this->wall = wall;

    if(this->wall)
    {
        this->wall->setPosition(this->squarePos.x(), this->squarePos.y(), this->height);
        this->wall->setParent(this);
    }

    emit this->wallChanged();

    return;
}

void StackModel::setFloor(ObjectTile *floor)
{
    if(this->hasFloor())
    {
        qDebug("Cannot set a floor on an occupied stack with another floor.");
        return;
    }

    this->floor = floor;

    if(this->floor)
    {
        this->floor->setPosition(this->squarePos.x(), this->squarePos.y(), this->height);
        this->floor->setParent(this);
        emit this->floorChanged();
    }

    emit this->floorChanged();

    return;
}

StackModel::PathIndication StackModel::getPathIndication() const
{
    return this->pathIndication;
}

ObjectCharacter *StackModel::refCharacter() const
{
    return this->character;
}

QList<ObjectItem *> *StackModel::refItemList()
{
    return &this->itemList;
}

ObjectItem *StackModel::refItem(int i) const
{
    if(i < 0 || i >= this->itemList.size())
    {
        qDebug(QString("Error in refItem(): i was %1").arg(i).toStdString().c_str());
        i = 0;
    }

    if(this->itemList.empty())
    {
        return 0;
    }

    return this->itemList[i];
}

QList<ObjectSpecial *> *StackModel::refSpecialList()
{
    return &this->specialList;
}

ObjectSpecial *StackModel::refSpecial(int i) const
{
    if(i < 0 || i >= this->specialList.size())
    {
        qDebug(QString("Error in refSpecial(): i was %1").arg(i).toStdString().c_str());
        i = 0;
    }

    if(this->specialList.empty())
    {
        return 0;
    }

    return this->specialList[i];
}

ObjectTile *StackModel::refWall() const
{
    return this->wall;
}
ObjectTile *StackModel::refFloor() const
{
    return this->floor;
}

void StackModel::serialize(QDataStream &dataStream) const
{
    dataStream << this->itemList.size();
    for(int i = this->itemList.size()-1; i >= 0; --i)
    {
        dataStream << this->itemList[i]->getObjectID();
        this->itemList[i]->serialize(dataStream);
    }

    dataStream << this->specialList.size();
    for(int i = this->specialList.size()-1; i >= 0; --i)
    {
        dataStream << this->specialList[i]->getObjectID();
        this->specialList[i]->serialize(dataStream);
    }

    dataStream << (this->character != 0);
    if(this->character)
    {
        dataStream << this->character->getObjectID();
        this->refCharacter()->serialize(dataStream);
    }

    dataStream << (this->wall != 0);
    if(this->wall)
    {
        dataStream << this->wall->getObjectID();
        this->refWall()->serialize(dataStream);
    }

    dataStream << (this->floor != 0);
    if(this->floor)
    {
        dataStream << this->floor->getObjectID();
        this->refFloor()->serialize(dataStream);
    }

    return;
}

void StackModel::deserialize(QDataStream &dataStream)
{
    this->deleteAll();

    int itemListSize;
    dataStream >> itemListSize;

    ObjectItem *item;
    int itemID;

    for(int i = 0; i < itemListSize; ++i)
    {
        dataStream >> itemID;
        item = ObjectFromID::objectFrom(ObjectID::ItemID(itemID));
        item->deserialize(dataStream);
        this->prependItem(item);
    }

    int specialListSize;
    dataStream >> specialListSize;

    ObjectSpecial *special;
    int specialID;

    for(int i = 0; i < specialListSize; ++i)
    {
        dataStream >> specialID;
        special = ObjectFromID::objectFrom(ObjectID::SpecialID(specialID));
        special->deserialize(dataStream);
        this->prependSpecial(special);
    }

    bool characterNotNull;
    bool wallNotNull;
    bool floorNotNull;

    dataStream >> characterNotNull;

    if(characterNotNull)
    {
        int characterID;

        dataStream >> characterID;
        ObjectCharacter *character = ObjectFromID::objectFrom(ObjectID::CharacterID(characterID));
        character->deserialize(dataStream);
        this->setCharacter(character);
    }

    dataStream >> wallNotNull;
    if(wallNotNull)
    {
        int wallID;

        dataStream >> wallID;
        ObjectTile *wall = ObjectFromID::objectFrom(ObjectID::TileID(wallID));
        wall->deserialize(dataStream);
        this->setWall(wall);
    }

    dataStream >> floorNotNull;
    if(floorNotNull)
    {
        int floorID;

        dataStream >> floorID;
        ObjectTile *floor = ObjectFromID::objectFrom(ObjectID::TileID(floorID));
        floor->deserialize(dataStream);
        this->setFloor(floor);
    }

    return;
}
