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

#ifndef SERVER_MODEL_H
#define SERVER_MODEL_H

#include <QTcpServer>
#include <QMap>

#include "Network/NetworkModel.h"
#include "Network/ClientSocket.h"
#include "Command/Processor.h"
#include "Editor/Model/WorldModel.h"

/** \addtogroup Network
  * \{
  * \class ClientModel
  *
  * \brief The server side implementation of the network model.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ServerModel : public NetworkModel
{
    Q_OBJECT

private:
    Processor *             processor;
    WorldModel *          worldModel;

    QTcpServer              server;         ///< The Server connecting to all the clients.
    QMap<unsigned int,
         ClientSocket *>    clients;        ///< A map with all clients. The key is the player's ID.

public:
    ServerModel(int port, WorldModel *worldModel, Processor *processor);
    virtual ~ServerModel();

    virtual bool isClient();
    virtual bool isServer();
    virtual QVector<QString> getConnectionList();
    virtual QVector<unsigned int> getConnectedPlayerIDs();

    virtual bool changeClientID(unsigned int fromID, unsigned int toID);
    bool listen();

    virtual void sendData(unsigned int data, unsigned int playerID = 0);
    virtual void sendData(int data, unsigned int playerID = 0);
    virtual void sendData(bool data, unsigned int playerID = 0);
    virtual void sendData(const Serialize &data, unsigned int playerID = 0);
    virtual void sendData(const QString &data, unsigned int playerID = 0);

    virtual void receiveData(unsigned int &data, unsigned int playerID = 0);
    virtual void receiveData(int &data, unsigned int playerID = 0);
    virtual void receiveData(bool &data, unsigned int playerID = 0);
    virtual void receiveData(Serialize &data, unsigned int playerID = 0);
    virtual void receiveData(QString &data, unsigned int playerID = 0);

private slots:
    void receivePendingData(ClientSocket *client);
    void newConnection();
    void deleteDisconnectedClient(ClientSocket *client);
    void socketError(QAbstractSocket::SocketError socketError);

};

#endif // SERVER_MODEL_H
