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

#include "ClientSocket.h"

ClientSocket::ClientSocket(unsigned int playerID, QTcpSocket *socket, QObject *parent) :
    QObject(parent), playerID(playerID)
{
    this->socket = socket;
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(gotReadyRead()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(gotDisconnected()));
}

ClientSocket::~ClientSocket()
{
}

unsigned int ClientSocket::getPlayerID() const
{
    return playerID;
}

void ClientSocket::setPlayerID(unsigned int playerID)
{
    this->playerID = playerID;
    qDebug() << "Client changed playerID to" << this->playerID;
    return;
}

QTcpSocket *ClientSocket::refSocket() const
{
    return socket;
}

void ClientSocket::gotReadyRead()
{
    emit this->readyRead(this);
    return;
}

void ClientSocket::gotDisconnected()
{
    emit this->disconnected(this);
    return;
}
