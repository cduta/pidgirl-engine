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

#include "MainView/Model/MapModel.h"

#include <QDataStream>
#include <QDebug>

#include "Common/Common.h"
#include "Object/Character/Player.h"

#include <iostream>

MapModel::MapModel(QObject *parent)
    : QObject(parent)
{
    this->setObjectName("MapModel");
    this->firstTimeInit();
    this->initMapModel(PIDGIRL::STANDARD_HORIZONTAL_SQUARE_COUNT,
                       PIDGIRL::STANDARD_VERTICAL_SQUARE_COUNT,
                       PIDGIRL::STANDARD_HEIGHT,
                       PIDGIRL::STANDARD_GRID_LINE_SIZE);

}

MapModel::MapModel(int hSquareCount, int vSquareCount, int maxHeight, int gridLineSize, QObject *parent)
    : QObject(parent)
{
    this->setObjectName("MapModel");
    this->firstTimeInit();
    this->initMapModel(hSquareCount, vSquareCount, maxHeight, gridLineSize);
}

void MapModel::firstTimeInit()
{
    this->clipboardObject = 0;
    this->squareSizeZoomFactor = PIDGIRL::MIN_ZOOM_FACTOR;
}

void MapModel::initMapModel(int hSquareCount, int vSquareCount, int maxHeight, int gridLineSize)
{
    this->localMapPath = QString("");
    this->updateSquareSize();
    this->gridLineSize = gridLineSize;
    this->currentHeight = 0;
    this->startPositionStacks.clear();
    this->playerStacks.clear();
    this->clearPath();
    this->resetFileInfo();

    this->setHSquareCount(hSquareCount);
    this->setVSquareCount(vSquareCount);
    this->setMaxHeight(maxHeight);
    emit this->gridChanged();

    return;
}

void MapModel::resizeStackModelGrid(int newHSquareCount, MapModel::Side hDirection, int newVSquareCount, MapModel::Side vDirection, int newMaxHeight, MapModel::Side heightDirection)
{
    bool changed = false;
    if(newHSquareCount != this->getHSquareCount())
    {
        this->setHSquareCount(newHSquareCount, hDirection);
        changed = true;
    }

    if(newVSquareCount != this->getVSquareCount())
    {
        this->setVSquareCount(newVSquareCount, vDirection);
        changed = true;
    }

    if(newMaxHeight != this->getMaxHeight())
    {
        this->setMaxHeight(newMaxHeight, heightDirection);
        changed = true;
    }

    if(changed)
    {
        emit this->gridChanged();
    }

    return;
}

void MapModel::clearStackModelGrid()
{
    for(int x = 0; x < this->stackModelGrid.size(); ++x)
    {
        for(int y = 0; y < this->stackModelGrid[x].size(); ++y)
        {
            for(int z = 0; z < this->stackModelGrid[x][y].size(); ++z)
            {
                this->stackModelGrid[x][y][z]->removeAll();
            }
        }
    }

    return;
}

void MapModel::setNewStandardMap()
{
    this->clearStackModelGrid();

    this->initMapModel(PIDGIRL::STANDARD_HORIZONTAL_SQUARE_COUNT,
                       PIDGIRL::STANDARD_VERTICAL_SQUARE_COUNT,
                       PIDGIRL::STANDARD_HEIGHT,
                       PIDGIRL::STANDARD_GRID_LINE_SIZE);
    return;
}

void MapModel::correctPositionEntries()
{
    for(int x = 0; x < this->stackModelGrid.size(); ++x)
    {
        for(int y = 0; y < this->stackModelGrid[x].size(); ++y)
        {
            for(int z = 0; z < this->stackModelGrid[x][y].size(); ++z)
            {
                this->stackModelGrid[x][y][z]->setPosition(x,y,z);
            }
        }
    }

    return;
}

