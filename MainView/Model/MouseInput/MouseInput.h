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

#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

#include <QObject>
#include <QMouseEvent>
#include <QMenu>

#include "Editor/Model/EditorModel.h"
#include "Command/Processor.h"
#include "MainView/Model/MouseInput/MouseState.h"
#include "MainView/Model/StackModel.h"
#include "MainView/Model/MapModel.h"
#include "Game/Model/GameModel.h"

/** \addtogroup State
  * \{
  * \class MouseInput
  *
  * \brief The base class that manages the flow of the events to be processed next.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MouseInput : public QObject
{
    Q_OBJECT

signals:
    void showContextMenu(StackModel *);

protected:
    MouseState *    currentMouseState;

    Processor *     processor;
    GameModel *     gameModel;
    MapModel *      mapModel;

    QMenu *         contextMenu;
public:
    explicit MouseInput(MouseState *mouseState, GameModel *gameModel, MapModel *mapModel, Processor *processor, QObject *parent = 0);
    ~MouseInput();

    virtual void nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack) = 0;

    virtual void mousePressed(QMouseEvent *event, StackModel *target);
    virtual void mouseReleased(QMouseEvent *event, StackModel *target);

    void showContextMenu(const QPoint &pos);

protected slots:
    void deleteContextMenu();
};

#endif // MOUSE_INPUT_STATE_H
