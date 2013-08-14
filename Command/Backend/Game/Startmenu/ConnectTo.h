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

#ifndef CONNECT_TO_H
#define CONNECT_TO_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QIntValidator>

#include "Command/Backend/Game/GameCommand.h"
#include "Network/ClientModel.h"

/** \addtogroup Commands
  * \{
  * \class ConnectTo
  *
  * \brief Connect to a running PIDGIRL Server
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ConnectTo : public GameCommand
{
    Q_OBJECT

    ClientModel *       clientModel;

    // ConnectTo Dialog
    QDialog             connectToDialog;
    QGridLayout *       connectToLayout;

    // ConnectTo Elements
    QLabel *            IPAddressLabel;
    QLineEdit *         IPAddressEdit;
    QRegExpValidator *  IPAddressValdidator;
    QLabel *            portLabel;
    QLineEdit *         portEdit;
    QIntValidator *     portValidator;
    QPushButton *       startNetworkButton;

public:
    ConnectTo(QObject *parent = 0);

    virtual bool execute();

    /**
      * @brief Initialize the Connect Dialog.
      * @return True, if initialization is successful. Otherwise, false.
      */
    bool initToConnectDialog();

private slots:
    /**
      * @brief Connect a server, close dialog with accept, if succesful and otherwise close dialog with reject.
      */
    void connectToServer();
};

#endif // CONNECT_TO_H
