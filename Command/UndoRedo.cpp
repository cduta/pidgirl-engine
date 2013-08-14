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

#include "UndoRedo.h"

#include <iostream>

UndoRedo::UndoRedo(QObject *parent) :
    QObject(parent)
{
    this->setOnlySavedWorldChanges(true);
    this->setOnlySavedMapChanges(true);
}

UndoRedo::~UndoRedo()
{
    this->clear();
    emit this->undoChanged(!this->undoList.isEmpty());
    emit this->redoChanged(!this->redoList.isEmpty());
}

void UndoRedo::undo()
{
    if(this->undoList.empty())
    {
        return;
    }

    BaseCommand *undoneCommand = this->undoList.takeFirst();
    undoneCommand->undo();
    this->redoList.prepend(undoneCommand);

    emit this->undoChanged(!this->undoList.isEmpty());
    emit this->redoChanged(!this->redoList.isEmpty());

    std::cout << "Undo: " << undoneCommand->objectName().toStdString() << std::endl;

    return;
}

void UndoRedo::redo()
{
    if(this->redoList.empty())
    {
        return;
    }

    BaseCommand *redoneCommand = this->redoList.takeFirst();
    redoneCommand->redo();
    this->undoList.prepend(redoneCommand);

    emit this->undoChanged(!this->undoList.isEmpty());
    emit this->redoChanged(!this->redoList.isEmpty());

    std::cout << "Redo: " << redoneCommand->objectName().toStdString() << std::endl;

    return;
}

void UndoRedo::add(BaseCommand *command)
{
    if(this->undoList.size() > PIDGIRL::MAX_UNDO_REDO_SIZE)
    {
        this->undoList.takeLast()->deleteLater();
        this->setPossibleToReachOriginalState(false);
    }

    this->clearRedoList();

    this->undoList.prepend(command);
    emit this->undoChanged(!this->undoList.isEmpty());

    return;
}

void UndoRedo::clear()
{
    this->clearUndoList();
    this->clearRedoList();
    this->undoListSavedState.clear();
    this->redoListSavedState.clear();
    this->setOnlySavedMapChanges(true);
    this->setOnlySavedWorldChanges(true);
    this->setPossibleToReachOriginalState(true);
    return;
}

void UndoRedo::clearUndoList()
{
    while(!this->undoList.empty())
    {
        this->undoList.takeFirst()->deleteLater();
    }

    emit this->undoChanged(!this->undoList.isEmpty());

    return;
}

void UndoRedo::clearRedoList()
{
    while(!this->redoList.empty())
    {
        this->redoList.takeFirst()->deleteLater();
    }

    emit this->redoChanged(!this->redoList.isEmpty());

    return;
}

bool UndoRedo::hasOnlySavedMapChanges()
{
    bool result = ((this->undoList == this->undoListSavedState &&
            this->redoList == this->redoListSavedState) ||
           (this->redoListSavedState.isEmpty() &&
            this->undoListSavedState.isEmpty() &&
            this->undoList.isEmpty() &&
            this->possibleToReachOriginalState)) && this->onlySavedMapChanges;

    return result;
}

bool UndoRedo::hasOnlySavedWorldChanges()
{
    return this->onlySavedWorldChanges;
}

void UndoRedo::setSavedStates()
{
    this->undoListSavedState = this->undoList;
    this->redoListSavedState = this->redoList;
    this->setOnlySavedMapChanges(true);
    return;
}

void UndoRedo::setOnlySavedWorldChanges(bool onlySavedWorldChanges)
{
    this->onlySavedWorldChanges = onlySavedWorldChanges;
    return;
}

void UndoRedo::setOnlySavedMapChanges(bool onlySavedMapChanges)
{
    this->onlySavedMapChanges = onlySavedMapChanges;
    return;
}

void UndoRedo::setPossibleToReachOriginalState(bool possibleToReachOriginalState)
{
    this->possibleToReachOriginalState = possibleToReachOriginalState;
    return;
}