void MapModel::createStackModelAt(int x, int y, int z)
{
    this->stackModelGrid[x][y][z] = new StackModel(x,y,z, this);
    connect(this->stackModelGrid[x][y][z], SIGNAL(startPositionSet(StackModel*)), this, SLOT(addStartPositionStack(StackModel*)));
    connect(this->stackModelGrid[x][y][z], SIGNAL(startPositionRemoved(StackModel*)), this, SLOT(removeStartPositionStack(StackModel*)));
    connect(this->stackModelGrid[x][y][z], SIGNAL(playerSet(StackModel*)), this, SLOT(addPlayerStack(StackModel*)));
    connect(this->stackModelGrid[x][y][z], SIGNAL(playerRemoved(StackModel*)), this, SLOT(removePlayerStack(StackModel*)));
    return;
}

void MapModel::removeStackModelAt(int x, int y, int z)
{
    disconnect(this->stackModelGrid[x][y][z], SIGNAL(startPositionSet(StackModel*)), this, SLOT(addStartPositionStack(StackModel*)));
    disconnect(this->stackModelGrid[x][y][z], SIGNAL(startPositionRemoved(StackModel*)), this, SLOT(removeStartPositionStack(StackModel*)));
    disconnect(this->stackModelGrid[x][y][z], SIGNAL(playerSet(StackModel*)), this, SLOT(addPlayerStack(StackModel*)));
    disconnect(this->stackModelGrid[x][y][z], SIGNAL(playerRemoved(StackModel*)), this, SLOT(removePlayerStack(StackModel*)));
    this->stackModelGrid[x][y][z] = 0;
    return;
}

void MapModel::deleteStackModelAt(int x, int y, int z)
{
    this->stackModelGrid[x][y][z]->deleteLater();
    this->stackModelGrid[x][y][z] = 0;
    return;
}

void MapModel::removeHorizontalLeft(int amount)
{
    for(int i = 0; i < amount; ++i)
    {
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->deleteStackModelAt(i,y,z);
            }
        }
    }

    this->stackModelGrid.remove(0, amount);

    return;
}

void MapModel::removeHorizontalRight(int amount)
{
    for(int i = 0; i < amount; ++i)
    {
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->deleteStackModelAt(this->getHSquareCount() - i - 1,y,z);
            }
        }
    }

    this->stackModelGrid.remove(this->getHSquareCount() - amount, amount);

    return;
}

void MapModel::appendHorizontalLeft(int amount)
{
    QVector< StackModel *> height = QVector< StackModel *>(this->getMaxHeight());

    for(int i = 0; i < amount; ++i)
    {
        this->stackModelGrid.prepend(QVector< QVector< StackModel *> >(this->getVSquareCount()));
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            this->stackModelGrid[0][y] = height;
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->createStackModelAt(0,y,z);
            }
        }
    }

    return;
}

void MapModel::appendHorizontalRight(int amount)
{
    int oldSize = this->getHSquareCount();

    for(int i = 0; i < amount; ++i)
    {
        this->stackModelGrid.append(QVector< QVector< StackModel *> >(this->getVSquareCount()));
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            this->stackModelGrid[this->getHSquareCount() - 1][y].resize(this->getMaxHeight());
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->createStackModelAt(oldSize + i,y,z);
            }
        }
    }

    return;
}

