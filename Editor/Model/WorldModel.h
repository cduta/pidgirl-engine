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

#ifndef WORLD_MODEL_H
#define WORLD_MODEL_H

#include <QFileSystemModel>
#include <QString>
#include <QFile>
#include <QDataStream>

#include "Editor/Model/LocalFilePaths.h"
#include "Common/Serialize.h"
#include "Object/ObjectID.h"

/** \addtogroup Model
  * \{
  * \class WorldModel
  *
  * \brief Represents the world and all of its settings.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class WorldModel : public QFileSystemModel, public Serialize
{
    Q_OBJECT

signals:
    void fileChanged();

private:
    QFileInfo       worldFileInfo;  ///< Information about the world file.
    LocalFilePaths  startMaps;      ///< The list of starting maps.
    ObjectID        objectID;       ///< Information about the next possible ObjectIDs.

public:
    explicit WorldModel(QObject *parent = 0);

public:
    // Set-Methods
    void setWorldFileInfo(const QFileInfo &worldFileInfo);
    void setStartMaps(const LocalFilePaths &startMaps);
    void setStartMaps(const QVector< QString > &pathVector);
    // Get-Methods
    QVector<QString> getStartMapWorldPaths() const;
    QString localMapPathToAbsoluteMapPath(const QString &localMapPath);
    QString absoluteMapPathToLocalMapPath(const QString &absoluteMapPath);
    // Ref-Methods
    QFileInfo *refWorldFileInfo();
    ObjectID *refObjectID();

public:
    // Serialize
    virtual void serialize(QIODevice *device) const;
    void serialize(QDataStream &stream) const;
    virtual void deserialize(QIODevice *device);
    void deserialize(QDataStream &stream);
};

#endif // WORLD_MODEL_H
