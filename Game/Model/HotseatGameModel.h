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

#ifndef HOTSEAT_GAME_MODEL_H
#define HOTSEAT_GAME_MODEL_H

#include "Game/Model/LocalGameModel.h"

/** \addtogroup Game
  * \{
  * \class HotseatGameModel
  *
  * \brief The model representing a hotseat game with one or more players.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class HotseatGameModel : public LocalGameModel
{
    Q_OBJECT

public:
    HotseatGameModel(Processor *processor, QObject *parent);

private:
    bool nextPlayerID();

public:
    virtual bool nextTurn();
    virtual bool beginTurn();
    virtual bool firstTurn();
    virtual bool endTurn();

    virtual void changePlayerID(unsigned int newID);

    virtual void convertFromDifferentGameModel(GameModel *gameModel);

    // Get-Methods
    virtual PIDGIRL::GameType getGameType() const;

    // Serialize
    virtual void serialize(QIODevice *device) const;
    virtual void deserialize(QIODevice *device);
};

#endif // HOTSEAT_GAME_MODEL_H
