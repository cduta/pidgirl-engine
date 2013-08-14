/*
* A game about cooperative gameplay and defeating the evil empire.
* Copyright (C) 2012  Ryoga Unryu
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

#ifndef NOT_UNDOABLE_H
#define NOT_UNDOABLE_H

#include "Command/Backend/Command.h"

/** \addtogroup Commands
  * \{
  * \class NotUndoable
  *
  * \brief Abstract class to be inherited by Commands which are not undoable.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class NotUndoable : public Command
{
    Q_OBJECT

    const bool clearsUndoRedo; ///< True, if this command clears everything in the undo and redo stack.

public:
    explicit NotUndoable(bool clearsUndoRedo, QObject *parent = 0);

    virtual bool isExecutable() const;
    virtual bool execute() = 0;
    virtual void undo();
    virtual void redo();
    virtual bool isUndoable();
    virtual bool isClearingUndoRedo();
};

#endif // NOT_UNDOABLE_H
