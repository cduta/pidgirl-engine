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

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <QTcpSocket>

class ClientSocket : public QObject
{
    Q_OBJECT

signals:
    void readyRead(ClientSocket *socket);
    void disconnected(ClientSocket *socket);

private:
    unsigned int playerID;  ///< Consant unique ID connecting this connection with a given player model.
    QTcpSocket * socket;    ///< The socket connection to this player client.

public:
    explicit ClientSocket(unsigned int playerID, QTcpSocket *socket, QObject *parent = 0);
    ~ClientSocket();

    // Get-Methods
    unsigned int getPlayerID() const;

    // Set-Methods
    void setPlayerID(unsigned int playerID);

    // Red-Methods
    QTcpSocket *refSocket() const;

private slots:
    void gotReadyRead();
    void gotDisconnected();
    
};

#endif // CLIENT_SOCKET_H