void MapModel::setHSquareCount(int hSquareCount, MapModel::Side from)
{
    if(hSquareCount < PIDGIRL::MIN_HORIZONTAL_SQUARE_COUNT)
    {
        std::cout << "Error in setHSquareCount: " << hSquareCount << " was < " << PIDGIRL::MIN_HORIZONTAL_SQUARE_COUNT << "." << std::endl;
        hSquareCount = PIDGIRL::MIN_HORIZONTAL_SQUARE_COUNT;
    }

    if(hSquareCount > PIDGIRL::MAX_HORIZONTAL_SQUARE_COUNT)
    {
        std::cout << "Error in setHSquareCount: " << hSquareCount << " was > " << PIDGIRL::MAX_HORIZONTAL_SQUARE_COUNT << "." << std::endl;
        hSquareCount = PIDGIRL::MAX_HORIZONTAL_SQUARE_COUNT;
    }

    if(hSquareCount < this->getHSquareCount())
    {
        if(from == MapModel::Right)
        {
            this->removeHorizontalRight(this->getHSquareCount() - hSquareCount);
        }
        else
        {
            this->removeHorizontalLeft(this->getHSquareCount() - hSquareCount);
        }

        this->correctPositionEntries();
        emit this->horizontalSizeChanged();
    }
    else if(hSquareCount > this->getHSquareCount())
    {
        if(from == MapModel::Right)
        {
            this->appendHorizontalRight(hSquareCount - this->getHSquareCount());
        }
        else
        {
            this->appendHorizontalLeft(hSquareCount - this->getHSquareCount());
        }

        this->correctPositionEntries();
        emit this->horizontalSizeChanged();
    }

    return;
}

void MapModel::removeVerticalLeft(int amount)
{
    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int i = 0; i < amount; ++i)
        {
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->deleteStackModelAt(x,i,z);
            }
        }

        this->stackModelGrid[x].remove(0, amount);
    }

    return;
}

void MapModel::removeVerticalRight(int amount)
{
    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int i = 0; i < amount; ++i)
        {
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->deleteStackModelAt(x,this->stackModelGrid[x].size() - i - 1,z);
            }
        }

        this->stackModelGrid[x].remove(this->stackModelGrid[x].size() - amount, amount);
    }

    return;
}

void MapModel::appendVerticalLeft(int amount)
{
    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int i = 0; i < amount; ++i)
        {
            this->stackModelGrid[x].prepend(QVector< StackModel *>(this->getMaxHeight()));
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->createStackModelAt(x,0,z);
            }
        }
    }

    return;
}

void MapModel::appendVerticalRight(int amount)
{
    int oldSize = this->getVSquareCount();

    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int i = 0; i < amount; ++i)
        {
            this->stackModelGrid[x].append(QVector< StackModel *>(this->getMaxHeight()));
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->createStackModelAt(x,oldSize+i,z);
            }
        }
    }

    return;
}

void MapModel::setVSquareCount(int vSquareCount, MapModel::Side from)
{
    if(vSquareCount < PIDGIRL::MIN_VERTICAL_SQUARE_COUNT)
    {
        std::cout << "Error in setVSquareCount: " << vSquareCount << " was < " << PIDGIRL::MIN_VERTICAL_SQUARE_COUNT << "." << std::endl;
        vSquareCount = PIDGIRL::MIN_VERTICAL_SQUARE_COUNT;
    }

    if(vSquareCount > PIDGIRL::MAX_VERTICAL_SQUARE_COUNT)
    {
        std::cout << "Error in setVSquareCount: " << vSquareCount << " was > " << PIDGIRL::MAX_VERTICAL_SQUARE_COUNT << "." << std::endl;
        vSquareCount = PIDGIRL::MAX_VERTICAL_SQUARE_COUNT;
    }

    if(vSquareCount < this->getVSquareCount())
    {
        if(from == MapModel::Right)
        {
            this->removeVerticalRight(this->getVSquareCount() - vSquareCount);
        }
        else
        {
            this->removeVerticalLeft(this->getVSquareCount() - vSquareCount);
        }

        this->correctPositionEntries();
        emit this->verticalSizeChanged();
    }
    else if(vSquareCount > this->getVSquareCount())
    {
        if(from == MapModel::Right)
        {
            this->appendVerticalRight(vSquareCount - this->getVSquareCount());
        }
        else
        {
            this->appendVerticalLeft(vSquareCount - this->getVSquareCount());
        }

        this->correctPositionEntries();
        emit this->verticalSizeChanged();
    }

    return;
}

