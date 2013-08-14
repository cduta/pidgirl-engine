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

#include "Player.h"

#include <QGridLayout>
#include <QLabel>

#include "Command/Backend/Object/ShowDescription.h"

Player::Player(const QString &name, const QString &description, QObject *parent)
    : ObjectCharacter(name, description, ":/objects/characters/hero", true, parent)
{
}

Player::Player(const Player &player)
    : ObjectCharacter(player)
{
    this->initPlayer();
}

void Player::initPlayer()
{
    return;
}

Player *Player::copy() const
{
    return new Player(*this);
}

void Player::update(const ObjectBase &object)
{
    if(this->getType() != object.getType() || this->getObjectIDNumber() != object.getObjectIDNumber())
    {
        qDebug("Object has not been updatet since the given object was not of that type.");
        return;
    }

    const Player &player = (const Player &) object;

    this->updateCharacter(player);
    return;
}

QWidget *Player::createInformationWidget(QWidget *parent) const
{
    QWidget *widget = new QWidget(parent);
    QGridLayout *layout = new QGridLayout(widget);
    QLabel *name = new QLabel(QString("Name: <b>%1</b>").arg(this->getObjectName()), widget);
    name->setTextFormat(Qt::RichText);
    QLabel *description = new QLabel(this->getDescription(), widget);

    layout->addWidget(name,0,0);
    layout->addWidget(description, 1,0);

    widget->setLayout(layout);
    return widget;
}

ObjectID::CharacterID Player::getObjectID() const
{
    return ObjectID::PLAYER;
}

QMap<QString, BaseCommand *> Player::getCommandList() const
{
    QMap<QString, BaseCommand *> map;

    map.insert(tr("Description..."), new ShowDescription(this));

    return map;
}

void Player::serialize(QDataStream &dataStream) const
{
    this->ObjectCharacter::serialize(dataStream);
    return;
}

void Player::serialize(QIODevice *device) const
{
    QDataStream stream(device);
    this->serialize(stream);
    return;
}

void Player::deserialize(QDataStream &dataStream)
{
    this->ObjectCharacter::deserialize(dataStream);
    return;
}

void Player::deserialize(QIODevice *device)
{
    QDataStream stream(device);
    this->deserialize(stream);
    return;
}


