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

#include "CreateCharacter.h"

#include <QMessageBox>

#include <iostream>

#include "Common/Common.h"
#include "Command/Backend/Game/Ingame/LoadStartMapFromIndex.h"
#include "Command/Backend/Game/Ingame/SpawnPlayerOnCurrentMap.h"
#include "Object/Character/Player.h"
#include "Network/WaitingForDataDialog.h"

CreateCharacter::CreateCharacter(QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("CreateCharacter");

    this->chooseStartMap = 0;
    this->chooseStartMapLayout = 0;
    this->chooseListView = 0;
    this->chooseListModel = 0;

    this->characterCreationLayout = new OptionsLayout();

    this->characterCreationDialog.setLayout(this->characterCreationLayout);
    this->characterCreationDialog.setWindowTitle(tr("Character Creation..."));
    this->characterCreationLayout->refOkButton()->setText(tr("Done"));
    this->characterCreationLayout->addWidget(this->characterCreationLayout->refOkButton(),1,0);
    connect(this->characterCreationLayout->refOkButton(), SIGNAL(clicked()), this, SLOT(characterDone()));

    this->informationWidget = new QWidget(&this->characterCreationDialog);
    this->informationWidgetLayout = new QGridLayout(this->informationWidget);
    this->informationWidgetLayout->setAlignment(Qt::AlignTop);
    this->informationWidget->setLayout(this->informationWidgetLayout);

    this->playerNameValidator.setRegExp(QRegExp(PIDGIRL::NAME_REG_EXP_STRING));

    this->playerNameEdit = new QLineEdit();
    this->playerNameEdit->setPlaceholderText(tr("Player Name?"));
    this->playerNameEdit->setValidator(&this->playerNameValidator);
}

CreateCharacter::~CreateCharacter()
{
    this->deleteConnectionListItems();
}

bool CreateCharacter::execute()
{
    if(!this->init())
    {
        return false;
    }

    if(this->characterCreationDialog.exec() == QDialog::Rejected)
    {
        return false;
    }

    int mapIndex = -1;

    if(this->gameModel->getPlayerChoosesStartLocation() && this->chooseListView->currentIndex().isValid())
    {
        mapIndex = this->chooseListView->currentIndex().row()-1;
    }

    qDebug(QString("Row chosen: %1").arg(mapIndex).toStdString().c_str());

    if(!this->processor->execute(new LoadStartMapFromIndex(mapIndex)))
    {
        QMessageBox::information(0,
                                 tr("Loading the starting map has failed..."),
                                 tr("The map couldn't be loaded."),
                                 QMessageBox::Ok);
        return false;
    }

    for(int i = 0; i < this->chooseListItems.size(); ++i)
    {
        delete this->chooseListItems[i];
    }

    return this->processor->execute(new SpawnPlayerOnCurrentMap(this->playerNameEdit->text()));
}

