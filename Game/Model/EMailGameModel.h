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

#ifndef EMAIL_GAME_MODEL_H
#define EMAIL_GAME_MODEL_H

#include "Game/Model/LocalGameModel.h"
#include "Game/Model/MailGameInfo.h"

/** \addtogroup Game
  * \{
  * \class EMailGameModel
  *
  * \brief The model representing an E-Mail game.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class EMailGameModel : public LocalGameModel
{
    Q_OBJECT
    QMap<unsigned int, MailGameInfo *> mailGameInfos;
    unsigned int turnCount;

public:
    EMailGameModel(Processor *processor, QObject *parent);

private:
    void nextPlayerID();

public:
    virtual bool nextTurn();
    virtual bool beginTurn();
    virtual bool firstTurn();
    virtual bool endTurn();

    virtual void convertFromDifferentGameModel(GameModel *gameModel);
public:
    // Get-Methods
    virtual PIDGIRL::GameType getGameType() const;
    unsigned int getTurnCount() const;

    // Set-Methods
    void setTurnCount(unsigned int turnCount);

    // Ref-Methods
    MailGameInfo *refMailGameInfo(unsigned int playerID);

    // Serialize
    virtual void serialize(QIODevice *device) const;
    void serialize(QDataStream &stream) const;
    virtual void deserialize(QIODevice *device);
    void deserialize(QDataStream &stream);
};

#endif // EMAIL_GAME_MODEL_H
