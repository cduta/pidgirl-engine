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

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>

#include "Object/ObjectBase.h"
#include "Command/UndoRedo.h"
#include "Command/Backend/BaseCommand.h"
#include "Editor/Model/EditorModel.h"
#include "Editor/Model/WorldModel.h"
#include "Game/Model/GameModel.h"
#include "MainView/Model/MapModel.h"
#include "Network/NetworkModel.h"

/** \addtogroup CommandProcessor
  * \{
  * \class Processor
  *
  * \brief Process commands and manages them accordingly.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class Processor : public QObject
{
    Q_OBJECT

signals:
    void commandProcessed(); ///< Emmited whenever a command is processed.

private:
    UndoRedo *      undoRedo;       ///< The Undo and Redo management object.
    EditorModel *   editorModel;
    WorldModel *    worldModel;
    GameModel *     gameModel;
    MapModel *      mapModel;
    NetworkModel *  networkModel;

public:
    explicit Processor(QObject *parent = 0);

    /**
      * @brief Check if the command can be executed.
      * @param command The command to be checked.
      * @return True if command is executable. Otherwise, false.
      */
    bool isExecutable(BaseCommand *command);

    /**
      * \brief Execute a given command.
      * \param command The command to be executed.
      * \return True if the given command was executed successfully. Otherwise, false.
      * \note The given command will have the processor set as its parent may be deleted when executed.
      */
    bool execute(BaseCommand *command);

    // Set-Methods
    void setEditorModel(EditorModel *editorModel);
    void setWorldModel(WorldModel *worldModel);
    void setGameModel(GameModel *gameModel);
    void setMapModel(MapModel *mapModel);
    void setNetworkModel(NetworkModel *networkModel);

    // Ref-Methods
    UndoRedo *refUndoRedo() const;
};

#endif // PROCESSOR_H
