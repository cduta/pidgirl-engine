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

#ifndef CLIENT_GAME_MODEL_H
#define CLIENT_GAME_MODEL_H

#include <QVariant>

#include "Game/Model/GameModel.h"
#include "Command/Processor.h"
#include "Network/ClientModel.h"

/** \addtogroup Game
  * \{
  * \class ClientGameModel
  *
  * \brief The model representing a game ran as a client where most information is accessible remotely.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ClientGameModel : public GameModel
{
    Q_OBJECT

    Processor * processor;

    MapModel *  currentMap; ///< The current map loaded.
    bool        yourTurn;   ///< True, if it is your turn.

public:
    ClientGameModel(Processor *processor, QObject *parent);

    virtual bool addNewPlayer(unsigned int playerID, PlayerModel *playerModel);

    virtual bool nextTurn();
    virtual bool beginTurn();
    virtual bool firstTurn();
    virtual bool endTurn();

    virtual void deavtivatePlayer(unsigned int playerID);

    virtual void addtoPreloadedMaps(const QString &localMapPath, MapModel *map);
    virtual bool loadMap(const QString &localMapPath);
    virtual bool loadMap(MapModel *map);
    virtual bool spawnCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &newCharacter);
    virtual bool updateCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &oldCharacter, const ObjectCharacter &newCharacter);

    virtual void changePlayerID(unsigned int newID);

    virtual void convertFromDifferentGameModel(GameModel *gameModel);
private:
    // Set-Methods
    void setYourTurn(bool yourTurn);
    virtual void setCurrentMap(MapModel *map);

public:
    // Get-Methods
    virtual PIDGIRL::GameType getGameType() const;
    virtual bool isYourTurn() const;
    virtual QMap <unsigned int, PlayerModel *> getPlayerModels() const;
    virtual QMap<QString, MapModel *> getPreloadedMaps() const;

    // Ref-Methods
    virtual PlayerModel *refPlayerModel(unsigned int playerID) const;
    virtual MapModel *refPreloadedMap(const QString &localMapPath) const;
    virtual MapModel *refCurrentMap() const;
    virtual Player *refPlayer(unsigned int playerID) const;

public:
    // Serialize
    virtual void serialize(QIODevice *device) const;
    virtual void deserialize(QIODevice *device);
};

#endif // CLIENT_GAME_MODEL_H
