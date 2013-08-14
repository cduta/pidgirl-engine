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

#include "AddToChosenList.h"

#include "Common/FileManager.h"

#include <QMessageBox>

AddToChosenList::AddToChosenList(QFileSystemModel *availableFileSystemModel, QStandardItemModel *chosenListModel, const QModelIndex &currentIndex, QObject *parent)
    : NotUndoable(false, parent), currentIndex(currentIndex)
{
    this->setObjectName("AddToChosenList");
    this->availableFileSystemModel = availableFileSystemModel;
    this->chosenListModel = chosenListModel;
}

bool AddToChosenList::execute()
{
    QString chosenFullPath = this->availableFileSystemModel->filePath(this->currentIndex);

    QString chosenPath = QString(chosenFullPath).remove(0,this->availableFileSystemModel->rootPath().size());

    if(QFileInfo(chosenFullPath).isDir())
    {
        QMessageBox::critical(0, tr("Couldn't add a map to the start maps..."),
                              tr("The chosen entry %1 was a directory and\ncannot be added as a start map.").arg(chosenPath));
        return true;
    }

    MapModel mapModel;
    FileManager fileManager;

    fileManager.deserialize(&mapModel, chosenFullPath);

    if(!mapModel.hasStartPositions())
    {
        QMessageBox::critical(0, tr("Couldn't add a map to the start maps..."),
                              tr("The map %1 cannot be added to the start maps\nbecause it doesn't have any start positions on the map.").arg(chosenPath));
        return false;
    }

    if(chosenPath.isEmpty())
    {
        return true;
    }

    for(int i = 0; i < this->chosenListModel->rowCount(); ++i)
    {
        if(this->chosenListModel->item(i)->text() == chosenPath)
        {
            return true;
        }
    }

    this->chosenListModel->appendRow(new QStandardItem(chosenPath));
    this->chosenListModel->sort(0);

    return true;
}
