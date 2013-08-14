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

#ifndef SETUP_NEW_GAME_H
#define SETUP_NEW_GAME_H

#include <QDialog>
#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QRegExpValidator>

#include "Command/Backend/Game/GameCommand.h"
#include "Common/OptionsLayout.h"
#include "Game/GeneralSetupWidget.h"
#include "Game/SoloHotseatSetupWidget.h"
#include "Game/NetworkSetupWidget.h"
#include "Game/EMailSetupWidget.h"

/** \addtogroup Commands
  * \{
  * \class SetupNewGame
  *
  * \brief Setup a new game for PIDGIRL Engine
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class SetupNewGame : public GameCommand
{
    Q_OBJECT
private:
    GameModel **            gameModelPointer; ///< The Game Model pointer from the Main Window to be set in this.

    // Game Setup Dialog
    QDialog                 gameSetupDialog;
    OptionsLayout *         gameSetupLayout;

    // General Widget
    GeneralSetupWidget *    generalSetupWidget;

    // Solo / Hotseat Widget
    SoloHotseatSetupWidget *soloHotseatSetupWidget;

    // Network Widget
    NetworkSetupWidget *    networkSetupWidget;

    // E-Mail Widget
    EMailSetupWidget *      emailSetupWidget;

public:
    SetupNewGame(GameModel **gameModelPointer, QObject *parent = 0);

    virtual bool execute();

private:
    /**
      * @brief Initialize the Game Setup Dialog.
      * @return True if initialization was successful, otherwise false.
      */
    bool initGameSetupDialog();

private slots:
    /**
      * @brief Apply the General Properties to any game started.
      */
    void applyGeneralProperties();

    /**
      * @brief Initialize the Solo / Hotseat Game when triggered.
      */
    void initSoloHotseat();

    /**
      * @brief Initialize the Network when triggered.
      */
    void initNetwork();

    /**
      * @brief Initialize the E-Mail Game.
      */
    void initEMailGame();
};


#endif // SETUP_NEW_GAME_H
