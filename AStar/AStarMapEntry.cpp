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
#include "AStarMapEntry.h"

#include <iostream>

AStarMapEntry::AStarMapEntry()
{
    this->init(std::numeric_limits<double>::infinity(),QPoint(-1,-1));
}

AStarMapEntry::AStarMapEntry(StackModel *stackModel)
{
    this->fromStackModel(stackModel);
}

AStarMapEntry::AStarMapEntry(const QPoint &position)
{
    this->init(1.0,position);
}

AStarMapEntry::AStarMapEntry(const AStarMapEntry &other)
{
    this->copy(other);
}

void AStarMapEntry::fromStackModel(StackModel *stackModel)
{
    double weight;

    if(stackModel->refWall() || stackModel->refCharacter())
    {
        weight = std::numeric_limits<double>::infinity();
    }
    else
    {
        weight = 1.0;
    }

    this->init(weight, stackModel->getSquarePos());

    return;
}

void AStarMapEntry::copy(const AStarMapEntry &other)
{
    if(other.hasInfinityWeight())
    {
        this->setWeightToInfinity();
    }
    else
    {
        this->setWeight(other.getWeight());
    }

    this->init(other.getWeight(), other.getPosition());

    return;
}

void AStarMapEntry::init(double weight, const QPoint &position, double f, double g)
{
    this->setWeight(weight);
    this->position = position;
    this->setF(f);
    this->setG(g);
    this->cameFrom = 0;
    return;
}

double AStarMapEntry::heuristicalDistanceTo(AStarMapEntry *startEntry, AStarMapEntry *endEntry)
{
    double fromX = this->getPosition().x();
    double fromY = this->getPosition().y();
    double endX = endEntry->getPosition().x();
    double endY = endEntry->getPosition().y();
    double dX = fromX - endX;
    double dY = fromY - endY;
    double dSX = startEntry->getPosition().x() - endX;
    double dSY = startEntry->getPosition().y() - endY;
    double hDiagonal = fmin(fabs(dX), fabs(dY));
    double hStraight = fabs(dX) + fabs(dY);
    double cross = fabs((dX*dSY) - (dY*dSX));

    return (M_SQRT2 * hDiagonal) + (hStraight - 2.0*hDiagonal) + (cross * 0.001);
}

void AStarMapEntry::calculateF(AStarMapEntry *startEntry, AStarMapEntry *endEntry)
{
    this->setF(this->getG() + this->heuristicalDistanceTo(startEntry, endEntry));
    return;
}

double AStarMapEntry::getWeight() const
{
    return this->weight;
}

bool AStarMapEntry::hasInfinityWeight() const
{
    return this->weight == std::numeric_limits<double>::infinity();
}

QPoint AStarMapEntry::getPosition() const
{
    return this->position;
}

double AStarMapEntry::getF() const
{
    return this->f;
}

double AStarMapEntry::getG() const
{
    return this->g;
}

void AStarMapEntry::setWeight(double weight)
{
    if(weight < 0.0)
    {
        weight = 0.0;
    }
    this->weight = weight;
    return;
}

void AStarMapEntry::setWeightToInfinity()
{
    this->weight = std::numeric_limits<double>::infinity();
    return;
}

void AStarMapEntry::setF(double f)
{
    if(f < 0.0)
    {
        f = 0.0;
    }

    this->f = f;
    return;
}

void AStarMapEntry::setCameFrom(AStarMapEntry *cameFrom)
{
    this->cameFrom = cameFrom;
    return;
}

AStarMapEntry *AStarMapEntry::refCameFrom() const
{
    return this->cameFrom;
}

void AStarMapEntry::setG(double g)
{
    if(g < 0.0)
    {
        g = 0.0;
    }

    this->g = g;
    return;
}

AStarMapEntry &AStarMapEntry::operator =(const AStarMapEntry &other)
{
    this->copy(other);
    return *this;
}

bool AStarMapEntry::operator ==(const AStarMapEntry &other) const
{
    return this->position.x() == other.getPosition().x() &&
            this->position.y() == other.getPosition().y();
}

bool AStarMapEntry::operator !=(const AStarMapEntry &other) const
{
    return !((*this) == other);
}
