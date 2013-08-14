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

#ifndef COPY_FOLDER_H
#define COPY_FOLDER_H

#include <QDir>
#include <QList>
#include <QPair>
#include <QFileInfoList>

#include "Command/Backend/Common/CommonCommand.h"

/** \addtogroup Commands
  * \{
  * \class CopyFolder
  *
  * \brief Copy a folder recursively to another location.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class CopyFolder : public CommonCommand
{
    Q_OBJECT

private:
    QDir from;  ///< The directory from which to copy the folder.
    QDir to;    ///< The directory to which the folder will be copied to.

public:
    CopyFolder(const QDir &from, const QDir &to, QObject *parent = 0);

    virtual bool execute();

private:
    /**
     * @brief The actual copy function.
     * @param next Represents the current entries in a directory over which to find new files and folders.
     * @return A list of folders found in the current entries which need to be looked over as well.
     */
    QList<QPair<QFileInfoList, QDir> > copy(QPair<QFileInfoList, QDir> next);
};

#endif // COPY_FOLDER_H
