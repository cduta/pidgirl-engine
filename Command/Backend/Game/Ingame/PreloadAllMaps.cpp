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

#include "PreloadAllMaps.h"

#include <QDir>
#include <QMessageBox>
#include <QFileInfoList>
#include <QList>
#include <QFile>
#include <QFileDialog>

#include "Common/Common.h"
#include "Common/FileNameConventions.h"

PreloadAllMaps::PreloadAllMaps(QObject *parent)
    : GameCommand(parent)
{
    this->setObjectName("PreloadAllMaps");
}

bool PreloadAllMaps::execute()
{
    PIDGIRL::writeLog("Preloading Maps");

    QList<QFileInfoList> toBeCopied;
    toBeCopied.append(this->worldModel->refWorldFileInfo()->dir().entryInfoList());

    try
    {
        while(!toBeCopied.isEmpty())
        {
            QFileInfoList next = toBeCopied.takeFirst();
            toBeCopied.append(this->preload(next));
        }
    }
    catch(char const *error)
    {
        qDebug(error);
        PIDGIRL::writeLogFail();
        return false;
    }

    PIDGIRL::writeLogDone();
    return true;
}

QList<QFileInfoList> PreloadAllMaps::preload(QFileInfoList entries)
{
    QList<QFileInfoList> rest;
    MapModel *newMap;

    for(int i = 2; i < entries.size(); ++i)
    {
        QFileInfo entry = entries[i];

        if(entry.isDir())
        {
            rest.append(QDir(entry.absoluteFilePath()).entryInfoList());
        }
        else
        {
            if(entry.fileName().endsWith(PIDGIRL::MAP_SUFFIX))
            {
                newMap = new MapModel(this);
                PIDGIRL::writeLog(QString("  Loading %1").arg(entry.fileName()));
                if(!this->fileManager.deserialize(newMap, entry.absoluteFilePath()))
                {
                    PIDGIRL::writeLogFail();
                    throw "  ERROR: The map could not be loaded.";
                }
                PIDGIRL::writeLogDone();

                this->gameModel->addtoPreloadedMaps(this->worldModel->absoluteMapPathToLocalMapPath(entry.absoluteFilePath()), newMap);
            }
        }
    }

    return rest;
}