void MapModel::removeHeightLeft(int amount)
{
    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            for(int i = 0; i < amount; ++i)
            {
                this->deleteStackModelAt(x,y,0);
            }

            this->stackModelGrid[x][y].remove(0, amount);
        }
    }

    return;
}

void MapModel::removeHeightRight(int amount)
{
    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            for(int i = 0; i < amount; ++i)
            {
                this->deleteStackModelAt(x,y,this->stackModelGrid[x][y].size() - i - 1);
            }

            this->stackModelGrid[x][y].remove(this->stackModelGrid[x][y].size() - amount, amount);
        }
    }

    return;
}

void MapModel::appendHeightLeft(int amount)
{    
    int oldSize = this->getMaxHeight();

    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            for(int i = 0; i < amount; ++i)
            {
                this->stackModelGrid[x][y].append(0);
                this->createStackModelAt(x,y,oldSize+i);
            }
        }
    }

    return;
}

void MapModel::appendHeightRight(int amount)
{
    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            for(int i = 0; i < amount; ++i)
            {
                this->stackModelGrid[x][y].prepend(0);
                this->createStackModelAt(x,y,0);
            }
        }
    }

    return;
}

void MapModel::setMaxHeight(int maxHeight, MapModel::Side from)
{
    if(maxHeight < PIDGIRL::MIN_HEIGHT)
    {
        std::cout << "Error in setMaxHeight: " << maxHeight << " was < " << PIDGIRL::MIN_HEIGHT << "." << std::endl;
        maxHeight = PIDGIRL::MIN_HEIGHT;
    }

    if(maxHeight > PIDGIRL::MAX_HEIGHT)
    {
        std::cout << "Error in setMaxHeight: " << maxHeight << " was > " << PIDGIRL::MAX_HEIGHT << "." << std::endl;
        maxHeight = PIDGIRL::MAX_HEIGHT;
    }

    if(maxHeight < this->getMaxHeight())
    {
        if(from == MapModel::Right)
        {
            this->removeHeightRight(this->getMaxHeight() - maxHeight);
        }
        else
        {
            this->removeHeightLeft(this->getMaxHeight() - maxHeight);
        }

        this->correctPositionEntries();
        emit this->heightSizeChanged();
    }
    else if(maxHeight > this->getMaxHeight())
    {
        if(from == MapModel::Right)
        {
            this->appendHeightRight(maxHeight - this->getMaxHeight());
        }
        else
        {
            this->appendHeightLeft(maxHeight - this->getMaxHeight());
        }

        this->correctPositionEntries();
        emit this->heightSizeChanged();
    }

    if(this->getCurrentHeight() >= this->getMaxHeight())
    {
        this->setCurrentHeight(this->getMaxHeight() - 1);
    }

    return;
}

void MapModel::clearPath()
{
    for(int i = 0; i < this->currentPath.size(); ++i)
    {
        this->currentPath.at(i)->resetPathDirection();
    }

    this->currentPath.clear();
    emit this->mapPathChanged();
    return;
}

QString MapModel::getLocalMapPath() const
{
    return this->localMapPath;
}

int MapModel::getHSquareCount() const
{
    return this->stackModelGrid.size();
}

int MapModel::getVSquareCount() const
{
    int result = 0;

    if(!this->stackModelGrid.isEmpty())
    {
        result = this->stackModelGrid[0].size();
    }

    return result;
}

int MapModel::getSquareSizeZoomFactor() const
{
    return this->squareSizeZoomFactor;
}

int MapModel::getSquareSize() const
{
    return this->squareSize;
}

int MapModel::getGridLineSize() const
{
    return this->gridLineSize;
}

int MapModel::getMaxHeight() const
{
    int result = 0;

    if(!this->stackModelGrid.isEmpty())
    {
        if(!this->stackModelGrid[0].isEmpty())
        {
            result = this->stackModelGrid[0][0].size();
        }
    }

    return result;
}

