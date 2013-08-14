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

#ifndef COMMAND_H
#define COMMAND_H

#include "Command/Backend/BaseCommand.h"

#include "Command/Processor.h"
#include "Command/UndoRedo.h"
#include "Editor/Model/EditorModel.h"
#include "Editor/Model/WorldModel.h"
#include "Game/Model/GameModel.h"
#include "MainView/Model/MapModel.h"
#include "Network/NetworkModel.h"

/** \addtogroup Commands
  * \{
  * \class Command
  *
  * \brief The base for all commands.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class Command : public BaseCommand
{
    Q_OBJECT

protected:
    Processor *     processor;
    UndoRedo *      undoRedo;
    EditorModel *   editorModel;
    WorldModel *    worldModel;
    GameModel *     gameModel;
    MapModel *      mapModel;
    NetworkModel *  networkModel;

public:
    Command(QObject *parent = 0);

    virtual bool isExecutable() const = 0;
    virtual bool execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual bool isUndoable() = 0;
    virtual bool isClearingUndoRedo() = 0;

    // Set-Methods
    virtual void setModels(QObject *processor,
                           QObject *undoRedo,
                           QObject *editorModel,
                           QObject *worldModel,
                           QObject *gameModel,
                           QObject *mapModel,
                           QObject *networkModel);
};

#endif // COMMAND_H