bool CreateCharacter::init()
{
    this->characterCreationLayout->addPropertyWidget(tr("Information"), this->informationWidget);

    this->informationWidgetLayout->addWidget(this->playerNameEdit,0,0);

    if(this->gameModel->getPlayerChoosesStartLocation())
    {
        this->chooseStartMap = new QWidget(&this->characterCreationDialog);
        this->chooseStartMapLayout = new QGridLayout(this->chooseStartMap);
        this->chooseStartMapLayout->setAlignment(Qt::AlignTop);
        this->chooseStartMap->setLayout(this->chooseStartMapLayout);

        this->characterCreationLayout->addPropertyWidget(tr("Starting Map"), this->chooseStartMap);

        this->chooseListView = new QListView(&this->characterCreationDialog);
        this->chooseListModel = new QStandardItemModel();
        this->chooseListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->chooseListView->setModel(this->chooseListModel);

        QVector< QString > mapPaths = this->worldModel->getStartMapWorldPaths();

        this->chooseListItems.append(new QStandardItem(tr("< Random >")));

        for(int i = 0; i < mapPaths.size(); ++i)
        {
            this->chooseListItems.append(new QStandardItem(mapPaths[i]));
        }

        this->chooseListModel->appendRow(this->chooseListItems[0]);

        for(int i = 1; i < this->chooseListItems.size(); ++i)
        {
            this->chooseListModel->appendRow(this->chooseListItems[i]);
        }

        this->chooseStartMapLayout->addWidget(this->chooseListView,0,0);
    }
    else
    {
        this->chooseStartMap = 0;
        this->chooseStartMapLayout = 0;
        this->chooseListView = 0;
        this->chooseListModel = 0;
    }

    if(this->gameModel->getGameType() == PIDGIRL::NETWORK && this->networkModel->isServer())
    {
        this->serverOverview = new QWidget(&this->characterCreationDialog);
        this->serverOverviewLayout = new QGridLayout(this->serverOverview);
        this->serverOverviewLayout->setAlignment(Qt::AlignTop);
        this->serverOverview->setLayout(this->serverOverviewLayout);

        this->connectionLabel = new QLabel(tr("Connections (Count: 0):"), this->serverOverview);
        this->serverOverviewLayout->addWidget(this->connectionLabel,0,0);

        this->connectionListView = new QListView(this->serverOverview);
        this->connectionListModel = new QStandardItemModel();
        this->connectionListView->setModel(this->connectionListModel);
        this->serverOverviewLayout->addWidget(this->connectionListView,1,0);

        connect(this->networkModel, SIGNAL(connectionEtablished()), this, SLOT(connectionsChanged()));
        connect(this->networkModel, SIGNAL(clientDisconnect()), this, SLOT(connectionsChanged()));

        this->characterCreationLayout->addPropertyWidget(tr("Server Overview"), this->serverOverview);
    }

    return true;
}

void CreateCharacter::deleteConnectionListItems()
{
    this->connectionListItems.clear();

    for(int i = 0; i < this->connectionListItems.size(); ++i)
    {
        delete this->connectionListItems[i];
    }
    return;
}

void CreateCharacter::characterDone()
{
    QString toBeValidated = this->playerNameEdit->text();
    int pos = 0;
    bool nameCorrect = QValidator::Acceptable == (QRegExpValidator(QRegExp(PIDGIRL::NAME_REG_EXP_STRING)).validate(toBeValidated, pos));

    if(!nameCorrect)
    {
        QStringList errors;

        if(!nameCorrect)
        {
            errors.append(tr("Player Name has to be at least %1 characters long.").arg(PIDGIRL::MIN_PLAYER_NAME_LENGTH));
        }

        QString output;

        for(int i = 0; i < errors.size(); ++i)
        {
            output.append("* ").append(errors[i]).append("\n\n");
        }

        QMessageBox::information(0,
                                 tr("Character not done yet..."),
                                 output,
                                 QMessageBox::Ok);
    }
    else
    {
        if(this->gameModel->getGameType() == PIDGIRL::NETWORK && this->networkModel->isServer())
        {
            disconnect(this->networkModel, SIGNAL(connectionEtablished()), this, SLOT(connectionsChanged()));
            disconnect(this->networkModel, SIGNAL(clientDisconnect()), this, SLOT(connectionsChanged()));
        }
        this->characterCreationDialog.done(QDialog::Accepted);
    }

    return;
}

void CreateCharacter::connectionsChanged()
{
    QVector< QString > connections = this->networkModel->getConnectionList();

    this->connectionListModel->clear();
    this->deleteConnectionListItems();

    for(int i = 0; i < connections.size(); ++i)
    {
        this->connectionListItems.append(new QStandardItem(connections[i]));
    }

    for(int i = 0; i < this->connectionListItems.size(); ++i)
    {
        this->connectionListModel->appendRow(this->connectionListItems[i]);
    }

    this->connectionLabel->setText(tr("Connections (Count: %1):").arg(connections.size()));

    return;
}
