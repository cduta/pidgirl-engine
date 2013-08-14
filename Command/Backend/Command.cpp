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

#include "Command.h"

Command::Command(QObject *parent)
    : BaseCommand(parent)
{
    this->processor = 0;
    this->undoRedo = 0;
    this->editorModel = 0;
    this->worldModel = 0;
    this->gameModel = 0;
    this->mapModel = 0;
}

void Command::setModels(QObject *processor,
                        QObject *undoRedo,
                        QObject *editorModel,
                        QObject *worldModel,
                        QObject *gameModel,
                        QObject *mapModel,
                        QObject *networkModel)
{
    this->processor = qobject_cast<Processor *>(processor);
    this->undoRedo = qobject_cast<UndoRedo *>(undoRedo);
    this->editorModel = qobject_cast<EditorModel *>(editorModel);
    this->worldModel = qobject_cast<WorldModel *>(worldModel);
    this->gameModel = qobject_cast<GameModel *>(gameModel);
    this->mapModel = qobject_cast<MapModel *>(mapModel);
    this->networkModel = qobject_cast<NetworkModel *>(networkModel);
    return;
}
