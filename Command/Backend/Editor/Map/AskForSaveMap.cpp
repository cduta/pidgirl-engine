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

#include "AskForSaveMap.h"

#include "Command/Backend/Editor/World/SaveMap.h"

AskForSaveMap::AskForSaveMap(QObject *parent)
    : NotUndoable(false, parent)
{
    this->setObjectName("AskForSaveMap");
}

bool AskForSaveMap::execute()
{
    if(!this->undoRedo->hasOnlySavedMapChanges())
    {
        this->yncDialog.showDialog(tr("Save map changes?"), tr("There are unsaved changes for this map.\nDo you want to save?"));

        if(this->yncDialog.getButtonClicked() == YesNoCancelDialog::YES_BUTTON)
        {
            return this->processor->execute(new SaveMap());
        }
        else if(this->yncDialog.getButtonClicked() == YesNoCancelDialog::CANCEL_BUTTON)
        {
            return false;
        }
    }

    return true;
}
