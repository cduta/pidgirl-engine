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

#include "LoadMap.h"

#include <QMessageBox>

#include "Common/Common.h"
#include "Command/Backend/Editor/Map/AskForSaveMap.h"

LoadMap::LoadMap(const QString &path, bool ask, QObject *parent)
    : NotUndoable(true, parent), fileManager(parent)
{
    this->setObjectName("LoadMap");
    this->path = path;
    this->ask = ask;
}

bool LoadMap::execute()
{
    if(!QFileInfo(this->path).isDir())
    {
        if(this->ask && !this->processor->execute(new AskForSaveMap()))
        {
            return false;
        }

        PIDGIRL::writeLog("Loading map");
    }
    else
    {
        return true;
    }

    if(!this->fileManager.deserialize(this->mapModel, this->path))
    {
        QMessageBox::critical(0, tr("Failed to load a map..."), tr("Loading a map has failed."));
        PIDGIRL::writeLogFail("The loading process of the map failed.");
        return false;
    }

    this->undoRedo->setSavedStates();

    PIDGIRL::writeLogDone();

    return true;
}
