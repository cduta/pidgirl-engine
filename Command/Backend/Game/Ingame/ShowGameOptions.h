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

#ifndef SHOW_GAME_OPTIONS_H
#define SHOW_GAME_OPTIONS_H

#include "Command/Backend/Game/GameCommand.h"

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include "Common/OptionsLayout.h"

/** \addtogroup Commands
  * \{
  * \class ShowGameOptions
  *
  * \brief Show the options for the game.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ShowGameOptions : public GameCommand
{
    Q_OBJECT

    QDialog         gameOptionsDialog;
    OptionsLayout * gameOptionsLayout;

    QWidget *       specificGameTypeWidget;
    QGridLayout *   specificGameTypeLayout;

    // Save Game
    QPushButton *   saveGameButton;

    // Leave Game Button
    QPushButton *   leaveGameButton;

    // Add a new player
    QPushButton *   addNewPlayerButton;

    // E-Mail
    QLabel *        saveDirLabel;
    QLineEdit *     saveDirLineEdit;
    QPushButton *   saveDirChooseButton;

public:
    ShowGameOptions(QObject *parent = 0);

    virtual bool execute();

private:
    bool init();

private slots:
    void saveGame();
    void addHotseatPlayer();
    void leaveGame();
    void choseSaveDir();
};

#endif // SHOW_GAME_OPTIONS_H
