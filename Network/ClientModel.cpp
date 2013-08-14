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

#include "ClientModel.h"

#include <QMessageBox>
#include <QDataStream>
#include <QHostAddress>
#include <QBuffer>

#include "Common/Common.h"

#include "Command/Backend/Network/Client/ReceiveInitialPlayerInformation.h"
#include "Command/Backend/Network/Client/ReceiveMap.h"
#include "Command/Backend/Network/Client/ReceivePlayer.h"
#include "Command/Backend/Network/Client/ReceivePlayerModels.h"
#include "Command/Backend/Network/ReceiveSpawnCharacterFrom.h"
#include "Command/Backend/Network/ReceiveUpdateCharacterFrom.h"
#include "Command/Backend/Game/Ingame/NextTurn.h"
#include "Command/Backend/Common/Quit.h"

ClientModel::ClientModel(const QString &ipAddress, int port, Processor *processor)
    : NetworkModel(port, processor), ipAddress(ipAddress)
{
    this->processor = processor;

    connect(&this->connection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));
}

ClientModel::~ClientModel()
{
    this->connection.disconnectFromHost();
}

bool ClientModel::isClient()
{
    return true;
}

bool ClientModel::isServer()
{
    return false;
}

bool ClientModel::changeClientID(unsigned int fromID, unsigned int toID)
{
    Q_UNUSED(fromID);
    Q_UNUSED(toID);

    qDebug() << "A client cannot change client IDs. The ID to which a client is connected to is always" << PIDGIRL::SERVER_PLAYER_ID;

    return false;
}

QVector<QString> ClientModel::getConnectionList()
{
    QVector<QString> result;
    result.append(QString("Client: %1 - PlayerID: %2").arg(this->connection.peerAddress().toString(), "0"));
    return result;
}

QVector< unsigned int > ClientModel::getConnectedPlayerIDs()
{
    QVector<unsigned int> result;
    result.append(0);
    return result;
}

bool ClientModel::connectTo()
{
    this->connection.connectToHost(this->ipAddress, this->port);

    // Wait for world model from server.
    if(!this->connection.waitForReadyRead(-1))
    {
        QMessageBox::critical(0, tr("PIDGIRL Client"),
                                 tr("When waiting for a ready to read, the following error occurred: %1.")
                                 .arg(this->connection.errorString()));
        return false;
    }

    this->receivePendingData(); // Receive the new client information immediatly.

    connect(&this->connection, SIGNAL(readyRead()), this, SLOT(receivePendingData()));
    connect(&this->connection, SIGNAL(disconnected()), this, SLOT(disconnectedFromServer()));
    return true;
}

void ClientModel::sendData(unsigned int data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.

    QDataStream stream(&this->connection);
    stream << data;

    return;
}

void ClientModel::sendData(int data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.

    QDataStream stream(&this->connection);
    stream << data;

    return;
}

void ClientModel::sendData(bool data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.

    QDataStream stream(&this->connection);
    stream << data;

    return;
}

void ClientModel::sendData(const Serialize &data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.
    QDataStream stream(&this->connection);

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QBuffer::ReadWrite);
    data.serialize(&buffer);

    bytes = qCompress(bytes);

    stream << bytes.size();
    stream << bytes;

    buffer.close();

    return;
}

void ClientModel::sendData(const QString &data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.
    QDataStream stream(&this->connection);

    stream << (int) data.toStdString().size();
    stream << data.toStdString().c_str();

    return;
}

void ClientModel::receiveData(unsigned int &data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.
    while(this->connection.bytesAvailable() < (int) sizeof(unsigned int))
    {
        this->connection.waitForReadyRead();
    }

    QDataStream stream(&this->connection);

    stream >> data;

    return;
}

void ClientModel::receiveData(int &data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.
    while(this->connection.bytesAvailable() < (int) sizeof(int))
    {
        this->connection.waitForReadyRead();
    }

    QDataStream stream(&this->connection);

    stream >> data;

    return;
}

void ClientModel::receiveData(bool &data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.
    while(this->connection.bytesAvailable() < (int) sizeof(bool))
    {
        this->connection.waitForReadyRead();
    }

    QDataStream stream(&this->connection);

    stream >> data;

    return;
}

void ClientModel::receiveData(Serialize &data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.

    while(this->connection.bytesAvailable() < (int) sizeof(int))
    {
        this->connection.waitForReadyRead();
    }

    QDataStream stream(&this->connection);

    int size;
    stream >> size;

    while(this->connection.bytesAvailable() < size)
    {
        this->connection.waitForReadyRead();
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

void ClientModel::receiveData(QString &data, unsigned int playerID)
{
    Q_UNUSED(playerID); // Since there is only one connection open to the server,
                        // we don't need player ID to determine to whom we're sending data to.

    while(this->connection.bytesAvailable() < (int) sizeof(int))
    {
        this->connection.waitForReadyRead();
    }

    QDataStream stream(&this->connection);

    int size;
    stream >> size;

    while(this->connection.bytesAvailable() < size)
    {
        this->connection.waitForReadyRead();
    }

    char *rawString;
    stream >> rawString;

    data = QString(rawString);

    return;
}

void ClientModel::receivePendingData()
{
    QDataStream stream(&this->connection);
    int data;
    bool successful = false;

    stream >> data;

    switch(FromServer(data))
    {
    case RECEIVE_INITIAL_PLAYER_INFORMATION:
    {
        successful = this->processor->execute(new ReceiveInitialPlayerInformation());
        qDebug("Initial Player information Received.");
        break;
    }
    case SEND_SPECIFIC_MAP:
    {
        successful = this->processor->execute(new ReceiveMap());
        qDebug("Reply To Specific Map Request Done.");
        break;
    }
    case SEND_SPECIFIC_PLAYER:
    {
        successful = this->processor->execute(new ReceivePlayer());
        qDebug("Reply To Specific Player Request Done.");
        break;
    }
    case SEND_PLAYER_MODELS:
    {
        successful = this->processor->execute(new ReceivePlayerModels());
        qDebug("Reply To Player Models Request Done.");
        break;
    }
    case FROM_SERVER_NEXT_TURN:
    {
        successful = this->processor->execute(new NextTurn());
        qDebug("Your Turn Is Now.");
        break;
    }
    case BROADCAST_SPAWN_CHARACTER:
    {
        successful = this->processor->execute(new ReceiveSpawnCharacterFrom(PIDGIRL::SERVER_PLAYER_ID));
        qDebug("Received the character spawn broadcasted.");
        break;
    }
    case BROADCAST_UPDATE_CHARACTER:
    {
        successful = this->processor->execute(new ReceiveUpdateCharacterFrom(PIDGIRL::SERVER_PLAYER_ID));
        qDebug("Received the character update broadcasted.");
        break;
    }
    default: qDebug("Client has received an invalid command."); break;
    }

    if(!successful)
    {
        qDebug("Receive pending data failed.");
        return;
    }

    emit this->allDataReceivedFromServer(FromServer(data));

    return;
}

void ClientModel::socketError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(0, tr("PIDGIRL Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(0, tr("PIDGIRL Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure a PIDGIRL server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::critical(0, tr("PIDGIRL Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(this->connection.errorString()));
    }

    return;
}

void ClientModel::disconnectedFromServer()
{
    QMessageBox::critical(0, tr("PIDGIRL Client"),
                             tr("The connection to the server closed."));

    qDebug("Server Disconnected.");

    return;
}
