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

#ifndef LOCAL_GAME_MODEL_H
#define LOCAL_GAME_MODEL_H

#include <QMap>

#include "Command/Processor.h"
#include "Game/Model/GameModel.h"

/** \addtogroup Game
  * \{
  * \class LocalGameModel
  *
  * \brief The model representing a local game where all the information is held locally.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class LocalGameModel : public GameModel
{
    Q_OBJECT

protected:
    Processor *                 processor;
    QMap< QString, MapModel *>  preloadedMaps;  ///< The map of preloaded maps. The key is the local map path for the map.

public:
    LocalGameModel(Processor *processor, QObject *parent);

    virtual bool addNewPlayer(unsigned int playerID, PlayerModel *playerModel);
    virtual void addtoPreloadedMaps(const QString &localMapPath, MapModel *map);
    virtual bool loadMap(const QString &localMapPath);
    virtual void deavtivatePlayer(unsigned int playerID);

    virtual void convertFromDifferentGameModel(GameModel *gameModel);

    // Get-Methods
    virtual bool isYourTurn() const;
    virtual QMap<QString, MapModel *> getPreloadedMaps() const;

    // Set-Methods
    virtual void setCurrentMap(MapModel *map);

    // Ref-Methods
    virtual PlayerModel *refPlayerModel(unsigned int playerID) const;
    virtual MapModel *refCurrentMap() const;
    virtual MapModel *refPreloadedMap(const QString &localMapPath) const;
    virtual Player *refPlayer(unsigned int playerID) const;

    // Serialize
    virtual void serialize(QDataStream &dataStream) const;
    virtual void deserialize(QDataStream &dataStream);
};

#endif // LOCAL_GAME_MODEL_H
