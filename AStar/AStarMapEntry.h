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
#ifndef A_STAR_MAP_ENTRY_H
#define A_STAR_MAP_ENTRY_H

#include "MainView/Model/StackModel.h"

#include <QHash>

#include "math.h"
#include <limits>

/** \addtogroup AStar
  * \{
  * \class FindPath
  *
  * \brief Creates a path that shows how to get from one stack to another.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class AStarMapEntry
{
private:
    double weight;              ///< The weight for the given map entry.
    QPoint position;            ///< The current position.
    double g;                   ///< The shortest distance to the start.
    double f;                   ///< The shortest distance calculated with the heuristical distance from start to end.
    AStarMapEntry *cameFrom;    ///< The entry where the shortest path came from.

public:
    AStarMapEntry();
    AStarMapEntry(StackModel *stackModel);
    AStarMapEntry(const QPoint &position);
    AStarMapEntry(const AStarMapEntry &other);

    /**
      * \brief Create a AStarMapEntry ouf of a Stack Model.
      * \param stackModel The StackModel which is used to create the AStarMapEntry.
      */
    void fromStackModel(StackModel *stackModel);

private:
    /**
      * \brief Create a copy of another AStarMapEntry.
      * \param other The AStarMapEntry to be copied.
      */
    void copy(const AStarMapEntry &other);

    /**
      * \brief Initialized the AStarMapEntry.
      * \param weight The initial weight.
      * \param position The initial position.
      * \param g Distance to start is initialized as -1 (Infinity).
      * \param h Heuristical distance to end is initialized as -1 (Infinity).
      */
    void init(double weight, const QPoint &position, double f = std::numeric_limits<double>::infinity(), double g = std::numeric_limits<double>::infinity());

public:

    /**
      * \brief Calculate heuristical distance to the end.
      * \param endEntry The end entry where to heuristically determine the distance.
      */
    double heuristicalDistanceTo(AStarMapEntry *startEntry, AStarMapEntry *endEntry);

    /**
      * \brief Calculate heuristical distance to the end from the start.
      * \param endEntry The end entry where to heuristically determine the distance.
      */
    void calculateF(AStarMapEntry *startEntry, AStarMapEntry *endEntry);

public:
    // Get-Methods
    double getWeight() const;
    bool hasInfinityWeight() const;
    QPoint getPosition() const;
    double getG() const;
    double getF() const;
    // Set-Methods
    void setWeight(double weight);
    void setWeightToInfinity();
    void setG(double g);
    void setF(double f);
    void setCameFrom(AStarMapEntry *cameFrom);
    // Ref-Methods
    AStarMapEntry *refCameFrom() const;

public:
    AStarMapEntry &operator=(const AStarMapEntry &other);
    bool operator ==(const AStarMapEntry &other) const;
    bool operator !=(const AStarMapEntry &other) const;
};

#endif // A_STAR_MAP_ENTRY_H
