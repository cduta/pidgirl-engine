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

#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <QIODevice>
#include <QFileInfo>

/** \addtogroup Common
  * \{
  * \class Serialize
  *
  * \brief Interface for serializable classes.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class Serialize
{
private:
    QFileInfo fileInfo; ///< The file information for serializable classes.

public:
    Serialize();

    virtual void serialize(QIODevice *device) const = 0;
    virtual void deserialize(QIODevice *device) = 0;

    void resetFileInfo();

    // Get-Methods
    QFileInfo getFileInfo() const;

    // Set-Methods
    void setFileInfo(const QFileInfo &fileInfo);
    void setFileInfo(const QString &fileInfo);
};

#endif // SERIALIZE_H
