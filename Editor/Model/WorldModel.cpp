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

#include "Editor/Model/WorldModel.h"

WorldModel::WorldModel(QObject *parent)
    : QFileSystemModel(parent)
{
}

void WorldModel::setWorldFileInfo(const QFileInfo &worldFileInfo)
{
    this->worldFileInfo = worldFileInfo;
    emit this->fileChanged();
    return;
}

void WorldModel::setStartMaps(const LocalFilePaths &startingMaps)
{
    this->startMaps = startingMaps;
    return;
}

void WorldModel::setStartMaps(const QVector<QString> &pathVector)
{
    this->startMaps = LocalFilePaths(pathVector);
    return;
}

QVector<QString> WorldModel::getStartMapWorldPaths() const
{
    return this->startMaps;
}

QString WorldModel::localMapPathToAbsoluteMapPath(const QString &localMapPath)
{
    return this->worldFileInfo.absoluteDir().absolutePath().append(localMapPath);
}

QString WorldModel::absoluteMapPathToLocalMapPath(const QString &absoluteMapPath)
{
    QString result = absoluteMapPath;
    return result.remove(0, this->worldFileInfo.absoluteDir().absolutePath().size());
}

QFileInfo *WorldModel::refWorldFileInfo()
{
    return &this->worldFileInfo;
}

ObjectID *WorldModel::refObjectID()
{
    return &this->objectID;
}

void WorldModel::serialize(QIODevice *device) const
{
    // At some point, compression with qCompression which uses zlib (LZ77, Huffman).
    // Usage only if one can predict good results. Before that, keep it plain text.

    QDataStream dataStream(device);
    this->serialize(dataStream);

    return;
}

void WorldModel::serialize(QDataStream &stream) const
{
    stream << this->getStartMapWorldPaths();

    this->objectID.serialize(stream);
    return;
}

void WorldModel::deserialize(QIODevice *device)
{
    QDataStream dataStream(device);
    this->deserialize(dataStream);

    return;
}

void WorldModel::deserialize(QDataStream &stream)
{
    QVector< QString > startingMaps;
    stream >> startingMaps;
    this->setStartMaps(startingMaps);

    this->objectID.deserialize(stream);
    return;
}

