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

#ifndef SPAWN_GAME_OBJECT_H
#define SPAWN_GAME_OBJECT_H

#include "Command/Backend/Game/GameCommand.h"
#include "Object/ObjectBase.h"
#include "MainView/Model/StackModel.h"

/** \addtogroup Commands
  * \{
  * \class SpawnGameObject
  *
  * \brief Generic Command to spawn an object.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class SpawnGameObject : public GameCommand
{
    Q_OBJECT
private:
    ObjectBase *spawnableObject;    ///< Object to be spawned.
    StackModel *stackModel;         ///< The stack where to spawn the object.

public:
    SpawnGameObject(ObjectBase *spawnableObject, StackModel *stackModel, QObject *parent = 0);

    virtual bool execute();
};

#endif // SPAWN_GAME_OBJECT_H