int MapModel::getCurrentHeight() const
{
    return this->currentHeight;
}

QSize MapModel::getMapSize() const
{
    return QSize(this->getHSquareCount()*(this->squareSize + 1)+1,
                 this->getVSquareCount()*(this->squareSize + 1)+1);
}

QVector<StackModel *> MapModel::getCurrentPath() const
{
    return this->currentPath;
}

bool MapModel::hasStartPositions() const
{
    return !this->startPositionStacks.isEmpty();
}

void MapModel::setSquareSizeZoomFactor(int zoomFactor)
{
    if(zoomFactor < PIDGIRL::MIN_ZOOM_FACTOR)
    {
        std::cout << "Error in setSquareSizeZoomFactor: " << zoomFactor << " was < " << PIDGIRL::MIN_ZOOM_FACTOR << "." << std::endl;
        zoomFactor = PIDGIRL::MIN_ZOOM_FACTOR;
    }

    if(zoomFactor > PIDGIRL::MAX_ZOOM_FACTOR)
    {
        std::cout << "Error in setSquareSizeZoomFactor: " << zoomFactor << " was > " << PIDGIRL::MAX_ZOOM_FACTOR << "." << std::endl;
        zoomFactor = PIDGIRL::MAX_ZOOM_FACTOR;
    }

    this->squareSizeZoomFactor = zoomFactor;
    this->updateSquareSize();
    return;
}

void MapModel::updateSquareSize()
{
    this->squareSize = this->getSquareSizeZoomFactor()*PIDGIRL::MIN_SQUARE_SIZE;
    emit gridChanged();
    return;
}

void MapModel::setGridLineSize(int gridLineSize, bool willEmit)
{
    if(gridLineSize < PIDGIRL::MIN_GRID_LINE_SIZE)
    {
        std::cout << "Error in setGridLineSize: " << gridLineSize << " was < " << PIDGIRL::MIN_GRID_LINE_SIZE << "." << std::endl;
        gridLineSize = PIDGIRL::MIN_GRID_LINE_SIZE;
    }

    if(gridLineSize > PIDGIRL::MAX_GRID_LINE_SIZE)
    {
        std::cout << "Error in setGridLineSize: " << gridLineSize << " was > " << PIDGIRL::MAX_GRID_LINE_SIZE << "." << std::endl;
        gridLineSize = PIDGIRL::MAX_GRID_LINE_SIZE;
    }

    bool emitting = (this->gridLineSize != gridLineSize) && willEmit;
    this->gridLineSize = gridLineSize;

    if(emitting)
    {
        emit this->gridLineSizeChanged();
    }
    return;
}

void MapModel::addStartPositionStack(StackModel *startPositionStack)
{
    for(int i = 0; i < this->startPositionStacks.size(); ++i)
    {
        if(this->startPositionStacks[i] == startPositionStack)
        {
            return;
        }
    }

    /*qDebug(QString("Add Start Position Stack to the list for coordinates (%1,%2,%3)").arg(QString::number(startPositionStack->getSquarePos().x()),
                                                                                          QString::number(startPositionStack->getSquarePos().y()),
                                                                                          QString::number(startPositionStack->getHeight())).toStdString().c_str());
    */
    this->startPositionStacks.append(startPositionStack);

    return;
}

void MapModel::removeStartPositionStack(StackModel *startPositionStack)
{
    for(int i = 0; i < this->startPositionStacks.size(); ++i)
    {
        if(this->startPositionStacks[i] == startPositionStack)
        {
            this->startPositionStacks.remove(i);
            return;
        }
    }
    return;
}

void MapModel::addPlayerStack(StackModel *playerStacks)
{
    for(int i = 0; i < this->playerStacks.size(); ++i)
    {
        if(this->playerStacks[i] == playerStacks)
        {
            return;
        }
    }

    this->playerStacks.append(playerStacks);

    return;
}

