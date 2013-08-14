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

#ifndef CLIENT_MODEL_H
#define CLIENT_MODEL_H

#include <QTcpSocket>
#include <QString>
#include <QDataStream>

#include "Command/Processor.h"
#include "Network/NetworkModel.h"

/** \addtogroup Network
  * \{
  * \class ClientModel
  *
  * \brief The client side implementation of the network model.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ClientModel : public NetworkModel
{
    Q_OBJECT

private:
    Processor *  processor;
    QString      ipAddress;     ///< The IPAddress of the Server.
    QTcpSocket   connection;    ///< The connection to the server.

public:
    ClientModel(const QString &ipAddress, int port, Processor *processor);
    virtual ~ClientModel();

    virtual bool isClient();
    virtual bool isServer();

    virtual bool changeClientID(unsigned int fromID, unsigned int toID);

    /**
      * @brief Connect to the given ipAddress with the given port. It will also set up world and game model with the informations given by the server.
      * @return True, if connection was established. Otherwise, false.
      */
    bool connectTo();

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

    // Get-Methods
    virtual QVector< QString > getConnectionList();
    virtual QVector< unsigned int > getConnectedPlayerIDs();

private slots:
    void receivePendingData();
    void socketError(QAbstractSocket::SocketError socketError);
    void disconnectedFromServer();
};

#endif // CLIENT_MODEL_H
