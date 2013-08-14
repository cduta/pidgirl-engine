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

#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <QObject>

#include "Game/Model/PlayerModel.h"
#include "Common/Serialize.h"
#include "MainView/Model/MapModel.h"
#include "Object/Character/Player.h"

namespace PIDGIRL
{
    enum GameType {HOTSEAT = 0, NETWORK, EMAIL};
}

/** \addtogroup Game
  * \{
  * \class GameModel
  *
  * \brief The model representing the game preferences and players.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class GameModel : public QObject, public Serialize
{
    Q_OBJECT

signals:
    void setNewMapSignal(MapModel *); ///< Send a MapModel out to be set.

protected:
    QVariant                requestedData;              ///< Requested Data QVariant. Everything that is not an object, has to be saved here.
    QObject *               requestedObject;            ///< For all the objects which inherit from QObject.

    QMap< unsigned int,
          PlayerModel * >   playerModels;               ///< The players registered in the game. The key is the player's ID.
    bool                    playerChoosesStartLocation; ///< True, if players can choose their own start location.
    unsigned int            playerID;                   ///< Your player ID.

public:
    explicit GameModel(QObject *parent);

    /**
      * @brief Add a new player to the game.
      * @param playerID The playerID to be added.
      * @param playerModel The player model representing the player to be added.
      * @return True, if the player has been added. Otherwise, false.
      */
    virtual bool addNewPlayer(unsigned int playerID, PlayerModel *playerModel) = 0;

    /**
      * @brief Add a preloaded map to the preloaded maps.
      * @param localMapPath Local file path.
      * @param map The preloaded map.
      */
    virtual void addtoPreloadedMaps(const QString &localMapPath, MapModel *map) = 0;

    /**
      * @brief Load a map from a local map path.
      * @param localMapPath The local map path from which to load a map.
      * @return True, if the map has been loaded. Otherwise. false.
      */
    virtual bool loadMap(const QString &localMapPath) = 0;

    /**
      * @brief Load a map directly from a map model.
      * @param map The map model to be loaded.
      * @return True, if the map model has been loaded. Otherwise, false.
      */
    virtual bool loadMap(MapModel *map);

    /**
      * @brief Spawn a given character on a given map.
      * @param playerID The playerID of the player that wants to spawn a character.
      * @param map The map where to spawn the character on.
      * @param newCharacter The character to be spawned with given coordinates already set.
      * @return True, if the character has been spawned. Otherwise, false.
      */
    virtual bool spawnCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &newCharacter);

    /**
     * @brief Update a given character with the information of a new character on a given myp.
     * @param playerID The playerID of the player that wants to update a character.
     * @param map The map where to update the character.
     * @param oldCharacter The old character that will be updated.
     * @param newCharacter The new character with the updated information.
     * @return True, if the character has been updated. Otherwise, false.
     */
    virtual bool updateCharacter(unsigned int playerID, MapModel *map, const ObjectCharacter &oldCharacter, const ObjectCharacter &newCharacter);

    /**
      * @brief Deactivate a player.
      * @param playerID The playerID of which to deactivate the character of.
      */
    virtual void deavtivatePlayer(unsigned int playerID) = 0;

    /**
      * @brief Prepare for the first turn.
      */
    virtual bool firstTurn() = 0;

    /**
      * @brief Prepare for the next turn.
      */
    virtual bool nextTurn() = 0;

    /**
      * @brief Begin the turn.
      */
    virtual bool beginTurn() = 0;

    /**
      * @brief End your turn.
      */
    virtual bool endTurn() = 0;

    /**
      * @brief Delete the current player models.
      */
    void deletePlayerModels();

    /**
      * @brief Change the player ID.
      * @param newID The new ID of the player.
      */
    virtual void changePlayerID(unsigned int newID);

    /**
      * @brief Update this game model with a game model of different type.
      * @param gameModel Game Model with a different type than the one being updated.
      */
    virtual void convertFromDifferentGameModel(GameModel *gameModel);

public:
    // Get-Methods
    virtual PIDGIRL::GameType getGameType() const = 0;
    virtual bool isYourTurn() const = 0;
    bool getPlayerChoosesStartLocation() const;
    unsigned int getPlayerID() const;
    virtual int getCurrentPlayerID() const;
    virtual QMap <unsigned int, PlayerModel *> getPlayerModels() const;
    virtual QMap <QString, MapModel *> getPreloadedMaps() const = 0;

    // Set-Methods
    void setPlayerChoosesStartLocation(bool playerChoosesStartLocation);
    void setPlayerID(unsigned int playerID);
    virtual void setCurrentMap(MapModel *map) = 0;
    void setPlayerModels(const QMap<unsigned int, PlayerModel *> playerModels);
    void setRequestedData(QVariant data);
    void setRequestedObject(QObject *object);

    // Ref-Methods
    virtual MapModel *refPreloadedMap(const QString &localMapPath) const = 0;
    virtual MapModel *refCurrentMap() const = 0;
    virtual PlayerModel *refPlayerModel(unsigned int playerID) const = 0;
    virtual Player *refPlayer(unsigned int playerID) const = 0;

    // Serialize
    virtual void serialize(QDataStream &dataStream) const;
    virtual void deserialize(QDataStream &dataStream);
};

#endif // GAME_MODEL_H
