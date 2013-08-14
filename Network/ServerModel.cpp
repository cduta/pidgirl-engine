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

#include "ServerModel.h"

#include <QMessageBox>
#include <QList>
#include <QDataStream>
#include <QBuffer>

#include <climits>

#include "Common/Common.h"

#include "Command/Backend/Network/Server/ClientDisconnected.h"
#include "Command/Backend/Network/Server/SendInitialPlayerInformation.h"
#include "Command/Backend/Network/Server/ReplyToRequestForMap.h"
#include "Command/Backend/Network/Server/ReplyToRequestForPlayer.h"
#include "Command/Backend/Network/Server/ReplyToRequestForPlayerModels.h"
#include "Command/Backend/Network/Server/ReceiveChangePlayerID.h"
#include "Command/Backend/Network/ReceiveSpawnCharacterFrom.h"
#include "Command/Backend/Network/ReceiveUpdateCharacterFrom.h"
#include "Command/Backend/Game/Ingame/NextTurn.h"

ServerModel::ServerModel(int port, WorldModel *worldModel, Processor *processor)
    : NetworkModel(port, processor)
{
    this->processor = processor;
    this->worldModel = worldModel;

    connect(&this->server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(&this->server, SIGNAL(acceptError(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));
}

ServerModel::~ServerModel()
{
    this->server.close();
    QList<unsigned int> keyList = this->clients.keys();

    for(int i = 0; i < keyList.size(); ++i)
    {
        this->clients[keyList[i]]->refSocket()->disconnectFromHost();
    }
}

bool ServerModel::isClient()
{
    return false;
}

bool ServerModel::isServer()
{
    return true;
}

QVector<QString> ServerModel::getConnectionList()
{
    QVector<QString> result;

    QList<ClientSocket *> socketList = this->clients.values();

    for(int i = 0; i < socketList.size(); ++i)
    {
        result.append(QString("Client: %1 - PlayerID: %2")
                      .arg(socketList[i]->refSocket()->peerAddress().toString(), QString::number(socketList[i]->getPlayerID())));
    }

    return result;
}

QVector<unsigned int> ServerModel::getConnectedPlayerIDs()
{
    QVector<unsigned int> result;

    QList<ClientSocket *> socketList = this->clients.values();

    for(int i = 0; i < socketList.size(); ++i)
    {
        result.append(socketList[i]->getPlayerID());
    }

    return result;
}

bool ServerModel::changeClientID(unsigned int fromID, unsigned int toID)
{
    if(!this->clients.contains(fromID))
    {
        qDebug() << "Cannot change the client IDs from" << fromID << "to" << toID << "because no client existed with the fromID" << fromID;
        return false;
    }

    if(this->clients.contains(toID))
    {
        qDebug() << "Cannot change the client IDs from" << fromID << "to" << toID << "because" << toID << "already existed.";
        return false;
    }

    ClientSocket *client = this->clients.take(fromID);
    client->setPlayerID(toID);
    this->clients.insert(toID, client);
    return true;
}

bool ServerModel::listen()
{
    if(!this->server.listen(QHostAddress::Any, this->port))
    {
        QMessageBox::critical(0, tr("PIDGIRL Server"),
                              tr("Unable to start the server: %1.")
                              .arg(this->server.errorString()));
        return false;
    }

    return true;
}

void ServerModel::sendData(unsigned int data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    QDataStream stream(client->refSocket());

    stream << data;

    return;
}

void ServerModel::sendData(int data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    QDataStream stream(client->refSocket());

    stream << data;

    return;
}

void ServerModel::sendData(bool data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    QDataStream stream(client->refSocket());

    stream << data;

    return;
}

void ServerModel::sendData(const Serialize &data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    QDataStream stream(client->refSocket());

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QBuffer::ReadWrite);
    data.serialize(&buffer);

    bytes = qCompress(bytes, 7);

    stream << bytes.size();
    stream << bytes;

    buffer.close();

    return;
}

void ServerModel::sendData(const QString &data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    QDataStream stream(client->refSocket());

    stream << (int) data.toStdString().size();
    stream << data.toStdString().c_str();

    return;
}

void ServerModel::receiveData(unsigned int &data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    while(client->refSocket()->bytesAvailable() < (int) sizeof(unsigned int))
    {
        client->refSocket()->waitForReadyRead();
    }

    QDataStream stream(client->refSocket());

    stream >> data;

    return;
}

void ServerModel::receiveData(int &data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    while(client->refSocket()->bytesAvailable() < (int) sizeof(int))
    {
        client->refSocket()->waitForReadyRead();
    }

    QDataStream stream(client->refSocket());

    stream >> data;

    return;
}

void ServerModel::receiveData(bool &data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    while(client->refSocket()->bytesAvailable() < (int) sizeof(bool))
    {
        client->refSocket()->waitForReadyRead();
    }

    QDataStream stream(client->refSocket());

    stream >> data;

    return;
}

void ServerModel::receiveData(Serialize &data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    while(client->refSocket()->bytesAvailable() < (int) sizeof(int))
    {
        client->refSocket()->waitForReadyRead();
    }

    QDataStream stream(client->refSocket());

    int size;
    stream >> size;

    while(client->refSocket()->bytesAvailable() < size)
    {
        client->refSocket()->waitForReadyRead();
        qDebug() << "Available are" << client->refSocket()->bytesAvailable();
    }

    QByteArray byteData;
    stream >> byteData;

    byteData = qUncompress(byteData);

    QBuffer buffer(&byteData);
    buffer.open(QBuffer::ReadWrite);

    data.deserialize(&buffer);

    buffer.close();

    return;
}

void ServerModel::receiveData(QString &data, unsigned int playerID)
{
    ClientSocket *client = this->clients.value(playerID, 0);

    if(!client)
    {
        qDebug("Given player ID to determine the client was invalid.");
        return;
    }

    while(client->refSocket()->bytesAvailable() < (int) sizeof(int))
    {
        client->refSocket()->waitForReadyRead();
    }

    QDataStream stream(client->refSocket());

    int size;
    stream >> size;

    while(client->refSocket()->bytesAvailable() < size)
    {
        client->refSocket()->waitForReadyRead();
    }

    char *rawString;
    stream >> rawString;
    data = QString(rawString);

    return;
}

void ServerModel::receivePendingData(ClientSocket *client)
{
    QDataStream stream(client->refSocket());
    int data;
    bool successful = false;

    stream >> data;

    switch(FromClient(data))
    {
    case RECEIVE_REQUEST_FOR_SPECIFIC_MAP:
    {
        successful = this->processor->execute(new ReplyToRequestForMap(client->getPlayerID()));
        qDebug(QString("Reply To Request For Map to be sent to Player ID %1.").arg(client->getPlayerID()).toStdString().c_str());
        break;
    }
    case RECEIVE_REQUEST_FOR_PLAYER:
    {
        successful = this->processor->execute(new ReplyToRequestForPlayer(client->getPlayerID()));
        qDebug(QString("Reply To Request For Player to be sent to Player ID %1.").arg(client->getPlayerID()).toStdString().c_str());
        break;
    }
    case RECEIVE_REQUEST_FOR_PLAYER_MODELS:
    {
        successful = this->processor->execute(new ReplyToRequestForPlayerModels(client->getPlayerID()));
        qDebug() << "Replied to Request For Player Models to Player ID " << client->getPlayerID();
        break;
    }
    case FROM_CLIENT_NEXT_TURN:
    {
        successful = this->processor->execute(new NextTurn());
        qDebug("It's Your Turn Now.");
        break;
    }
    case SEND_SPAWN_CHARACTER:
    {
        successful = this->processor->execute(new ReceiveSpawnCharacterFrom(client->getPlayerID()));
        qDebug("Received Client Character Spawn");
        break;
    }
    case SEND_UPDATE_CHARACTER:
    {
        successful = this->processor->execute(new ReceiveUpdateCharacterFrom(client->getPlayerID()));
        qDebug("Received Client Character Update");
        break;
    }
    case CHANGE_PLAYER_ID:
    {
        successful = this->processor->execute(new ReceiveChangePlayerID(client->getPlayerID()));
        qDebug("Received Change Player ID");
        break;
    }
    default: qDebug("Client has received an invalid command."); break;
    }

    if(!successful)
    {
        qDebug("Receive pending data failed.");
        return;
    }

    emit this->allDataReceivedFromClient((FromClient) data);

    return;
}

void ServerModel::newConnection()
{
    if(this->clients.size() == UINT_MAX)
    {
        QMessageBox::critical(0, tr("PIDGIRL Server"),
                              tr("Server is full. The server has %1 players, which is the most that this server can hold.")
                              .arg(QString::number(UINT_MAX)));
        return;
    }

    unsigned int newPlayerID = this->worldModel->refObjectID()->getNewSpawnIDFor(ObjectID::PLAYER);
    ClientSocket *newClient = new ClientSocket(newPlayerID, this->server.nextPendingConnection(), this);
    this->clients.insert(newPlayerID, newClient);
    connect(newClient, SIGNAL(disconnected(ClientSocket *)), this, SLOT(deleteDisconnectedClient(ClientSocket *)));

    this->processor->execute(new SendInitialPlayerInformation(newPlayerID));

    connect(newClient, SIGNAL(readyRead(ClientSocket *)), this, SLOT(receivePendingData(ClientSocket *)));
    emit connectionEtablished();
    return;
}

void ServerModel::deleteDisconnectedClient(ClientSocket *client)
{
    this->clients.remove(client->getPlayerID());
    this->processor->execute(new ClientDisconnected(client->getPlayerID()));
    client->deleteLater();

    qDebug("Client Disconnected.");

    emit this->clientDisconnect();
    return;
}

void ServerModel::socketError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(0, tr("PIDGIRL Server"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the Clients are all connected in order, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::critical(0, tr("PIDGIRL Server"),
                                 tr("The following error occurred: %1.")
                                 .arg(this->server.errorString()));
    }

    return;
}
