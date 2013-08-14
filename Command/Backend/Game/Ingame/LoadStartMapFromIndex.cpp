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

#include "LoadStartMapFromIndex.h"

#include <QMessageBox>

#include "Common/Common.h"

LoadStartMapFromIndex::LoadStartMapFromIndex(int startMapIndex, QObject *parent)
    : GameCommand(parent), startMapIndex(startMapIndex)
{}

bool LoadStartMapFromIndex::execute()
{
    if(this->startMapIndex < 0 || this->startMapIndex > this->worldModel->getStartMapWorldPaths().size())
    {
        qDebug("Load Random Map!");
        PIDGIRL::newSeed();
        this->startMapIndex = qrand()%this->worldModel->getStartMapWorldPaths().size();
    }

    return this->gameModel->loadMap(this->worldModel->getStartMapWorldPaths().at(this->startMapIndex));
}


