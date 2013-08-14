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

#include "LocalFilePaths.h"

LocalFilePaths::LocalFilePaths()
    : QVector()
{
}

LocalFilePaths::LocalFilePaths(int size)
    : QVector<QString>(size)
{
}

LocalFilePaths::LocalFilePaths(const QString &localFilePath)
    : QVector<QString>(1, localFilePath)
{
}

LocalFilePaths::LocalFilePaths(const QVector<QString> &v)
    : QVector<QString>(v)
{
}

QVector<QString> LocalFilePaths::convertToFileNameVector()
{
    QVector<QString> filePathVector;

    for(int i = 0; i < this->size(); ++i)
    {
        filePathVector.append(this->convertToFileName(this->at(i)));
    }

    return filePathVector;
}

QString LocalFilePaths::convertToFileName(const QString &localFilePath)
{
    QString fileName;

    for(int i = localFilePath.size() - 1; i >= 0 && localFilePath[i] != '/'; --i)
    {
        fileName.append(localFilePath[i]);
    }

    return fileName;
}
