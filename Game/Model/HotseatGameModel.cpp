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

#include "HotseatGameModel.h"

#include <QMessageBox>

#include "Command/Backend/Game/Ingame/FirstTurn.h"
#include "Command/Backend/Game/Ingame/YourTurnInformation.h"
#include "Command/Backend/Common/Quit.h"

#include "Game/Model/ServerGameModel.h"

HotseatGameModel::HotseatGameModel(Processor *processor, QObject *parent)
    : LocalGameModel(processor, parent)
{
}

bool HotseatGameModel::nextPlayerID()
{
    unsigned int oldPlayerID = this->playerID;
    QList<unsigned int> keys = this->playerModels.keys();
    unsigned int nextPlayerID;
    int currentIndex = keys.indexOf(this->playerID);

    do
    {
        currentIndex++;

        if(currentIndex == keys.size())
        {
            currentIndex = 0;
        }

        nextPlayerID = keys[currentIndex];
    }
    while(!this->playerModels[nextPlayerID]->isActivePlayer() && nextPlayerID != oldPlayerID);

    if(nextPlayerID == oldPlayerID && !this->playerModels[nextPlayerID]->isActivePlayer())
    {
        qDebug("No more active players around. Going to quit the game...");

        QMessageBox::information(0,
                                 tr("No more players available..."),
                                 tr("No more players are available, therefore I'll quit the game."),
                                 QMessageBox::Ok);

        this->processor->execute(new Quit());
        return false;
    }

    this->setPlayerID(nextPlayerID);
    return true;
}

bool HotseatGameModel::nextTurn()
{
    if(!this->nextPlayerID())
    {
        return false;
    }

    return this->beginTurn();
}

bool HotseatGameModel::beginTurn()
{
    this->processor->execute(new YourTurnInformation());

    if(!this->refPlayerModel(this->playerID)->hasCharacterSpawned())
    {
        if(!this->processor->execute(new FirstTurn()))
        {
            this->refPlayerModel(this->playerID)->setActivePlayer(false);
            this->endTurn();
        }
    }
    else
    {
        if(!this->loadMap(this->playerModels[this->playerID]->getLocalMapPath()))
        {
            // TODO: Remove the playerModel with current playerID.
            qDebug() << "The current map could not be loaded for player with ID" << this->playerID << "\nClosing the game.";
            this->processor->execute(new Quit());
            return false;
        }
    }
    return true;
}

bool HotseatGameModel::firstTurn()
{
    return this->beginTurn();
}

bool HotseatGameModel::endTurn()
{
    return this->nextTurn();
}

void HotseatGameModel::changePlayerID(unsigned int newID)
{
    this->playerModels[newID]->setActivePlayer(true);
    this->playerModels[this->playerID]->setActivePlayer(false);
    this->GameModel::changePlayerID(newID);
    return;
}

void HotseatGameModel::convertFromDifferentGameModel(GameModel *gameModel)
{
    if(!gameModel)
    {
        qDebug() << "Given Game Model was 0.";
        return;
    }

    if(gameModel->getGameType() != PIDGIRL::NETWORK)
    {
        qDebug() << "Not a compatible game model used to update. Type was" << gameModel->getGameType();
        return;
    }

    this->LocalGameModel::convertFromDifferentGameModel(gameModel);
    this->setPlayerID(gameModel->getCurrentPlayerID());

    return;
}

PIDGIRL::GameType HotseatGameModel::getGameType() const
{
    return PIDGIRL::HOTSEAT;
}

void HotseatGameModel::serialize(QIODevice *device) const
{
    QDataStream dataStream(device);

    LocalGameModel::serialize(dataStream);
}

void HotseatGameModel::deserialize(QIODevice *device)
{
    QDataStream dataStream(device);

    LocalGameModel::deserialize(dataStream);
}
