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

#include "ShowGameOptions.h"

#include <QMessageBox>
#include <QFileDialog>

#include "Command/Backend/Game/Ingame/SaveGame.h"
#include "Game/Model/EMailGameModel.h"
#include "Game/Model/MailGameInfo.h"

ShowGameOptions::ShowGameOptions(QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("ShowGameOptions");

    this->specificGameTypeWidget = 0;
    this->specificGameTypeLayout = 0;
    this->saveGameButton = 0;
    this->addNewPlayerButton = 0;
    this->leaveGameButton = 0;
    this->saveDirLabel = 0;
    this->saveDirLineEdit = 0;
    this->saveDirChooseButton = 0;

    this->gameOptionsLayout = new OptionsLayout(&this->gameOptionsDialog);
    this->gameOptionsLayout->refApplyButton()->setVisible(false);
    this->gameOptionsLayout->refOkButton()->setVisible(false);
    this->gameOptionsDialog.setLayout(this->gameOptionsLayout);
}

bool ShowGameOptions::execute()
{
    if(!this->init())
    {
        return false;
    }

    this->gameOptionsDialog.exec();

    return true;
}

bool ShowGameOptions::init()
{
    this->specificGameTypeWidget = new QWidget(&this->gameOptionsDialog);
    this->specificGameTypeLayout = new QGridLayout(this->specificGameTypeWidget);
    this->specificGameTypeWidget->setLayout(this->specificGameTypeLayout);

    QString saveGameButtonText = tr("Save Game");
    QString saveGameToolTop = tr("Save the current game.");

    switch(this->gameModel->getGameType())
    {
    case PIDGIRL::HOTSEAT:
    {
        this->gameOptionsLayout->addPropertyWidget(tr("Solo / Hotseat"), this->specificGameTypeWidget);

        this->saveGameButton = new QPushButton(saveGameButtonText, this->specificGameTypeWidget);
        this->saveGameButton->setToolTip(saveGameToolTop);
        this->specificGameTypeLayout->addWidget(this->saveGameButton, 0,0);
        connect(this->saveGameButton, SIGNAL(clicked()), this, SLOT(saveGame()));

        this->addNewPlayerButton = new QPushButton(tr("Add New Player"), this->specificGameTypeWidget);
        this->addNewPlayerButton->setToolTip(tr("Add a new player to the game."));
        this->specificGameTypeLayout->addWidget(this->addNewPlayerButton, 1,0);
        connect(this->addNewPlayerButton, SIGNAL(clicked()), this, SLOT(addHotseatPlayer()));

        this->leaveGameButton = new QPushButton(tr("Leave Game"), this->specificGameTypeWidget);
        this->leaveGameButton->setToolTip(tr("You can leave the the game. Your turn will be skipped until you join again.\nThis will not close the game, if there are still players left to play."));
        this->specificGameTypeLayout->addWidget(this->leaveGameButton,2,0);
        connect(this->leaveGameButton, SIGNAL(clicked()), this, SLOT(leaveGame()));
        break;
    }
    case PIDGIRL::NETWORK:
    {
        this->gameOptionsLayout->addPropertyWidget(tr("Network"), this->specificGameTypeWidget);

        if(this->networkModel->isServer())
        {
            this->saveGameButton = new QPushButton(saveGameButtonText, this->specificGameTypeWidget);
            this->saveGameButton->setToolTip(saveGameToolTop);
            this->specificGameTypeLayout->addWidget(this->saveGameButton, 0,0);
            connect(this->saveGameButton, SIGNAL(clicked()), this, SLOT(saveGame()));
        }
        break;
    }
    case PIDGIRL::EMAIL:
    {
        MailGameInfo *mailGameInfo = qobject_cast<EMailGameModel *>(this->gameModel)->refMailGameInfo(this->gameModel->getPlayerID());

        this->gameOptionsLayout->addPropertyWidget(tr("Play By E-Mail"), this->specificGameTypeWidget);

        this->saveDirLabel = new QLabel(tr("Save Location:"), this->specificGameTypeWidget);
        this->specificGameTypeLayout->addWidget(this->saveDirLabel, 0,0);

        this->saveDirLineEdit = new QLineEdit(mailGameInfo->getSaveDirAbsolutePath(), this->specificGameTypeWidget);
        this->saveDirLineEdit->setPlaceholderText(tr("<Default Directory>"));
        connect(this->saveDirLineEdit, SIGNAL(textChanged(QString)), mailGameInfo, SLOT(setSaveDir(QString)));
        this->specificGameTypeLayout->addWidget(this->saveDirLineEdit, 0,1);

        this->saveDirChooseButton = new QPushButton("...", this->specificGameTypeWidget);
        this->saveDirChooseButton->setMaximumWidth(25);
        connect(this->saveDirChooseButton, SIGNAL(clicked()), this, SLOT(choseSaveDir()));
        this->specificGameTypeLayout->addWidget(this->saveDirChooseButton, 0,2);

        this->addNewPlayerButton = new QPushButton(tr("Add New Player"), this->specificGameTypeWidget);
        this->addNewPlayerButton->setToolTip(tr("Add a new player to the game. His turn will be last."));
        this->specificGameTypeLayout->addWidget(this->addNewPlayerButton, 2,0,3,0);
        connect(this->addNewPlayerButton, SIGNAL(clicked()), this, SLOT(addHotseatPlayer()));

        this->leaveGameButton = new QPushButton(tr("Leave Game"), this->specificGameTypeWidget);
        this->leaveGameButton->setToolTip(tr("You can leave the the game. Your turn will end and the game will close."));
        this->specificGameTypeLayout->addWidget(this->leaveGameButton,3,0,3,0);
        connect(this->leaveGameButton, SIGNAL(clicked()), this, SLOT(leaveGame()));
        break;
    }
    default: return false; break;
    }

    return true;
}

