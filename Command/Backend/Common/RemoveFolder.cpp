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

#include "RemoveFolder.h"

#include <QtCore/QFile>

#include <iostream>

RemoveFolder::RemoveFolder(const QFileInfo &folder, QObject *parent)
    : CommonCommand(parent), folder(folder)
{
    this->setObjectName("RemoveFolder");
}

bool RemoveFolder::execute()
{
    if(!this->folder.exists())
    {
        return true;
    }

    if(!this->folder.isDir())
    {
        std::cout << "ERROR: The chosen entry to be deleted wasn't a folder." << std::endl;
        return false;
    }

    QDir targetFolder(this->folder.dir());
    targetFolder.cd(this->folder.fileName());

    try
    {
        if(targetFolder.exists())
        {
            this->removeDirRecursive(targetFolder);
            this->removeEmpty(targetFolder);
        }
    }
    catch(char const *error)
    {
        std::cout << error << std::endl;
        return false;
    }

    return true;
}

void RemoveFolder::removeDirRecursive(const QDir &next)
{    
    QList< QDir > rest;

    QFileInfoList entryList = next.entryInfoList();

    for(int i = 2; i < entryList.size(); ++i)
    {
        QFileInfo entry(entryList[i]);

        if(entry.exists())
        {
            if(entry.isDir())
            {
                rest.append(QDir(entry.absoluteFilePath()));
            }
            else
            {
                QFile file(entry.absoluteFilePath());
                if(!file.remove())
                {
                    throw "ERROR: File couldn't be removed.";
                }
            }
        }
    }

    while(!rest.empty())
    {
        QDir nextDir = rest.takeFirst();

        if(nextDir.exists())
        {
            this->removeDirRecursive(nextDir);
            this->removeEmpty(nextDir);
        }
    }

    return;
}

void RemoveFolder::removeEmpty(const QDir &target)
{
    QDir upDir(target);
    upDir.cdUp();
    if(!upDir.rmdir(target.dirName()))
    {
        throw "ERROR: Directory couldn't be removed.";
    }
}

