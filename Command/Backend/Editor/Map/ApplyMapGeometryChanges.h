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

#ifndef APPLY_MAP_GEOMETRY_CHANGES_H
#define APPLY_MAP_GEOMETRY_CHANGES_H

#include "Command/Backend/NotUndoable.h"

/** \addtogroup Commands
  * \{
  * \class ApplyMapGeometryChanges
  *
  * \brief Apply the geometrical changes to the currently loaded map model.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ApplyMapGeometryChanges : public NotUndoable
{
    Q_OBJECT
private:
    int             horizontalNewValue;     ///< Horizontal new value.
    MapModel::Side  horizontalDirection;    ///< Horizontal direction in which to apply the new value.
    int             verticalNewValue;       ///< Vertical new value.
    MapModel::Side  verticalDirection;      ///< Vetical direction in which to apply the new value.
    int             maxHeightNewValue;      ///< Max Height new value.
    MapModel::Side  maxHeightDirection;     ///< Max Height direction in which to apply the new value.

public:
    ApplyMapGeometryChanges(int horizontalNewValue, int horizontalDirection,
                            int verticalNewValue, int verticalDirection,
                            int maxHeightNewValue, int maxHeightDirection,
                            QObject *parent = 0);

    virtual bool execute();

private:
    /**
     * @brief Apply the geometry changes to the current map.
     * @return True, if changes were applied. Otherwise, false.
     */
    bool applyGeometryChanges();
};

#endif // APPLY_MAP_GEOMETRY_CHANGES_H
