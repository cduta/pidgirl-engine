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

#include "SaveWorldAs.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"

SaveWorldAs::SaveWorldAs(QObject *parent)
    : NotUndoable(true, parent), fileManager(parent)
{
    this->setObjectName("SaveWorldAs");
}

bool SaveWorldAs::execute()
{
    PIDGIRL::writeLog("Save World As");

    QDir worldDir(QDir::current());
    worldDir.mkdir(PIDGIRL::WORLD_FOLDER_NAME);
    worldDir.cd(PIDGIRL::WORLD_FOLDER_NAME);

    QString fileName = QFileDialog::getSaveFileName
            (
                0,
                tr("Save World As..."),
                worldDir.absolutePath(),
                tr("PIDGIRL World Files (*").append(PIDGIRL::WORLD_SUFFIX).append(")")
            );

    if(fileName.isEmpty())
    {
        PIDGIRL::writeLogFail("No file was specified. The string, where the path should've been, was empty.");
        return false;
    }

    if(!fileName.endsWith(PIDGIRL::WORLD_SUFFIX))
    {
        fileName.append(PIDGIRL::WORLD_SUFFIX);
    }

    this->worldModel->setWorldFileInfo(QFileInfo(fileName));

    if(this->worldModel->getStartMapWorldPaths().empty())
    {
        QMessageBox::critical(0, tr("Couldn't save the world..."),
                              tr("The world can only be saved, if it has start maps.\nOtherwise no player can be spawned."));
        PIDGIRL::writeLogFail("The saving process of the world failed.");
        return false;
    }

    if(!this->fileManager.serialize(this->worldModel, this->worldModel->refWorldFileInfo()->absoluteFilePath()))
    {
        QMessageBox::critical(0, tr("Couldn't save the world..."), tr("Saving the world has failed."));
        PIDGIRL::writeLogFail("The saving process of the world failed.");
        return false;
    }

    this->undoRedo->setOnlySavedWorldChanges(true);

    PIDGIRL::writeLogDone();
    return true;
}
