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

#ifndef FIRST_TURN_H
#define FIRST_TURN_H

#include <QDialog>
#include <QList>
#include <QGridLayout>

#include "Command/Backend/Game/GameCommand.h"
#include "Common/FileManager.h"
#include "Common/OptionsLayout.h"
#include "Object/Character/Player.h"

/** \addtogroup Commands
  * \{
  * \class FirstTurn
  *
  * \brief Things to do for the very first turn.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class FirstTurn : public GameCommand
{
    Q_OBJECT
    int                     inactivePlayerChosen;       ///< Is -1 if a new player should be created. Otherwise it's an index corresponding to the inactivePlayers vector.
    QMap<unsigned int,
         PlayerModel *>     players;                    ///< Copy of the player models currently available.
    QList<Player *>         inactivePlayers;

    QDialog                 chooseCharacterDialog;
    OptionsLayout *         chooseCharacterLayout;      ///< The amount of widgets in this layout is always choosableCharacterWidgets.size() + 1.

    // New Character Widget
    QWidget *               newCharacterWidget;
    QGridLayout *           newCharacterLayout;
    QVector<QWidget *>      choosableCharacterWidgets;  ///< Choosable Characters. Characters of players that are inactive are choosable.


public:
    FirstTurn(QObject *parent = 0);

    virtual bool execute();

    bool init();

private slots:
    void indexChanged(int index);
    void done();
};

#endif // FIRST_TURN_H
