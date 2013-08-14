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

#ifndef LOAD_GAME_H
#define LOAD_GAME_H

#include <QDialog>

#include "Command/Backend/Game/GameCommand.h"
#include "Common/OptionsLayout.h"
#include "Common/FileManager.h"
#include "Game/Model/SaveGameFile.h"
#include "Game/GeneralSetupWidget.h"
#include "Game/SoloHotseatSetupWidget.h"
#include "Game/NetworkSetupWidget.h"

/** \addtogroup Commands
  * \{
  * \class LoadGame
  *
  * \brief Load a game for PIDGIRL Engine.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class LoadGame : public GameCommand
{
    Q_OBJECT

    GameModel **            gameModelPointer; ///< The Game Model pointer from the Main Window to be set in this.
    FileManager             fileManager;
    QString                 saveFilePath;

    // Game Setup Dialog
    QDialog                 loadSetupDialog;
    OptionsLayout *         loadSetupLayout;

    // Solo / Hotseat Widget
    SoloHotseatSetupWidget *soloHotseatSetupWidget;

    // Network Widget
    NetworkSetupWidget *    networkSetupWidget;

public:
    LoadGame(GameModel **gameModelPointer, QObject *parent = 0);

    virtual bool execute();

private:
    bool init();

private slots:
    void loadSoloHotseatGame();
    void loadNetworkGame();
};

#endif // LOAD_GAME_H
