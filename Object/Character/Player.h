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

#ifndef PLAYER_H
#define PLAYER_H

#include "Object/ObjectCharacter.h"

/** \addtogroup Object
  * \{
  * \class Player
  *
  * \brief The player object representing the player.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class Player : public ObjectCharacter
{
    Q_OBJECT

public:
    explicit Player(const QString &name = tr("Hero"), const QString &description = tr("Just another hero."), QObject *parent = 0);
    explicit Player(const Player &player);

protected:
    void initPlayer();

public:
    virtual Player *copy() const;
    virtual void update(const ObjectBase &object);

    virtual QWidget *createInformationWidget(QWidget *parent) const;

    // Get-Methods
    virtual ObjectID::CharacterID getObjectID() const;
    virtual QMap<QString, BaseCommand *> getCommandList() const;

    // Serialize
    virtual void serialize(QDataStream &dataStream) const;
    virtual void serialize(QIODevice *device) const;
    virtual void deserialize(QDataStream &dataStream);
    virtual void deserialize(QIODevice *device);
};

#endif // PLAYER_H
