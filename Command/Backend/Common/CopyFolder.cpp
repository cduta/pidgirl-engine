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

#include "CopyFolder.h"

#include <iostream>

CopyFolder::CopyFolder(const QDir &from, const QDir &to, QObject *parent)
    : CommonCommand(parent), from(from), to(to)
{
    this->setObjectName("CopyFolder");
}

bool CopyFolder::execute()
{
    QList< QPair< QFileInfoList, QDir> > toBeCopied;
    toBeCopied.append(QPair<QFileInfoList, QDir>(this->from.entryInfoList(), this->to));

    try
    {
        while(!toBeCopied.isEmpty())
        {
            QPair< QFileInfoList, QDir > next = toBeCopied.takeFirst();
            toBeCopied.append(this->copy(next));
        }
    }
    catch(char const *error)
    {
        std::cout << error << std::endl;
        return false;
    }

    return true;
}

QList<QPair<QFileInfoList, QDir> > CopyFolder::copy(QPair<QFileInfoList, QDir> next)
{
    QList<QPair<QFileInfoList, QDir> > rest;

    QFileInfoList entries = next.first;
    QDir targetDir = next.second;

    for(int i = 2; i < entries.size(); ++i)
    {
        QFileInfo entry = entries[i];

        if(entry.isDir())
        {
            QDir nextDir(targetDir);
            targetDir.mkdir(entry.fileName());
            nextDir.cd(entry.fileName());

            rest.append(QPair<QFileInfoList, QDir>(QDir(entry.absoluteFilePath()).entryInfoList(), nextDir));
        }
        else
        {
            if(!QFile::copy(entry.absoluteFilePath(),
                            QFileInfo(targetDir, entry.fileName()).absoluteFilePath()))
            {
                throw "ERROR: Current game folder couldn't be created.";
            }
        }
    }

    return rest;
}

