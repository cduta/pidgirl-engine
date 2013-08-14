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

#include "BrickWall.h"

#include <QGridLayout>
#include <QLabel>

#include "Command/Backend/Object/ShowDescription.h"

BrickWall::BrickWall(QObject *parent)
    : ObjectTile(tr("Brick Wall"),
                 tr("A very sturdy wall of bricks."),
                 ObjectTile::WALL, ":/objects/walls/brick_wall", true, parent)
{
}

BrickWall::BrickWall(const BrickWall &brickWall)
    : ObjectTile(brickWall)
{
}

QWidget *BrickWall::createInformationWidget(QWidget *parent) const
{
    QWidget *widget = new QWidget(parent);
    QGridLayout *layout = new QGridLayout(widget);
    QLabel *description = new QLabel(this->getDescription(), widget);

    layout->addWidget(description, 1,0);

    widget->setLayout(layout);
    return widget;
}

ObjectTile *BrickWall::copy() const
{
    return new BrickWall(*this);
}

void BrickWall::update(const ObjectBase &object)
{
    if(this->getType() != object.getType() || this->getObjectIDNumber() != object.getObjectIDNumber())
    {
        qDebug("Object has not been updatet since the given object was not of that type.");
        return;
    }

    const BrickWall &brickWall = (const BrickWall &) object;

    this->updateTile(brickWall);
    return;
}

ObjectID::TileID BrickWall::getObjectID() const
{
    return ObjectID::BRICK_WALL;
}

QMap<QString, BaseCommand *> BrickWall::getCommandList() const
{
    QMap<QString, BaseCommand *> map;

    map.insert(tr("Description..."), new ShowDescription(this));

    return map;
}

void BrickWall::serialize(QDataStream &dataStream) const
{
    ObjectTile::serialize(dataStream);
    return;
}

void BrickWall::serialize(QIODevice *device) const
{
    QDataStream stream(device);
    this->serialize(stream);
    return;
}

void BrickWall::deserialize(QDataStream &dataStream)
{
    ObjectTile::deserialize(dataStream);
    return;
}

void BrickWall::deserialize(QIODevice *device)
{
    QDataStream stream(device);
    this->deserialize(stream);
    return;
}
