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

#include "ReplyToRequestForMap.h"

ReplyToRequestForMap::ReplyToRequestForMap(unsigned int playerID, QObject *parent)
    : ServerCommand(playerID, parent)
{
    this->setObjectName("ReplyToRequestForMap");
}

bool ReplyToRequestForMap::execute()
{
    QString localMapPath;

    this->networkModel->receiveData(localMapPath, this->playerID);

    MapModel *requestedMap = this->gameModel->refPreloadedMap(localMapPath);

    if(!requestedMap)
    {
        qDebug(QString("Requested map not preloaded. Requested Map was: %1").arg(localMapPath).toStdString().c_str());
        return false;
    }

    this->networkModel->sendData(SEND_SPECIFIC_MAP, this->playerID);
    this->networkModel->sendData(*requestedMap, this->playerID);

    this->gameModel->refPlayerModel(this->playerID)->setPlayerMapPath(localMapPath);

    return true;
}
