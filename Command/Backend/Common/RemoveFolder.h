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

#ifndef REMOVE_FOLDER_H
#define REMOVE_FOLDER_H

#include <QtCore/QDir>
#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QFileInfoList>

#include "Command/Backend/Common/CommonCommand.h"

/** \addtogroup Commands
  * \{
  * \class RemoveFolder
  *
  * \brief Remove the a folder recursively.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class RemoveFolder : public CommonCommand
{
    Q_OBJECT
private:
    QFileInfo folder; ///< The folder to be recursively removed.

public:
    RemoveFolder(const QFileInfo &folder, QObject *parent = 0);

    virtual bool execute();

private:
    /**
      * @brief Remove directories recursive.
      * @param next The next directory to go through and queck for new directories to delete.
      */
    void removeDirRecursive(const QDir &next);

    /**
      * @brief Remove an empty directory.
      * @param target The directory that should be empty.
      */
    void removeEmpty(const QDir &target);
};

#endif // REMOVE_FOLDER_H
