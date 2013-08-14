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

#include "PreloadWorld.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

#include "Common/FileNameConventions.h"
#include "Common/Common.h"

PreloadWorld::PreloadWorld(QObject *parent)
    : GameCommand(parent), fileManager(parent)
{
    this->setObjectName("PreloadWorld");
}

bool PreloadWorld::execute()
{
    QDir worldDir(QDir::current());
    if(!worldDir.cd(PIDGIRL::WORLD_FOLDER_NAME))
    {
        worldDir.mkdir(PIDGIRL::WORLD_FOLDER_NAME);
        worldDir.cd(PIDGIRL::WORLD_FOLDER_NAME);
    }

    QString worldFilePath = QFileDialog::getOpenFileName
            (
                0,
                tr("Choose a New World to play in..."),
                worldDir.absolutePath(),
                tr("PIDGIRL World Files (*").append(PIDGIRL::WORLD_SUFFIX).append(")")
            );

    if(worldFilePath.isEmpty())
    {
        PIDGIRL::writeLogFail("No file was specified. The string where the path should've been was empty.");
        return false;
    }

    this->worldModel->setWorldFileInfo(QFileInfo(worldFilePath));

    if(!this->fileManager.deserialize(this->worldModel, this->worldModel->refWorldFileInfo()->absoluteFilePath()))
    {
        QMessageBox::critical(0, tr("Failed to load a world..."), tr("Loading a world has failed."));
        PIDGIRL::writeLogFail("The loading process of the world failed.");
        return false;
    }

    return true;
}
