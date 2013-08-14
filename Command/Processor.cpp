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

#include "Command/Processor.h"

#include <iostream>

Processor::Processor(QObject *parent)
    : QObject(parent)
{
    this->undoRedo = new UndoRedo(this);
    this->editorModel = 0;
    this->worldModel = 0;
    this->gameModel = 0;
    this->mapModel = 0;
    this->networkModel = 0;

}

bool Processor::isExecutable(BaseCommand *command)
{
    if(!command)
    {
        std::cout << "Command was 0." << std::endl;
        return false;
    }

    command->setModels(this, this->undoRedo, this->editorModel, this->worldModel, this->gameModel, this->mapModel, this->networkModel);

    return command->isExecutable();
}

bool Processor::execute(BaseCommand *command)
{
    if(!command)
    {
        std::cout << "Command was 0." << std::endl;
        return false;
    }

    command->setModels(this, this->undoRedo, this->editorModel, this->worldModel, this->gameModel, this->mapModel, this->networkModel);

    if(!command->isExecutable())
    {
        std::cout << "Tried executing a not executable command. Command was: " << command->objectName().toStdString() << std::endl;
        return false;
    }

    if(!command->execute())
    {
        if(command->isErrorEnabled())
        {
            std::cout << "Command " << command->objectName().toStdString() << " failed." << std::endl;
        }
        return false;
    }

    if(command->isUndoable())
    {
        this->undoRedo->add(command);
    }
    else
    {
        if(command->isClearingUndoRedo())
        {
            this->undoRedo->clear();
        }

        command->deleteLater();
    }

    emit this->commandProcessed();

    return true;
}

void Processor::setEditorModel(EditorModel *editorModel)
{
    this->editorModel = editorModel;
    return;
}

void Processor::setWorldModel(WorldModel *worldModel)
{
    this->worldModel = worldModel;
    return;
}

void Processor::setGameModel(GameModel *gameModel)
{
    this->gameModel = gameModel;
    return;
}

void Processor::setMapModel(MapModel *mapModel)
{
    this->mapModel = mapModel;
    return;
}

void Processor::setNetworkModel(NetworkModel *networkModel)
{
    this->networkModel = networkModel;
    return;
}

UndoRedo *Processor::refUndoRedo() const
{
    return this->undoRedo;
}
