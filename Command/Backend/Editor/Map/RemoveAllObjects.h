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

#ifndef REMOVE_ALL_OBJECTS_H
#define REMOVE_ALL_OBJECTS_H

#include "Command/Backend/Undoable.h"
#include "MainView/Model/StackModel.h"
#include "Object/ObjectCharacter.h"
#include "Object/ObjectItem.h"
#include "Object/ObjectTile.h"
#include "Object/ObjectSpecial.h"

/** \addtogroup Commands
  * \{
  * \class RemoveAllObjects
  *
  * \brief Remove all objects from a stackmodel.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class RemoveAllObjects : public Undoable
{
    Q_OBJECT
private:
    StackModel *            stackModel;         ///< The stack from which to remove objects.
    ObjectCharacter *       undoCharacter;      ///< The character removed.
    QList<ObjectItem *>     undoItemList;       ///< The items removed.
    ObjectTile *            undoWall;           ///< The wall removed.
    ObjectTile *            undoFloor;          ///< The floor removed.
    QList<ObjectSpecial *>  undoSpecialList;    ///< The specials removed.

public:
    RemoveAllObjects(StackModel *stackModel, QObject *parent = 0);

    virtual bool execute();
    virtual void undo();
    virtual void redo();
};

#endif // REMOVE_ALL_OBJECTS_H
