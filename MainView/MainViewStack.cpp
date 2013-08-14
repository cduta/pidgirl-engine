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
#include "MainViewStack.h"

#include <QPainter>
#include <QPoint>
#include <QApplication>

#include <iostream>

#include "MainView/ObjectMenu.h"
#include "Game/Model/GameModel.h"

MainViewStack::MainViewStack(Processor *processor, StackModel *stackModel, MapModel *mapModel, EditorModel *editorModel, GameModel *gameModel, MouseInput *mouseInput, QWidget *parent) :
    QWidget(parent)
{
    this->processor = processor;

    this->stackModel = stackModel;
    this->mapModel = mapModel;
    this->editorModel = editorModel;
    this->gameModel = gameModel;

    this->mouseInput = mouseInput;

    this->updateSize();

    connect(this->mapModel, SIGNAL(gridChanged()), this, SLOT(updateSize()));
    connect(this->stackModel, SIGNAL(characterChanged()), this, SLOT(update()));
    connect(this->stackModel, SIGNAL(itemListChanged()), this, SLOT(update()));
    connect(this->stackModel, SIGNAL(wallChanged()), this, SLOT(update()));
    connect(this->stackModel, SIGNAL(floorChanged()), this, SLOT(update()));
    connect(this->stackModel, SIGNAL(specialListChanged()), this, SLOT(update()));

    connect(this->stackModel, SIGNAL(pathIndicationChanged()), this, SLOT(update()));

    this->setAcceptDrops(true);

    this->update();
}

void MainViewStack::drawObject(QPainter *painter, ObjectBase *objectBase)
{
    if(objectBase)
    {
        QImage *image = objectBase->refImage();
        if(image)
        {
            painter->drawImage(0,0,(*image).scaledToHeight(this->size().height())); //, Qt::SmoothTransformation));
        }
    }
    return;
}

void MainViewStack::drawDirectionIndicator(QPainter *painter)
{
    if(this->stackModel->getPathIndication() == StackModel::NONE)
    {
        return;
    }

    QImage image;

    // TODO: Optimize to have the images loaded seperately and only use pointers instead of actual images.
    switch(this->stackModel->getPathIndication())
    {
        case StackModel::N:
        {
            image = QImage(":/misc/directionArrows/n");
            break;
        }
        case StackModel::NE:
        {
            image = QImage(":/misc/directionArrows/ne");
            break;
        }
        case StackModel::E:
        {
            image = QImage(":/misc/directionArrows/e");
            break;
        }
        case StackModel::SE:
        {
            image = QImage(":/misc/directionArrows/se");
            break;
        }
        case StackModel::S:
        {
            image = QImage(":/misc/directionArrows/s");
            break;
        }
        case StackModel::SW:
        {
            image = QImage(":/misc/directionArrows/sw");
            break;
        }
        case StackModel::W:
        {
            image = QImage(":/misc/directionArrows/w");
            break;
        }
        case StackModel::NW:
        {
            image = QImage(":/misc/directionArrows/nw");
            break;
        }
        case StackModel::DESTINATION:
        {
            image = QImage(":/misc/directionArrows/destination");
            break;
        }
        default: return; break;
    }

    painter->drawImage(0,0,image.scaledToHeight(this->size().height()));
    return;
}

void MainViewStack::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QList<ObjectItem *> *itemList = this->stackModel->refItemList();
    QList<ObjectSpecial *> *specialList = this->stackModel->refSpecialList();

    //std::cout << "Drawing Special...";
    for(int i = 0; i < specialList->size(); ++i)
    {
        if(this->editorModel->getIsEditor() || (!this->editorModel->getIsEditor() && specialList->at(i)->isVisibleInGame()))
        {
            this->drawObject(&painter, specialList->at(i));
        }
    }

    //std::cout << "Drawing Floor...";
    this->drawObject(&painter, this->stackModel->refFloor());
    //std::cout << "Drawing Wall...";
    this->drawObject(&painter, this->stackModel->refWall());

    //std::cout << "Drawing Items...";
    for(int i = 0; i < itemList->size(); ++i)
    {
        this->drawObject(&painter, itemList->at(i));
    }

    //std::cout << "Drawing Character..." << std::endl;
    this->drawObject(&painter, this->stackModel->refCharacter());

    if(!this->editorModel->getIsEditor())
    {
        this->drawDirectionIndicator(&painter);
    }

    return;
}

void MainViewStack::mousePressEvent(QMouseEvent *event)
{
    this->mouseInput->mousePressed(event, this->stackModel);
    return;
}

void MainViewStack::mouseMoveEvent(QMouseEvent *event)
{
    QWidget *widget = QApplication::widgetAt(this->mapToGlobal(event->pos()));

    if(!widget)
    {
        return;
    }

    if(event->buttons() & Qt::LeftButton)
    {
        QMouseEvent newEvent = QMouseEvent(QEvent::MouseButtonPress, event->pos(),Qt::LeftButton, event->buttons(), event->modifiers());
        QApplication::sendEvent(widget, &newEvent);
    }
    else if(event->buttons() & Qt::MiddleButton)
    {
        QMouseEvent newEvent = QMouseEvent(QEvent::MouseButtonPress, event->pos(),Qt::MiddleButton, event->buttons(), event->modifiers());
        QApplication::sendEvent(widget, &newEvent);
    }

    return;
}

void MainViewStack::mouseReleaseEvent(QMouseEvent *event)
{
    this->mouseInput->mouseReleased(event, this->stackModel);
    return;
}

void MainViewStack::setStackModel(StackModel *stackModel)
{
    this->stackModel = stackModel;
    this->update();
    return;
}

void MainViewStack::updateSize()
{
    int x = this->stackModel->getSquarePos().x();
    int y = this->stackModel->getSquarePos().y();
    int squareSize = this->mapModel->getSquareSize();
    this->resize(squareSize, squareSize);
    this->move(x*(squareSize+1)+1,
               y*(squareSize+1)+1);
    this->update();
    return;
}

void MainViewStack::updateAll()
{
    this->update();
    return;
}

