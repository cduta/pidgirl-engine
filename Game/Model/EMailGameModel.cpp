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

#include "EMailGameModel.h"

#include <QMessageBox>

#include "Command/Backend/Game/Ingame/SaveEMailGame.h"
#include "Command/Backend/Game/Ingame/YourTurnInformation.h"
#include "Command/Backend/Game/Ingame/FirstTurn.h"
#include "Command/Backend/Common/Quit.h"

EMailGameModel::EMailGameModel(Processor *processor, QObject *parent)
    : LocalGameModel(processor, parent)
{
    this->turnCount = 0;
}

void EMailGameModel::nextPlayerID()
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
        return;
    }

    this->setPlayerID(nextPlayerID);
    return;
}

bool EMailGameModel::nextTurn()
{
    MailGameInfo *mailGameInfo = this->mailGameInfos.value(this->playerID, 0);
    PlayerModel *oldPlayerModel = this->playerModels.value(this->playerID, 0);

    if(!oldPlayerModel->isActivePlayer())
    {
        this->mailGameInfos.remove(oldPlayerModel->getID());
    }

    this->turnCount++;
    this->nextPlayerID();

    PlayerModel *playerModel = this->playerModels.value(this->playerID, 0);

    if(!playerModel)
    {
        qDebug("The player model of the next player could not be found.\nClosing game...");
        return false;
    }

    if(playerModel->hasCharacterSpawned())
    {
        if(!this->processor->execute(new SaveEMailGame(mailGameInfo,
                                                       this->refPlayer(this->playerID)->getObjectName(),
                                                       this->turnCount)))
        {
            this->processor->execute(new Quit());
            return false;
        }
    }
    else
    {
        if(!this->processor->execute(new SaveEMailGame(mailGameInfo,
                                                       "",
                                                       this->turnCount)))
        {
            this->processor->execute(new Quit());
            return false;
        }
    }

    this->processor->execute(new Quit());
    return true;
}

bool EMailGameModel::beginTurn()
{
    this->processor->execute(new YourTurnInformation());

    if(this->refPlayerModel(this->playerID)->hasCharacterSpawned())
    {
        if(!this->loadMap(this->playerModels[this->playerID]->getLocalMapPath()))
        {
            qDebug() << "The current map could not be loaded for player with ID" << this->playerID << "\nClosing the game.";
            this->processor->execute(new Quit());
            return false;
        }
    }
    else
    {
        if(!this->processor->execute(new FirstTurn()))
        {
            this->processor->execute(new Quit());
            return false;
        }

        MailGameInfo *newMailGameInfo = new MailGameInfo(this);
        this->mailGameInfos.insert(this->playerID, newMailGameInfo);
    }

    return true;
}

bool EMailGameModel::firstTurn()
{
    return this->beginTurn();
}

bool EMailGameModel::endTurn()
{
    return this->nextTurn();
}

void EMailGameModel::convertFromDifferentGameModel(GameModel *gameModel)
{
    Q_UNUSED(gameModel);
    qDebug("Cannot convert any Game Model to an EMail Game Model.");
    return;
}

PIDGIRL::GameType EMailGameModel::getGameType() const
{
    return PIDGIRL::EMAIL;
}

unsigned int EMailGameModel::getTurnCount() const
{
    return this->turnCount;
}

void EMailGameModel::setTurnCount(unsigned int turnCount)
{
    this->turnCount = turnCount;
    return;
}

MailGameInfo *EMailGameModel::refMailGameInfo(unsigned int playerID)
{
    return this->mailGameInfos.value(playerID, 0);
}

void EMailGameModel::serialize(QIODevice *device) const
{
    QDataStream stream(device);

    this->serialize(stream);
    return;
}

void EMailGameModel::serialize(QDataStream &stream) const
{
    QList<unsigned int> keyList = mailGameInfos.keys();
    QList<MailGameInfo *> mailGameInfoList = mailGameInfos.values();

    stream << mailGameInfoList.size();

    for(int i = 0; i < mailGameInfoList.size(); ++i)
    {
        stream << keyList[i];
        mailGameInfoList[i]->serialize(stream);
    }

    stream << this->turnCount;

    LocalGameModel::serialize(stream);
    return;
}

void EMailGameModel::deserialize(QIODevice *device)
{
    QDataStream stream(device);
    this->deserialize(stream);

    return;
}

void EMailGameModel::deserialize(QDataStream &stream)
{
    int mailGameInfoSize;
    stream >> mailGameInfoSize;

    unsigned int key;
    MailGameInfo *mailGameInfo;

    for(int i = 0; i < mailGameInfoSize; ++i)
    {
        mailGameInfo = new MailGameInfo(this);
        stream >> key;
        mailGameInfo->deserialize(stream);
        this->mailGameInfos.insert(key, mailGameInfo);
    }

    unsigned int turnCount;
    stream >> turnCount;
    this->setTurnCount(turnCount);

    LocalGameModel::deserialize(stream);

    return;
}
