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

#include <iostream>

#include "Object/ObjectBase.h"

#include <climits>

ObjectBase::ObjectBase(const ObjectBase& objectBase) :
    QObject(objectBase.parent())
{
    this->initObjectBase(objectBase.getObjectName(), objectBase.getDescription(), objectBase.getUsedImageIndex(), objectBase.getIsVisible());
    this->setPosition(objectBase.getX(), objectBase.getY(), objectBase.getZ());
    this->setSpawnID(objectBase.getSpawnID());
    this->loadImages(objectBase.getImagePathList());
}

ObjectBase::ObjectBase(const QString &name, const QString &description, bool isVisible, QObject *parent) :
    QObject(parent)
{
    this->initObjectBase(name, description, -1, isVisible);
}

ObjectBase::ObjectBase(const QString &name, const QString &description, const QString &imagePath, bool isVisible, QObject *parent) :
    QObject(parent)
{
    this->initObjectBase(name, description, 0, isVisible);
    this->appendImage(imagePath);
}

ObjectBase::ObjectBase()
{
    this->initObjectBase();
}

void ObjectBase::initObjectBase(const QString &name, const QString &description, int usedImageIndex, bool isVisible)
{
    this->unsetPosition();
    this->setObjectName(name);
    this->setDescription(description);
    this->spawnID = UINT_MAX;
    this->setUsedImageIndex(usedImageIndex);
    this->setIsVisible(isVisible);

    return;
}

void ObjectBase::initObjectBase(const QVector<QString> &imagePathList, const QString &name, const QString &description, int usedImageIndex, bool isVisible)
{
    this->initObjectBase(name, description, usedImageIndex, isVisible);
    this->loadImages(imagePathList);
}

void ObjectBase::clearImageList()
{
    this->imageList.clear();
    this->usedImageIndex = -1;

    return;
}

void ObjectBase::appendImage(const QString &imagePath)
{
    this->imageList.append(ObjectImage(imagePath));
    this->usedImageIndex = 0;

    return;
}

void ObjectBase::appendImages(const QVector<QString> &imagePathList)
{
    for(int i = 0; i < imagePathList.size(); ++i)
    {
        this->appendImage(imagePathList[i]);
    }

    this->usedImageIndex = 0;

    return;
}

void ObjectBase::loadImage(const QString &imagePath)
{
    this->clearImageList();
    this->appendImage(imagePath);

    return;
}

void ObjectBase::loadImages(const QVector<QString> &imagePathList)
{
    this->clearImageList();
    this->appendImages(imagePathList);

    return;
}

void ObjectBase::toggleVisibility()
{
    this->isVisible = !this->isVisible;
    return;
}

bool ObjectBase::isSet() const
{
    return this->x >= 0 && this->y >= 0 && this->z >= 0;
}

void ObjectBase::unsetPosition()
{
    this->x = -1;
    this->y = -1;
    this->z = -1;
    return;
}

void ObjectBase::updateBase(const ObjectBase &object)
{
    this->setObjectName(object.getObjectName());
    this->setDescription(object.getDescription());
    this->setPosition(object.getX(), object.getY(), object.getZ());
    this->loadImages(object.getImagePathList());
    this->setIsVisible(object.getIsVisible());

    return;
}

QVector<QString> ObjectBase::getImagePathList() const
{
    QVector<QString> imagePathList;

    for(int i = 0; i < this->imageList.size(); ++i)
    {
        imagePathList.append(this->imageList[i].getPath());
    }

    return imagePathList;
}

QString ObjectBase::getCurrentImagePath() const
{
    if(this->usedImageIndex < 0 || this->usedImageIndex > this->imageList.size())
    {
        qDebug("Loading the current image path failed. The current image was not valid.");
        return QString();
    }

    return this->imageList[this->usedImageIndex].getPath();
}

int ObjectBase::getUsedImageIndex() const
{
    return this->usedImageIndex;
}

QString ObjectBase::getObjectName() const
{
    return this->objectName();
}

bool ObjectBase::getIsVisible() const
{
    return this->isVisible;
}

unsigned int ObjectBase::getSpawnID() const
{
    return this->spawnID;
}

int ObjectBase::getX() const
{
    return this->x;
}

int ObjectBase::getY() const
{
    return this->y;
}

int ObjectBase::getZ() const
{
    return this->z;
}

QString ObjectBase::getDescription() const
{
    return this->description;
}

void ObjectBase::setUsedImageIndex(int usedImageIndex)
{
    this->usedImageIndex = usedImageIndex;
    return;
}

void ObjectBase::setIsVisible(bool isVisible)
{
    this->isVisible = isVisible;
    return;
}

void ObjectBase::setSpawnID(unsigned int spawnID)
{
    this->spawnID = spawnID;
    //qDebug(QString("%1 got SpawnID %2").arg(this->objectName(), QString::number(this->spawnID)).toStdString().c_str());
    return;
}

void ObjectBase::setPosition(int x, int y, int z)
{
    if((x < 0 && y >= 0 && z >= 0) ||
       (x >= 0 && y < 0 && z >= 0) ||
       (x >= 0 && y >= 0 && z < 0))
    {
        qDebug(QString("Given position is invalid: (%1,%2,%3). Unsetting position.").arg(QString::number(x), QString::number(y), QString::number(z)).toStdString().c_str());
        this->unsetPosition();
        return;
    }

    this->x = x;
    this->y = y;
    this->z = z;

    return;
}

void ObjectBase::setDescription(const QString &description)
{
    this->description = description;
    return;
}

QImage *ObjectBase::refImage()
{
    return this->refImage(this->usedImageIndex);
}

QImage *ObjectBase::refImage(int index)
{
    // Will return 0, if there is an invalid index given.
    if(index < 0 || index >= this->imageList.size())
    {
        std::cout << "Couldn't reference the image that's used." << std::endl;
        std::cout << "    Index was: " << index << std::endl;
        std::cout << "    Size was: " << this->imageList.size() << std::endl;
        return 0;
    }

    if(!this->isVisible)
    {
        return 0;
    }

    return &this->imageList[index];
}

void ObjectBase::serialize(QDataStream &dataStream) const
{
    dataStream << this->getObjectName();
    dataStream << this->description;

    dataStream << this->getImagePathList();
    dataStream << this->getIsVisible();

    dataStream << this->spawnID;

    dataStream << this->x;
    dataStream << this->y;
    dataStream << this->z;

    return;
}

void ObjectBase::deserialize(QDataStream &dataStream)
{
    QString name;
    dataStream >> name;
    this->setObjectName(name);

    QString description;
    dataStream >> description;
    this->setDescription(description);

    QVector<QString> imagePathList;
    dataStream >> imagePathList;
    this->loadImages(imagePathList);

    bool isVisible;
    dataStream >> isVisible;
    this->setIsVisible(isVisible);

    unsigned int spawnID;
    dataStream >> spawnID;
    this->setSpawnID(spawnID);

    int x,y,z;
    dataStream >> x;
    dataStream >> y;
    dataStream >> z;
    this->setPosition(x,y,z);

    return;
}