void MapModel::removePlayerStack(StackModel *playerStack)
{
    for(int i = 0; i < this->playerStacks.size(); ++i)
    {
        if(this->playerStacks[i] == playerStack)
        {
            this->playerStacks.remove(i);
            return;
        }
    }
    return;
}

void MapModel::setLocalMapPath(const QString &localMapPath)
{
    this->localMapPath = localMapPath;
    return;
}

void MapModel::setCurrentHeight(int currentHeight)
{
    if(currentHeight < 0)
    {
        std::cout << "Error in setCurrentHeight: currentHeight was " << currentHeight << " < 0." << std::endl;
        currentHeight = 0;
    }

    if(currentHeight >= this->getMaxHeight())
    {
        std::cout << "Error in setCurrentHeight: currentHeight was " << currentHeight << " >= " << this->getMaxHeight() << "." << std::endl;
        currentHeight = this->getMaxHeight() - 1;
    }

    bool emitting = this->currentHeight != currentHeight;

    this->currentHeight = currentHeight;

    if(emitting)
    {
        emit gridChanged();
    }
    return;
}

void MapModel::setClipboardObject(ObjectBase *object)
{
    ObjectBase *oldObject = this->clipboardObject;
    this->clipboardObject = object;

    if(this->clipboardObject)
    {
        this->clipboardObject->setParent(this);
    }

    if(oldObject)
    {
        oldObject->deleteLater();
    }

    emit this->clipboardObjectSet();

    return;
}

void MapModel::setConvertedPath(QVector<AStarMapEntry> path)
{
    for(int i = 1; i < path.size(); ++i)
    {
        int dx = path[i-1].getPosition().x() - path[i].getPosition().x();
        int dy = path[i-1].getPosition().y() - path[i].getPosition().y();

        StackModel::PathIndication first;
        StackModel::PathIndication second;

        if(dy <= -1)
        {
            first = StackModel::S;
        }
        else if(dy == 0)
        {
            first = StackModel::NONE;
        }
        else if(dy >= 1)
        {
            first = StackModel::N;
        }

        if(dx <= -1)
        {
            second = StackModel::E;
        }
        else if(dx == 0)
        {
            second = StackModel::NONE;
        }
        else if(dx >= 1)
        {
            second = StackModel::W;
        }

        StackModel *stackModel = this->refStackModel(path[i-1].getPosition());
        stackModel->setPathIndication(StackModel::PathIndication(first | second));
        this->currentPath.append(stackModel);
    }

    StackModel *stackModel = this->refStackModel(path.last().getPosition());
    stackModel->setPathIndication(StackModel::DESTINATION);
    this->currentPath.append(stackModel);

    emit this->mapPathChanged();
    return;
}

StackModel *MapModel::refStartPositionStack() const
{
    PIDGIRL::newSeed();
    QVector<StackModel *> possibleStartPositions;

    for(int i = 0; i < this->startPositionStacks.size(); ++i)
    {
        if(!this->startPositionStacks[i]->refCharacter())
        {
            possibleStartPositions.append(this->startPositionStacks[i]);
        }
    }

    if(possibleStartPositions.isEmpty())
    {
        qDebug("No possible start positons found on this map. Choose another map.");
        return 0;
    }

    StackModel *startPositionStack = possibleStartPositions[qrand()%possibleStartPositions.size()];

    qDebug(QString("Referencing Random Start Position on coordinates (%1,%2,%3)").arg(QString::number(startPositionStack->getSquarePos().x()),
                                                                                       QString::number(startPositionStack->getSquarePos().y()),
                                                                                       QString::number(startPositionStack->getHeight())).toStdString().c_str());

    return startPositionStack;
}

