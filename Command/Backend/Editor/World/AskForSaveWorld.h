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

#ifndef ASK_FOR_SAVE_WORLD_H
#define ASK_FOR_SAVE_WORLD_H

#include "Command/Backend/NotUndoable.h"
#include "Common/YesNoCancelDialog.h"

/** \addtogroup Commands
  * \{
  * \class AskForSaveWorld
  *
  * \brief Ask whenever the world isn't saved, if you want to save.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class AskForSaveWorld : public NotUndoable
{
    Q_OBJECT

private:
    YesNoCancelDialog   yncDialog;  ///< Dialog to ask for the current world to be saved.

public:
    AskForSaveWorld(QObject *parent = 0);

    virtual bool execute();
};

#endif // ASK_FOR_SAVE_WORLD_H