void ShowGameOptions::saveGame()
{
    if(this->processor->execute(new SaveGame()))
    {
        this->gameOptionsDialog.accept();
    }
    return;
}

void ShowGameOptions::addHotseatPlayer()
{
    int addPlayer = QMessageBox::question(0,
                                          tr("New Player?"),
                                          tr("Do you really want to add a new player?"),
                                          QMessageBox::Yes, QMessageBox::No);

    if(addPlayer == QMessageBox::Yes)
    {
        unsigned int newPlayerID = this->worldModel->refObjectID()->getNewSpawnIDFor(ObjectID::PLAYER);
        this->gameModel->addNewPlayer(newPlayerID, new PlayerModel(newPlayerID));
        QMessageBox::information(0,
                                 tr("New player added."),
                                 tr("The new player will create a new character when it's her turn.\nHis turn starts after everyone took their turn."),
                                 QMessageBox::Ok);

        this->gameOptionsDialog.accept();
    }
    return;
}

void ShowGameOptions::leaveGame()
{
    int quitPlaying = QMessageBox::question(0,
                                            tr("Quit Playing?"),
                                            tr("Do you really want to quit the game? Your character will not be removed.\nYour turn will end and the next player's turn will start."),
                                            QMessageBox::Yes, QMessageBox::No);

    if(quitPlaying == QMessageBox::Yes)
    {
        this->gameModel->refPlayerModel(this->gameModel->getPlayerID())->setActivePlayer(false);
        this->gameOptionsDialog.accept();
        this->gameModel->endTurn();
    }

    return;
}

void ShowGameOptions::choseSaveDir()
{
    QString dirPath = QFileDialog::getExistingDirectory(0, tr("Choose a E-Mail Save Location..."));

    if(dirPath.isEmpty() || !this->saveDirLineEdit)
    {
        return;
    }

    this->saveDirLineEdit->setText(dirPath);
}