StackModel *MapModel::refPlayerStack(unsigned int playerID) const
{
    for(int i = 0; i < this->playerStacks.size(); ++i)
    {
        Player *player = qobject_cast<Player *>(this->playerStacks[i]->refCharacter());
        if(playerID == player->getSpawnID())
        {
            return this->playerStacks[i];
        }
    }

    qDebug() << "No player with the given ID" << playerID << " found.";
    return 0;
}

StackModel *MapModel::refDestinationStackModel() const
{
    if(this->currentPath.isEmpty())
    {
        return 0;
    }
    else
    {
        return this->currentPath.last();
    }
}

StackModel *MapModel::refStackModel(int x, int y) const
{
    return this->refStackModel(x,y,this->getCurrentHeight());
}

StackModel *MapModel::refStackModel(int x, int y, int z) const
{
    if(x < 0)
    {
        std::cout << "Error in refStackModel: x was " << x << " < 0." << std::endl;
        x = 0;
    }

    if(x >= this->getHSquareCount())
    {
        std::cout << "Error in refStackModel: x was " << x << " >= " << this->getHSquareCount() << "." << std::endl;
        x = this->getHSquareCount() - 1;
    }

    if(y < 0)
    {
        std::cout << "Error in refStackModel: y was " << y << " < 0." << std::endl;
        y = 0;
    }

    if(y >= this->getVSquareCount())
    {
        std::cout << "Error in refStackModel: y was " << y << " >= " << this->getVSquareCount() << "." << std::endl;
        y = this->getVSquareCount() - 1;
    }

    if(z < 0)
    {
        std::cout << "Error in refStackModel: z was " << z << " < 0." << std::endl;
        z = 0;
    }

    if(z >= this->getMaxHeight())
    {
        std::cout << "Error in refStackModel: z was " << z << " >= " << this->getMaxHeight() << "." << std::endl;
        z = this->getMaxHeight() - 1;
    }

    if(!this->stackModelGrid[x][y][z])
    {
        std::cout << "Error in refStackModel: Chosen stack model was 0." << std::endl;
    }

    return this->stackModelGrid[x][y][z];
}

StackModel *MapModel::refStackModel(const QPoint &pos) const
{
    return this->refStackModel(pos.x(), pos.y());
}

ObjectBase *MapModel::refClipboardObject() const
{
    return this->clipboardObject;
}

void MapModel::serialize(QIODevice *device) const
{
    QDataStream dataStream(device);
    this->serialize(dataStream);

    return;
}

void MapModel::serialize(QDataStream &dataStream) const
{
    dataStream << this->getLocalMapPath();
    dataStream << this->getHSquareCount();
    dataStream << this->getVSquareCount();
    dataStream << this->getMaxHeight();
    dataStream << this->getCurrentHeight();
    dataStream << this->getGridLineSize();
    dataStream << this->getSquareSize();

    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->stackModelGrid[x][y][z]->serialize(dataStream);
            }
        }
    }

    return;
}

void MapModel::deserialize(QIODevice *device)
{
    QDataStream dataStream(device);
    this->deserialize(dataStream);

    return;
}

void MapModel::deserialize(QDataStream &dataStream)
{
    this->clearStackModelGrid();

    QString localMapPath;
    int hSquareCount;
    int vSquareCount;
    int maxHeight;
    int currentHeight;
    int gridLineSize;
    int squareSize;

    dataStream >> localMapPath >> hSquareCount >> vSquareCount >> maxHeight >> currentHeight >> gridLineSize >> squareSize;

    this->initMapModel(hSquareCount, vSquareCount, maxHeight, gridLineSize);
    this->setLocalMapPath(localMapPath);
    this->setCurrentHeight(currentHeight);

    for(int x = 0; x < this->getHSquareCount(); ++x)
    {
        for(int y = 0; y < this->getVSquareCount(); ++y)
        {
            for(int z = 0; z < this->getMaxHeight(); ++z)
            {
                this->stackModelGrid[x][y][z]->deserialize(dataStream);
            }
        }
    }

    return;
}
