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

#ifndef SERVER_GAME_MODEL_H
#define SERVER_GAME_MODEL_H

#include "Game/Model/LocalGameModel.h"

/** \addtogroup Game
  * \{
  * \class ServerGameModel
  *
  * \brief The model representing a game that is also a server.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ServerGameModel : public LocalGameModel
{
    Q_OBJECT

    unsigned int currentPlayerID;

public:
    ServerGameModel(Processor *processor, QObject *parent);

private:
    void nextCurrentPlayer();

public:
    virtual bool nextTurn();
    virtual bool beginTurn();
    virtual bool firstTurn();
    virtual bool endTurn();

    virtual bool spawnCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &newCharacter);
    virtual bool updateCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &oldCharacter, const ObjectCharacter &newCharacter);
    virtual void deavtivatePlayer(unsigned int playerID);

    virtual void convertFromDifferentGameModel(GameModel *gameModel);

    // Get-Methods
    virtual bool isYourTurn() const;
    virtual PIDGIRL::GameType getGameType() const;
    virtual int getCurrentPlayerID() const;

    // Ref-Methods
    virtual MapModel *refCurrentMap() const;

private:
    // Set-Methods
    void setCurrentPlayerID(unsigned int currentPlayerID);

public:

    // Serialize
    virtual void serialize(QIODevice *device) const;
    virtual void deserialize(QIODevice *device);
};

#endif // SERVER_GAME_MODEL_H
