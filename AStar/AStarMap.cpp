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
#include "AStarMap.h"

#include <QSet>

#include <math.h>
#include <iostream>
#include <limits>

AStarMap::AStarMap(){}

AStarMap::~AStarMap()
{
    for(int x = 0; x < this->map.size(); ++x)
    {
        for(int y = 0; y < this->map[x].size(); ++y)
        {
            delete (this->map[x][y]);
        }
    }
}

void AStarMap::fromMapModel(MapModel *mapModel)
{
    this->map.resize(mapModel->getHSquareCount());
    for(int x = 0; x < this->map.size(); ++x)
    {
        this->map[x].resize(mapModel->getVSquareCount());
        for(int y = 0; y < this->map[x].size(); ++y)
        {
            this->map[x][y] = new AStarMapEntry(mapModel->refStackModel(x,y));
        }
    }

    return;
}

bool AStarMap::calculatePath(const QPoint &from, const QPoint &to)
{
    int n = 0;
    QSet<AStarMapEntry *> closedSet;
    QSet<AStarMapEntry *> openSet;
    AStarMapEntry *startEntry = this->refEntry(from);
    AStarMapEntry *endEntry = this->refEntry(to);
    startEntry->setG(0.0);
    startEntry->calculateF(startEntry, endEntry);
    openSet.insert(startEntry);

//    std::cout << "Start: (" << startEntry->getPosition().x() << "," << startEntry->getPosition().y() << ")" << std::endl;
//    std::cout << "End  : (" << endEntry->getPosition().x() << "," << endEntry->getPosition().y() << ")" << std::endl;

    while(!openSet.isEmpty())
    {
        ++n;
        AStarMapEntry *current = openSet.values().at(0);
        for(int i = 0; i < openSet.size(); ++i)
        {
            AStarMapEntry *entry = openSet.values().at(i);
            if(entry->getF() < current->getF())
            {
                current = entry;
            }
        }

        //std::cout << n << ".: (" << current->getPosition().x() << "," << current->getPosition().y() << ")" << std::endl;

        if(current == endEntry)
        {
            this->retracePath(startEntry, endEntry);
            return true;
        }

        openSet.remove(current);
        closedSet.insert(current);

        QVector<AStarMapEntry *> currentNeighbors = this->getPossibleNeighborsOf(current);
        for(int i = 0; i < currentNeighbors.size(); ++i)
        {
            AStarMapEntry *neighbor = currentNeighbors[i];
            if(!closedSet.contains(neighbor))
            {
                int tentativeG;

                // Check for diagonal positioning.
                if(current->getPosition().x() != neighbor->getPosition().x() &&
                   current->getPosition().y() != neighbor->getPosition().y())
                {
                    tentativeG = current->getG() + (neighbor->getWeight()*M_SQRT2);
                }
                else
                {
                    tentativeG = current->getG() + neighbor->getWeight();
                }

                if(!openSet.contains(neighbor) || neighbor->getG() == std::numeric_limits<double>::infinity() || tentativeG < neighbor->getG())
                {
                    openSet.insert(neighbor);
                    neighbor->setCameFrom(current);
                    neighbor->setG(tentativeG);
                    neighbor->calculateF(startEntry, endEntry);
                }
            }
        }

    }

    return false;
}

QVector<AStarMapEntry *> AStarMap::getPossibleNeighborsOf(AStarMapEntry *entry)
{
    QVector<AStarMapEntry *> result;
    int currentX = entry->getPosition().x();
    int currentY = entry->getPosition().y();

    for(int dx = -1; dx <= 1; ++dx)
    {
        for(int dy = -1; dy <= 1; ++dy)
        {
            if(dx != 0 || dy != 0)
            {
                int x = currentX + dx;
                int y = currentY + dy;
                if(x >= 0 && x < this->getMapWidth() &&
                   y >= 0 && y < this->getMapHeight() &&
                   !this->refEntry(x,y)->hasInfinityWeight())
                {
                    result.append(this->refEntry(x,y));
                }
            }
        }
    }

    return result;
}

void AStarMap::retracePath(AStarMapEntry *startEntry, AStarMapEntry *endEntry)
{
    AStarMapEntry *current = endEntry;

    while(current != startEntry)
    {
        this->path.prepend(*current);
        current = current->refCameFrom();
    }

    this->path.prepend(*current);

    return;
}

QVector< AStarMapEntry > AStarMap::getPath() const
{
    return this->path;
}

int AStarMap::getMapWidth() const
{
    return this->map.size();
}

int AStarMap::getMapHeight() const
{
    int result;

    if(this->map.isEmpty())
    {
        result = 0;
    }
    else
    {
        result = this->map[0].size();
    }

    return result;
}

AStarMapEntry *AStarMap::refEntry(const QPoint &position) const
{
    return this->refEntry(position.x(), position.y());
}

AStarMapEntry *AStarMap::refEntry(int x, int y) const
{
    return this->map[x][y];
}




