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

#include "ApplyWorldPropertiesChanges.h"

#include <QMessageBox>

#include <Common/Common.h>

ApplyWorldPropertiesChanges::ApplyWorldPropertiesChanges(QStandardItemModel *chosenListModel, QObject *parent)
    : NotUndoable(false, parent)
{
    this->setObjectName("ApplyWorldProertiesChanges");
    this->chosenListModel = chosenListModel;
}

bool ApplyWorldPropertiesChanges::execute()
{
    PIDGIRL::writeLog("Applying property changes to world");

    const QString standardErrorTitle = tr("Applying world changes failed...");
    bool commandSuccess = true;
    QString error = "";

    this->undoRedo->setOnlySavedWorldChanges(false);

    if(!this->applyChosenStarterMaps())
    {
        QMessageBox::critical(0, standardErrorTitle, tr("Couldn't apply changes to starter maps list."));
        error.append("Applying the changes to the starter maps failed.\n");
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

bool ApplyWorldPropertiesChanges::applyChosenStarterMaps()
{
    QVector<QString> starterMapsPaths;

    for(int i = 0; i < this->chosenListModel->rowCount(); ++i)
    {
        starterMapsPaths.append(this->chosenListModel->item(i)->text());
    }

    this->worldModel->setStartMaps(starterMapsPaths);

    return true;
}

