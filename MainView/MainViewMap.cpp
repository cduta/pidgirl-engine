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
#include "MainViewMap.h"

#include <QPainter>
#include <QMessageBox>

#include "MainView/Model/MouseInput/MouseGameInput.h"
#include "MainView/Model/MouseInput/MouseEditorInput.h"

#include <iostream>

MainViewMap::MainViewMap(Processor *processor, MapModel *mapModel, EditorModel *editorModel, GameModel *gameModel, QWidget *parent) :
    QWidget(parent)
{
    this->processor = processor;

    this->gameModel = gameModel;
    this->editorModel = editorModel;
    this->mapModel = mapModel;

    if(this->editorModel->getIsEditor())
    {
        this->mouseInput = new MouseEditorInput(this->gameModel, this->mapModel, this->processor, this);
    }
    else
    {
        this->mouseInput = new MouseGameInput(this->gameModel, this->mapModel, this->processor, this);
    }

    connect(this->mouseInput, SIGNAL(showContextMenu(StackModel *)), this, SLOT(showContextMenu(StackModel *)));

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->updateMap();

    connect(this->mapModel, SIGNAL(mapPathChanged()), this, SLOT(update()));
}

void MainViewMap::updateMap()
{
    this->stackGrid.resize(this->mapModel->getHSquareCount());

    for(int x = 0; x < this->stackGrid.size(); ++x)
    {
        this->stackGrid[x].resize(this->mapModel->getVSquareCount());

        for(int y = 0; y < this->stackGrid[x].size(); ++y)
        {
            this->createStackGrid(x,y);
        }
    }

    this->update();
    emit this->mapSizeUpdated();
    return;
}

void MainViewMap::paintGrid()
{
    QColor greyness(0,0,0,63);
    QPainter painter(this);

    this->resize(this->mapModel->getMapSize());

    painter.setPen(QColor("white"));
    painter.setBrush(QBrush(QColor("white")));
    painter.drawRect(0,0,this->mapModel->getMapSize().width(),this->mapModel->getMapSize().height());
    painter.setPen(greyness);

    int squareSize = this->mapModel->getSquareSize();
    int gridLineSize = this->mapModel->getGridLineSize();
    int vCount = this->mapModel->getVSquareCount();
    int hCount = this->mapModel->getHSquareCount();

    for(int i = 0; i < this->mapModel->getHSquareCount()+1; ++i)
    {
        for(int j = -gridLineSize+1; j < gridLineSize; ++j)
        {
            painter.drawLine((squareSize+1)*i+j,
                             0,
                             (squareSize+1)*i+j,
                             (squareSize+1)*vCount);
        }
    }

    for(int i = 0; i < this->mapModel->getVSquareCount()+1; ++i)
    {
        for(int j = -gridLineSize+1; j < gridLineSize; ++j)
        {
            painter.drawLine(0,
                             (squareSize+1)*i+j,
                             (squareSize+1)*hCount,
                             (squareSize+1)*i+j);
        }
    }

    return;
}

void MainViewMap::paintEvent(QPaintEvent *)
{
    this->paintGrid();

    return;
}

void MainViewMap::createStackGrid(int x, int y)
{
    this->stackGrid[x][y] = new MainViewStack(this->processor, this->mapModel->refStackModel(x,y), this->mapModel, this->editorModel, this->gameModel, this->mouseInput, this);
    return;
}

void MainViewMap::deleteStackGrid(int x, int y)
{
    this->stackGrid[x][y]->deleteLater();
    this->stackGrid[x][y] = 0;
    return;
}

void MainViewMap::showContextMenu(StackModel *stackModel)
{
    MainViewStack *mainViewStack = this->stackGrid[stackModel->getSquarePos().x()][stackModel->getSquarePos().y()];
    QPoint p = this->mapToGlobal(mainViewStack->rect().topLeft());
    this->mouseInput->showContextMenu(QPoint(p.x() + (mainViewStack->size().width() + this->mapModel->getGridLineSize()) * (stackModel->getSquarePos().x() + 1) + this->mapModel->getGridLineSize(),
                                             p.y() + (mainViewStack->size().height() + this->mapModel->getGridLineSize()) * stackModel->getSquarePos().y() + 1));
}
