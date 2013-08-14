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

#ifndef NETWORK_MODEL_H
#define NETWORK_MODEL_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

#include "Common/Serialize.h"

/**
  * @brief The Enum for messages received from the server.
  */
enum FromServer
{
    RECEIVE_INITIAL_PLAYER_INFORMATION = 0,
    SEND_SPECIFIC_MAP,
    SEND_SPECIFIC_PLAYER,
    SEND_PLAYER_MODELS,
    FROM_SERVER_NEXT_TURN,
    BROADCAST_SPAWN_CHARACTER,
    BROADCAST_UPDATE_CHARACTER
};

/**
  * @brief The Enum for messages received from the client.
  */
enum FromClient
{
    RECEIVE_REQUEST_FOR_SPECIFIC_MAP = 0,
    RECEIVE_REQUEST_FOR_PLAYER_MODELS,
    RECEIVE_REQUEST_FOR_PLAYER,
    END_TURN,
    FROM_CLIENT_NEXT_TURN,
    SEND_SPAWN_CHARACTER,
    SEND_UPDATE_CHARACTER,
    CHANGE_PLAYER_ID
};

/** \addtogroup Network
  * \{
  * \class NetworkModel
  *
  * \brief The network model managing connections and interpretations of incoming messages to be converted to commands.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class NetworkModel : public QObject
{
    Q_OBJECT
signals:
    void connectionEtablished();
    void clientDisconnect();
    void allDataReceivedFromServer(FromServer);
    void allDataReceivedFromClient(FromClient);

protected:
    int port;

public:
    NetworkModel(int port, QObject *parent = 0);
    virtual ~NetworkModel();

    /**
      * @brief Change a client ID.
      * @param fromID The client connection ID from which to change.
      * @param toID The client ID to which to change to.
      * @return True, if successfully changed. Otherwise, false.
      */
    virtual bool changeClientID(unsigned int fromID, unsigned int toID) = 0;

    /**
      * @brief Sends the given data to a playerID.
      * @param data The data to be sent.
      * @param playerID The ID the data needs to be sent to.
      */
    virtual void sendData(unsigned int data, unsigned int playerID = 0) = 0;
    virtual void sendData(int data, unsigned int playerID = 0) = 0;
    virtual void sendData(bool data, unsigned int playerID = 0) = 0;
    virtual void sendData(const Serialize &data, unsigned int playerID = 0) = 0;
    virtual void sendData(const QString &data, unsigned int playerID = 0) = 0;

    /**
      * @brief Receive data from a client with the given playerID.
      * @param data The data to hold the data received.
      * @param playerID The ID of the client data is received from.
      */
    virtual void receiveData(unsigned int &data, unsigned int playerID = 0) = 0;
    virtual void receiveData(int &data, unsigned int playerID = 0) = 0;
    virtual void receiveData(bool &data, unsigned int playerID = 0) = 0;
    virtual void receiveData(Serialize &data, unsigned int playerID = 0) = 0;
    virtual void receiveData(QString &data, unsigned int playerID = 0) = 0;

    // Get-Methods
    virtual bool isClient() = 0;
    virtual bool isServer() = 0;
    virtual QVector< QString > getConnectionList() = 0;
    virtual QVector< unsigned int > getConnectedPlayerIDs() = 0;
};

#endif // NETWORK_MODEL_H
