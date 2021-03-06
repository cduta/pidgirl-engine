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

#include "ReceiveUpdateCharacterFrom.h"

#include "Object/ObjectFromID.h"

ReceiveUpdateCharacterFrom::ReceiveUpdateCharacterFrom(unsigned int senderID, QObject *parent)
    : NetworkCommand(parent), senderID(senderID)
{
    this->setObjectName("ReceiveMoveCharacterFrom");
}

bool ReceiveUpdateCharacterFrom::execute()
{
    unsigned int oldCharacterID;
    unsigned int newCharacterID;

    this->networkModel->receiveData(oldCharacterID, this->senderID);
    ObjectCharacter *oldCharacter = ObjectFromID::objectFrom(ObjectID::CharacterID(oldCharacterID), this);
    this->networkModel->receiveData(*oldCharacter, this->senderID);

    this->networkModel->receiveData(newCharacterID, this->senderID);
    ObjectCharacter *newCharacter = ObjectFromID::objectFrom(ObjectID::CharacterID(newCharacterID), this);
    this->networkModel->receiveData(*newCharacter, this->senderID);

    return this->gameModel->updateCharacter(this->senderID, this->gameModel->refCurrentMap(), *oldCharacter, *newCharacter);
}
