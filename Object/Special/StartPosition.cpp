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

#include "StartPosition.h"

#include <QGridLayout>
#include <QLabel>

#include "Command/Backend/Object/ShowDescription.h"

StartPosition::StartPosition(QObject *parent)
    : ObjectSpecial(1, false,
                    tr("Start Position"),
                    tr("This indicates where a player can start from."),
                    ":/objects/characters/hero", true, parent)
{
}

StartPosition::StartPosition(const StartPosition &startPosition)
    : ObjectSpecial(startPosition)
{
}

QWidget *StartPosition::createInformationWidget(QWidget *parent) const
{
    QWidget *widget = new QWidget(parent);
    QGridLayout *layout = new QGridLayout(widget);
    QLabel *description = new QLabel(this->getDescription(), widget);

    layout->addWidget(description, 1,0);

    widget->setLayout(layout);
    return widget;
}

ObjectSpecial *StartPosition::copy() const
{
    return new StartPosition(*this);
}

void StartPosition::update(const ObjectBase &object)
{
    if(this->getType() != object.getType() || this->getObjectIDNumber() != object.getObjectIDNumber())
    {
        qDebug("Object has not been updatet since the given object was not of that type.");
        return;
    }

    const StartPosition &startPosition = (const StartPosition &) object;

    this->updateSpecial(startPosition);
    return;
}

ObjectID::SpecialID StartPosition::getObjectID() const
{
    return ObjectID::START_POSITION;
}

QMap<QString, BaseCommand *> StartPosition::getCommandList() const
{
    QMap<QString, BaseCommand *>map;

    map.insert(tr("Description..."), new ShowDescription(this));

    return map;
}

void StartPosition::serialize(QDataStream &dataStream) const
{
    ObjectSpecial::serialize(dataStream);
    return;
}

void StartPosition::serialize(QIODevice *device) const
{
    QDataStream stream(device);
    this->serialize(stream);
    return;
}

void StartPosition::deserialize(QDataStream &dataStream)
{
    ObjectSpecial::deserialize(dataStream);
    return;
}

void StartPosition::deserialize(QIODevice *device)
{
    QDataStream stream(device);
    this->deserialize(stream);
    return;
}

