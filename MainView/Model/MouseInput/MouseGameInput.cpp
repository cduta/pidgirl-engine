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

#include "MouseGameInput.h"

#include "MainView/Model/MouseInput/IdleGameMouseState.h"
#include "MainView/ObjectMenu.h"

#include "Command/Backend/Game/Ingame/EndTurn.h"
#include "Command/Backend/Game/Ingame/ShowGameOptions.h"

MouseGameInput::MouseGameInput(GameModel *gameModel, MapModel *mapModel, Processor *processor, QObject *parent)
    : MouseInput(new IdleGameMouseState(processor, 0), gameModel, mapModel, processor, parent)
{
}

void MouseGameInput::nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack)
{
    this->currentMouseState = this->currentMouseState->nextState(type, event, targetStack, this->mapModel->refPlayerStack(this->gameModel->getPlayerID()));
    //this->currentMouseState->setTarget(targetStack);
    if(this->currentMouseState->showContextMenu())
    {
        this->showGameContextMenu(targetStack);
    }
    return;
}

void MouseGameInput::showGameContextMenu(StackModel *stackModel)
{
    this->contextMenu = new QMenu();

    ObjectCharacter *character = stackModel->refCharacter();
    QList<ObjectItem *> *items = stackModel->refItemList();
    ObjectTile *wall = stackModel->refWall();
    ObjectTile *floor = stackModel->refFloor();
    QList<ObjectSpecial *> *specials = stackModel->refSpecialList();

    if(character)
    {
        ObjectMenu *menu = new ObjectMenu(character, this->processor, this->contextMenu);

        if(character->getObjectID() == ObjectID::PLAYER &&
           this->gameModel->getPlayerID() == character->getSpawnID())
        {
            menu->setTitle(menu->title().append(tr(" (YOU)")));
        }

        this->contextMenu->addMenu(menu);
    }

    if(!items->isEmpty())
    {
        QMenu *itemMenu = new QMenu(tr("Items"), this->contextMenu);

        for(int i = 0; i < items->size(); ++i)
        {
            itemMenu->addMenu(new ObjectMenu(items->at(i), this->processor, itemMenu));
        }

        if(!itemMenu->isEmpty())
        {
            this->contextMenu->addMenu(itemMenu);
        }
    }

    if(wall)
    {
        this->contextMenu->addMenu(new ObjectMenu(wall, this->processor, this->contextMenu));
    }

    if(floor)
    {
        this->contextMenu->addMenu(new ObjectMenu(floor, this->processor, this->contextMenu));
    }

    if(!specials->isEmpty())
    {
        QMenu *specialMenu = new QMenu(tr("Specials"), this->contextMenu);

        for(int i = 0; i < specials->size(); ++i)
        {
            if(specials->at(i)->isVisibleInGame())
            {
                specialMenu->addMenu(new ObjectMenu(specials->at(i), this->processor, specialMenu));
            }
        }

        if(!specialMenu->isEmpty())
        {
            this->contextMenu->addMenu(specialMenu);
        }
    }

    if(character)
    {
        QAction *options = 0;
        QAction *endTurn = 0;

        if(character &&
           character->getObjectID() == ObjectID::PLAYER &&
           character->getSpawnID() == this->gameModel->getPlayerID())
        {
            endTurn = new QAction(tr("End Turn"), this->contextMenu);
            connect(endTurn, SIGNAL(triggered()), this, SLOT(endTurn()));
            options = new QAction(tr("Options"), this->contextMenu);
            connect(options, SIGNAL(triggered()), this, SLOT(showGameOptions()));
        }

        if(((this->gameModel->isYourTurn() && endTurn) || options) && !this->contextMenu->isEmpty())
        {
            this->contextMenu->addSeparator();
        }

        if(options)
        {
            this->contextMenu->addAction(options);
        }

        if(this->gameModel->isYourTurn() && endTurn)
        {
            this->contextMenu->addAction(endTurn);
        }
    }

    if(!this->contextMenu->isEmpty())
    {
        emit showContextMenu(stackModel);
    }

    return;
}

void MouseGameInput::endTurn()
{
    this->processor->execute(new EndTurn());
    return;
}

void MouseGameInput::showGameOptions()
{
    this->processor->execute(new ShowGameOptions());
    return;
}
