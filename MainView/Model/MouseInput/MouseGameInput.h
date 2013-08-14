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

#ifndef MOUSE_GAME_INPUT_H
#define MOUSE_GAME_INPUT_H

#include "MainView/Model/MouseInput/MouseInput.h"

/** \addtogroup State
  * \{
  * \class MouseGameInput
  *
  * \brief The mouse input manager for the game.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MouseGameInput : public MouseInput
{
    Q_OBJECT

public:
    MouseGameInput(GameModel *gameModel, MapModel *mapModel, Processor *processor, QObject *parent = 0);

    virtual void nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack);

    void showGameContextMenu(StackModel *stackModel);

private slots:
    void endTurn();
    void showGameOptions();
};

#endif // MOUSE_GAME_INPUT_H
