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

#include "MouseInput.h"

MouseInput::MouseInput(MouseState *mouseState, GameModel *gameModel, MapModel *mapModel, Processor *processor, QObject *parent)
    : QObject(parent)
{
    this->processor = processor;
    this->gameModel = gameModel;
    this->mapModel = mapModel;
    this->currentMouseState = mouseState;

    this->contextMenu = 0;
}

MouseInput::~MouseInput()
{
    delete this->currentMouseState;
}

void MouseInput::mousePressed(QMouseEvent *event, StackModel *target)
{
    this->nextState(MouseState::PRESSED, event, target);
    return;
}

void MouseInput::mouseReleased(QMouseEvent *event, StackModel *target)
{
    this->nextState(MouseState::RELEASED, event, target);
    return;
}

void MouseInput::showContextMenu(const QPoint &pos)
{
    if(this->contextMenu)
    {
        connect(this->contextMenu, SIGNAL(aboutToHide()), this, SLOT(deleteContextMenu()));
        this->contextMenu->exec(pos);
    }
    return;
}

void MouseInput::deleteContextMenu()
{
    qDebug("Delete Context Menu.");
    this->contextMenu->deleteLater();
    this->contextMenu = 0;
    return;
}
