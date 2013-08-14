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

#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H

#include <QObject>
#include <QString>
#include <QDataStream>

#include "Common/Serialize.h"

/** \addtogroup Game
  * \{
  * \class PlayerModel
  *
  * \brief This model represents the informations about a specific player.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class PlayerModel : public QObject, public Serialize
{
    Q_OBJECT

    unsigned int    ID;                 ///< The ID of the Player.
    bool            activePlayer;       ///< True, if the player is active and playing.
    bool            characterSpawned;   ///< True, if the player has a character spawned.
    QString         playerMapPath;      ///< The map path on which the player is located.

public:
    explicit PlayerModel(unsigned int ID, const QString &localMapPath = QString(""), bool activePlayer = true, QObject *parent = 0);
    explicit PlayerModel(QObject *parent = 0);

private:
    void init(unsigned int ID = 0, const QString &localMapPath = QString(""), bool activePlayer = true, bool characterSpawned = false);

public:

    // Get-Methods
    unsigned int getID() const;
    QString getLocalMapPath() const;
    bool isActivePlayer() const;
    bool hasCharacterSpawned() const;

    // Set-Methods
    void setPlayerMapPath(const QString &playerMapPath);
    void setActivePlayer(bool activePlayer);
    void setCharacterSpwawned(bool characterSpawned);

public:
    // Serialize
    virtual void serialize(QIODevice *device) const;
    void serialize(QDataStream *dataStream) const;
    virtual void deserialize(QIODevice *device);
    void deserialize(QDataStream *dataStream);
};

#endif // PLAYER_MODEL_H
