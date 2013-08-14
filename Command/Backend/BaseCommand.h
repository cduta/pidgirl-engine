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

#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <QObject>
#include <QIcon>

/** \addtogroup Commands
  * \{
  * \class BaseCommand
  *
  * \brief Interface to ensure the least needed functions for the commands.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class BaseCommand : public QObject
{
    Q_OBJECT
private:
    bool errorEnabled;

public:
    explicit BaseCommand(QObject *parent = 0);

    /**
      * @brief Check if the command is executable.
      * @return If the command is executable.
      */
    virtual bool isExecutable() const = 0;

    /**
      * \brief Executes the command.
      * \returns True, if successful.
      */
    virtual bool execute() = 0;

    /**
      * \brief Undo changes made by the command.
      */
    virtual void undo() = 0;

    /**
      * \brief Redo changes made by the undoing of the command.
      */
    virtual void redo() = 0;

    /**
      * \brief Determines undoability.
      * \returns True, if this command can be undone.
      */
    virtual bool isUndoable() = 0;

    /**
      * \brief Determines, if undo and redo should be cleared.
      * \returns True, if undo and redo should be cleared.
      */
    virtual bool isClearingUndoRedo() = 0;

    // Get-Methods
    bool isErrorEnabled() const;
    virtual const QIcon getCommandIcon() const;

    // Set-Methods
    virtual void setModels(QObject *processor,
                           QObject *undoRedo,
                           QObject *editorModel,
                           QObject *worldModel,
                           QObject *gameModel,
                           QObject *mapModel,
                           QObject *networkModel) = 0;

    void setErrorEnabled(bool errorEnabled);
};

#endif // BASE_COMMAND_H
