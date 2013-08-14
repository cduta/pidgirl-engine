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

#ifndef A_STAR_MAP_H
#define A_STAR_MAP_H

#include <QVector>

#include "MainView/Model/MapModel.h"
#include "AStar/AStarMapEntry.h"

/** \addtogroup AStar
  * \{
  * \class AStarMap
  *
  * \brief The representation of the map for the A*-Algorithm.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class AStarMap
{
    QVector< QVector <AStarMapEntry *> > map; ///< The weighted map over which to calculate a path from given points.
    QVector< AStarMapEntry > path; ///< The found path.
public:
    AStarMap();
    ~AStarMap();

    /**
      * @brief Creates a AStarMap from a map model.
      * @param mapModel The map model used to create the AStarMap.
      */
    void fromMapModel(MapModel *mapModel);

    /**
      * @brief Calculate the best path from a point to another.
      * @param from From where to start.
      * @param to Where to go.
      * @return True, if a path was successfully created.
      */
    bool calculatePath(const QPoint &from, const QPoint &to);

private:
    /**
     * @brief Get a list of neighboring entries.
     * @param entry The entry in the middle of those neighmoring it.
     * @return A list of neighboring entries.
     */
    QVector< AStarMapEntry *> getPossibleNeighborsOf(AStarMapEntry *entry);

    /**
     * @brief Retraces calculated path from end to start.
     * @param startEntry Where to trace to.
     * @param endEntry Where to start tracing.
     */
    void retracePath(AStarMapEntry *startEntry, AStarMapEntry *endEntry);

public:
    // Get-Methods
    QVector< AStarMapEntry > getPath() const;
    int getMapWidth() const;
    int getMapHeight() const;

    // Ref-Methods
    AStarMapEntry *refEntry(const QPoint &position) const;
    AStarMapEntry *refEntry(int x, int y) const;
};

#endif // A_STAR_MAP_H
