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

#include "ApplyMapGeometryChanges.h"

#include <QMessageBox>
#include "Common/Common.h"

ApplyMapGeometryChanges::ApplyMapGeometryChanges(int horizontalNewValue, int horizontalDirection, int verticalNewValue, int verticalDirection, int maxHeightNewValue, int maxHeightDirection, QObject *parent)
    : NotUndoable(true, parent)
{
    this->setObjectName("ApplyMapGeometryChanges");

    this->horizontalNewValue = horizontalNewValue;
    this->horizontalDirection = MapModel::Side(horizontalDirection);
    this->verticalNewValue = verticalNewValue;
    this->verticalDirection = MapModel::Side(verticalDirection);
    this->maxHeightNewValue = maxHeightNewValue;
    this->maxHeightDirection = MapModel::Side(maxHeightDirection);
}

bool ApplyMapGeometryChanges::execute()
{
    PIDGIRL::writeLog("Applying property changes to map");

    QString standardErrorTitle = tr("Applying property changes to map...");
    bool commandSuccess = true;
    QString error = "";

    this->undoRedo->setOnlySavedMapChanges(false);

    if(!this->applyGeometryChanges())
    {
        QMessageBox::critical(0, standardErrorTitle, tr("Couldn't apply changes to map geometry."));
        error.append("Applying changes to the maps geometry failed.\n");
        commandSuccess = false;
    }

    if(!commandSuccess)
    {
        PIDGIRL::writeLogFail(error);
        return false;
    }

    PIDGIRL::writeLogDone();

    return true;
}

bool ApplyMapGeometryChanges::applyGeometryChanges()
{
    this->mapModel->resizeStackModelGrid(this->horizontalNewValue, this->horizontalDirection,
                                         this->verticalNewValue, this->verticalDirection,
                                         this->maxHeightNewValue, this->maxHeightDirection);

    return true;
}


