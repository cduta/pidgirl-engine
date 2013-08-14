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

#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include <QObject>
#include <QLinkedList>

#include "Command/Backend/BaseCommand.h"

/** \addtogroup CommandProcessor
  * \{
  * \class UndoRedo
  *
  * \brief Manage the Undo and Redo functionalities.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
namespace PIDGIRL
{
    const int MAX_UNDO_REDO_SIZE = 5;
}

class UndoRedo : public QObject
{
    Q_OBJECT

signals:
    void undoChanged(bool); ///< Emited whenever undo list changed.
    void redoChanged(bool); ///< Emited whenever redo list changed.

private:
    QLinkedList<BaseCommand *>  undoList; ///< Undoable command list.
    QLinkedList<BaseCommand *>  redoList; ///< Redoable command list.

    QLinkedList<BaseCommand *>  undoListSavedState; ///< The last undo state.
    QLinkedList<BaseCommand *>  redoListSavedState; ///< The last redo state.

    bool                        onlySavedWorldChanges;          ///< True, if the world has been saved since the last changes.
    bool                        onlySavedMapChanges;            ///< True, if the map has been saved since the last changed.
    bool                        possibleToReachOriginalState;   ///< True, if it's still possible to reach the original state of the map when loaded or created anew.

public:
    explicit UndoRedo(QObject *parent = 0);
    ~UndoRedo();

    /**
      * @brief Undo the last command.
      */
    void undo();

    /**
      * @brief Redo the last command.
      */
    void redo();

    /**
      * @brief Add another command to the undo list.
      * @param command The command to be added to the undo list.
      */
    void add(BaseCommand *command);

    /**
      * @brief Clear the undo and redo lists.
      */
    void clear();

private:
    // Clear the undo and redo lists.
    void clearUndoList();
    void clearRedoList();

public:
    // Get-Methods
    bool hasOnlySavedMapChanges();
    bool hasOnlySavedWorldChanges();

    // Set-Methods
    void setSavedStates();
    void setOnlySavedWorldChanges(bool onlySavedWorldChanges);
    void setOnlySavedMapChanges(bool onlySavedMapChanges);
    void setPossibleToReachOriginalState(bool possibleToReachOriginalState);
};

#endif // UNDO_REDO_H
