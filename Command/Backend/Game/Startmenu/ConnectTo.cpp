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

#include "ConnectTo.h"

#include <QGridLayout>

#include "Command/Backend/Game/Startmenu/PreloadWorld.h"
#include "Common/Common.h"
#include "Network/ClientModel.h"
#include "Network/WaitingForDataDialog.h"

ConnectTo::ConnectTo(QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("ConnectTo");

    this->connectToDialog.setWindowTitle(tr("Connect To..."));
    connect(&(this->connectToDialog), SIGNAL(rejected()),this, SLOT(quit()));

    this->connectToLayout = new QGridLayout(&this->connectToDialog);
    this->connectToDialog.setLayout(this->connectToLayout);

    this->IPAddressLabel = new QLabel("IP Address:", &this->connectToDialog);
    this->IPAddressEdit = new QLineEdit("localhost", &this->connectToDialog);
    this->IPAddressValdidator = new QRegExpValidator(QRegExp(PIDGIRL::IP_ADDRESS_REG_EXP_STRING), this->IPAddressEdit);
    this->IPAddressEdit->setValidator(this->IPAddressValdidator);
    this->portLabel = new QLabel("Port:", &this->connectToDialog);
    this->portEdit = new QLineEdit("64120", &this->connectToDialog);
    this->portValidator = new QIntValidator(1025, 65535, this->portEdit);
    this->portEdit->setValidator(this->portValidator);

    this->startNetworkButton = new QPushButton(tr("Start Game"), &this->connectToDialog);
    connect(this->startNetworkButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
}

bool ConnectTo::execute()
{
    if(!this->initToConnectDialog())
    {
        return false;
    }

    if(this->connectToDialog.exec() != QDialog::Accepted)
    {
        return false;
    }

    WaitingForDataDialog waitDialog(this->clientModel, tr("Waiting for your turn..."), tr("Game Starts when it's your turn..."), this);
    if(!waitDialog.waitFor(FROM_SERVER_NEXT_TURN))
    {
        return false;
    }

    return true;
}

bool ConnectTo::initToConnectDialog()
{
    this->connectToLayout->addWidget(this->IPAddressLabel,0,0,Qt::AlignLeft);
    this->connectToLayout->addWidget(this->IPAddressEdit,0,1,Qt::AlignLeft);
    this->connectToLayout->addWidget(this->portLabel,1,0,Qt::AlignLeft);
    this->connectToLayout->addWidget(this->portEdit,1,1,Qt::AlignLeft);
    this->connectToLayout->addWidget(this->startNetworkButton,2,1,Qt::AlignRight);

    return true;
}

void ConnectTo::connectToServer()
{
    this->clientModel = new ClientModel(this->IPAddressEdit->text(), this->portEdit->text().toInt(), this->processor);
    this->processor->setNetworkModel(this->clientModel);
    if(!this->clientModel->connectTo())
    {
        this->connectToDialog.done(QDialog::Rejected);
    }
    this->connectToDialog.done(QDialog::Accepted);
    return;
}
