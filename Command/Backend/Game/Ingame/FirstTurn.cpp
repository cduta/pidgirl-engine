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

#include "FirstTurn.h"

#include "Command/Backend/Game/Ingame/CreateCharacter.h"
#include "Common/Common.h"

FirstTurn::FirstTurn(QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("FirstTurn");

    this->inactivePlayerChosen = -1;

    this->chooseCharacterLayout = new OptionsLayout();
    this->chooseCharacterLayout->setPropertyListWidth(200);

    this->chooseCharacterDialog.setLayout(this->chooseCharacterLayout);
    this->chooseCharacterDialog.setWindowTitle(tr("Choose a character..."));
    connect(this->chooseCharacterLayout, SIGNAL(currentIndexChangedTo(int)), this,SLOT(indexChanged(int)));
}

bool FirstTurn::execute()
{
    PIDGIRL::writeLog("First Turn");

    if(!this->init())
    {
        return false;
    }

    if(!this->inactivePlayers.empty() && this->chooseCharacterDialog.exec() == QDialog::Rejected)
    {
        return false;
    }

    PIDGIRL::writeLogDone();
    if(this->inactivePlayerChosen == -1)
    {
        if(!this->processor->execute(new CreateCharacter()))
        {
            return false;
        }
    }
    else
    {
        unsigned int newID = this->inactivePlayers[this->inactivePlayerChosen]->getSpawnID();
        this->gameModel->loadMap(this->players[newID]->getLocalMapPath());
        this->gameModel->changePlayerID(newID);
        //this->gameModel->nextTurn();
    }

    return true;
}

bool FirstTurn::init()
{
    QPushButton *doneButton;

    this->newCharacterWidget = new QWidget(&this->chooseCharacterDialog);
    this->newCharacterLayout = new QGridLayout(this->newCharacterWidget);

    this->newCharacterLayout->addWidget(new QLabel("Choose this option to create a new character."),0,0);
    doneButton = new QPushButton(tr("Done"), this->newCharacterWidget);
    connect(doneButton, SIGNAL(clicked()), this, SLOT(done()));
    this->newCharacterLayout->addWidget(doneButton,1,0);
    this->newCharacterWidget->setLayout(this->newCharacterLayout);

    this->chooseCharacterLayout->addPropertyWidget("Create a New Character...", this->newCharacterWidget);

    this->players = this->gameModel->getPlayerModels();
    QList<PlayerModel *> playerList = this->players.values();

    for(int i = 0; i < playerList.size(); ++i)
    {
        if(!playerList[i]->isActivePlayer() && playerList[i]->hasCharacterSpawned())
        {
            this->inactivePlayers.append(this->gameModel->refPlayer(playerList[i]->getID()));
        }
    }

    QWidget *widget;
    QGridLayout *layout;

    for(int i = 0; i < this->inactivePlayers.size(); ++i)
    {
        widget = new QWidget(&this->chooseCharacterDialog);
        layout = new QGridLayout(widget);

        layout->addWidget(this->inactivePlayers[i]->createInformationWidget(&this->chooseCharacterDialog),0,0);

        doneButton = new QPushButton(tr("Done"), widget);
        connect(doneButton, SIGNAL(clicked()), this, SLOT(done()));
        layout->addWidget(doneButton,1,0);

        widget->setLayout(layout);

        this->choosableCharacterWidgets.append(widget);
        this->chooseCharacterLayout->addPropertyWidget(this->inactivePlayers[i]->getObjectName(), widget);
    }

    return true;
}

void FirstTurn::indexChanged(int index)
{
    if(index < 0)
    {
        index = 0;
    }

    this->inactivePlayerChosen = index-1;
    return;
}

void FirstTurn::done()
{
    this->chooseCharacterDialog.accept();
    return;
}
