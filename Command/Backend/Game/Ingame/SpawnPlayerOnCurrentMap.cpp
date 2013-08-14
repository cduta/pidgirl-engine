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

#include "SpawnPlayerOnCurrentMap.h"

#include <QMessageBox>

#include "Object/ObjectID.h"

SpawnPlayerOnCurrentMap::SpawnPlayerOnCurrentMap(const QString &playerName, QObject *parent)
    : GameCommand(parent), playerName(playerName)
{
    this->setObjectName("SpawnPlayerOnCurrentMap");
}

bool SpawnPlayerOnCurrentMap::execute()
{
    StackModel *startStack = this->mapModel->refStartPositionStack();

    if(!startStack)
    {
        QMessageBox::information(0,
                                 tr("Spawning the character has failed..."),
                                 tr("The character couldn't be spwaned on a map because none was slected."),
                                 QMessageBox::Ok);
        return false;
    }

    Player newPlayerCharacter(this->playerName, tr("The Player Character"), this);
    newPlayerCharacter.setSpawnID(this->gameModel->getPlayerID());
    newPlayerCharacter.setPosition(startStack->getSquarePos().x(), startStack->getSquarePos().y(), startStack->getHeight());

    return this->gameModel->spawnCharacter(this->gameModel->getPlayerID(), this->mapModel, newPlayerCharacter);
}
