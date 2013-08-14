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

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <QFile>
#include <QFileInfo>
#include <QObject>

#include "Common/Serialize.h"

/** \addtogroup Common
  * \{
  * \class FileManager
  *
  * \brief Manages files to open and close accordingly and other things.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class FileManager : public QObject
{

private:
    QFile file; ///< The file which is managed.

public:
    FileManager(QObject *parent = 0);

    /**
      * \brief Check if file exists.
      * \returns True, if exists.
      */
    bool fileExists();

    /**
      * \brief Remove file if it exists.
      * \returns True, if successful.
      */
    bool fileRemove();

    /**
      * \brief Open a handle to the file.
      * \returns True, if successful.
      */
    bool fileOpen(QIODevice::OpenModeFlag openFlag);

    /**
      * \brief Close a handle to the file.
      * \returns True, if successful.
      */
    bool fileClose();

    /**
      * \brief Set a new file path as a target.
      * \param path The path of the target.
      */
    void setFilePath(const QString &path);

    /**
      * \brief Serialize datatype to path.
      * \param serializable The datatype to be serialized.
      * \param path The path where to serialize.
      */
    bool serialize(Serialize *serializable, const QString &path);

    /**
      * \brief Serialize datatype to path.
      * \param serializable The datatype to be deserialized.
      * \param path The path from where to deserialize.
      */
    bool deserialize(Serialize *serializable, const QString &path);

public:
    // Ref-Methods
    QFile *refFile();
};

#endif // FILE_MANAGER_H
