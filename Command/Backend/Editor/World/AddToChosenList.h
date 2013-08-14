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

#ifndef ADD_TO_CHOSEN_LIST_H
#define ADD_TO_CHOSEN_LIST_H

#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QModelIndex>

#include "Command/Backend/NotUndoable.h"
#include "Common/FileManager.h"

/** \addtogroup Commands
  * \{
  * \class AddToChosenList
  *
  * \brief Add the current index to the chosen list.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class AddToChosenList : public NotUndoable
{
    Q_OBJECT
private:
    QFileSystemModel *  availableFileSystemModel;   ///< The file system model of which to get the path from.
    QStandardItemModel *chosenListModel;            ///< The list model representing the already chosen entries.
    QModelIndex         currentIndex;               ///< The current index to be added to the chosen list model.

public:
    AddToChosenList(QFileSystemModel *availableFileSystemModel, QStandardItemModel *chosenListModel, const QModelIndex &currentIndex, QObject *parent = 0);

    virtual bool execute();
};

#endif // ADD_TO_CHOSEN_LIST_H
