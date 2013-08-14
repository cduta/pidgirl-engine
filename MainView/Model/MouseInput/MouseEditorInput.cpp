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

#include "MouseEditorInput.h"

#include "MainView/Model/MouseInput/IdleEditorMouseState.h"

#include "Command/Backend/Editor/Map/CopyWall.h"
#include "Command/Backend/Editor/Map/CutWall.h"
#include "Command/Backend/Editor/Map/RemoveWall.h"

#include "Command/Backend/Editor/Map/PasteObject.h"

#include "Command/Backend/Editor/Map/RemoveAllObjects.h"

MouseEditorInput::MouseEditorInput(GameModel *gameModel, MapModel *mapModel, Processor *processor, QObject *parent)
    : MouseInput(new IdleEditorMouseState(processor, 0), gameModel, mapModel, processor, parent)
{
    this->contextMenuStack = 0;
}

void MouseEditorInput::nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack)
{
    this->currentMouseState = this->currentMouseState->nextState(type, event, targetStack);
    //this->currentMouseState->setTarget(targetStack);
    if(this->currentMouseState->showContextMenu())
    {
        this->showEditorContextMenu(targetStack);
    }
    return;
}

void MouseEditorInput::showEditorContextMenu(StackModel *stackModel)
{
    this->contextMenuStack = stackModel;
    this->contextMenu = new QMenu();

    this->characterMenu = new QMenu(tr("Character"), this->contextMenu);
    this->wallMenu = new QMenu(tr("Wall"), this->contextMenu);
    this->floorMenu = new QMenu(tr("Floor"), this->contextMenu);
    this->itemsMenu = new QMenu(tr("Items"), this->contextMenu);
    this->specialsMenu = new QMenu(tr("Specials"), this->contextMenu);

    this->copyCharacterAction = new QAction(tr("Copy"), this->characterMenu);
    connect(this->copyCharacterAction, SIGNAL(triggered()), this, SLOT(copyCharacter()));
    this->cutCharacterAction = new QAction(tr("Cut"), this->characterMenu);
    connect(this->cutCharacterAction, SIGNAL(triggered()), this, SLOT(cutCharacter()));
    this->removeCharacterAction = new QAction(tr("Remove"), this->characterMenu);
    connect(this->removeCharacterAction, SIGNAL(triggered()), this, SLOT(removeCharacter()));
    this->editCharacterAction = new QAction(tr("Edit..."), this->characterMenu);
    connect(this->editCharacterAction, SIGNAL(triggered()), this, SLOT(editCharacter()));

    this->copyWallAction = new QAction(tr("Copy"), this->wallMenu);
    connect(this->copyWallAction, SIGNAL(triggered()), this, SLOT(copyWall()));
    this->cutWallAction = new QAction(tr("Cut"), this->wallMenu);
    connect(this->cutWallAction, SIGNAL(triggered()), this, SLOT(cutWall()));
    this->removeWallAction = new QAction(tr("Remove"), this->wallMenu);
    connect(this->removeWallAction, SIGNAL(triggered()), this, SLOT(removeWall()));
    this->editWallAction = new QAction(tr("Edit..."), this->wallMenu);
    connect(this->editWallAction, SIGNAL(triggered()), this, SLOT(editWall()));

    this->copyFloorAction = new QAction(tr("Copy"), this->floorMenu);
    connect(this->copyFloorAction, SIGNAL(triggered()), this, SLOT(copyFloor()));
    this->cutFloorAction = new QAction(tr("Cut"), this->floorMenu);
    connect(this->cutFloorAction, SIGNAL(triggered()), this, SLOT(cutFloor()));
    this->removeFloorAction = new QAction(tr("Remove"), this->floorMenu);
    connect(this->removeFloorAction, SIGNAL(triggered()), this, SLOT(removeFloor()));
    this->editFloorAction = new QAction(tr("Edit..."), this->floorMenu);
    connect(this->editFloorAction, SIGNAL(triggered()), this, SLOT(editFloor()));

    this->copyItemsAction = new QAction(tr("Copy..."), this->itemsMenu);
    connect(this->copyItemsAction, SIGNAL(triggered()), this, SLOT(copyItems()));
    this->cutItemsAction = new QAction(tr("Cut..."), this->itemsMenu);
    connect(this->cutItemsAction, SIGNAL(triggered()), this, SLOT(cutItems()));
    this->removeItemsAction = new QAction(tr("Remove..."), this->itemsMenu);
    connect(this->removeItemsAction, SIGNAL(triggered()), this, SLOT(removeItems()));
    this->editItemsAction = new QAction(tr("Edit..."), this->itemsMenu);
    connect(this->editItemsAction, SIGNAL(triggered()), this, SLOT(editItems()));

    this->copySpecialsAction = new QAction(tr("Copy..."), this->specialsMenu);
    connect(this->copySpecialsAction, SIGNAL(triggered()), this, SLOT(copySpecials()));
    this->cutSpecialsAction = new QAction(tr("Cut..."), this->specialsMenu);
    connect(this->cutSpecialsAction, SIGNAL(triggered()), this, SLOT(cutSpecials()));
    this->removeSpecialsAction = new QAction(tr("Remove..."), this->specialsMenu);
    connect(this->removeSpecialsAction, SIGNAL(triggered()), this, SLOT(removeSpecials()));
    this->editSpecialsAction = new QAction(tr("Edit..."), this->specialsMenu);
    connect(this->editSpecialsAction, SIGNAL(triggered()), this, SLOT(editSpecials()));

    this->pasteObjectAction = new QAction(tr("Paste"), this);
    connect(this->pasteObjectAction, SIGNAL(triggered()), this, SLOT(pasteObject()));

    this->removeAllAction = new QAction(tr("Remove All"), this);
    connect(this->removeAllAction, SIGNAL(triggered()), this, SLOT(removeAll()));

    this->checkItemsActions();
    this->checkCharacterActions();
    this->checkWallActions();
    this->checkFloorActions();
    this->checkSpecialsActions();

    this->checkPasteAction();
    this->checkRemoveAllAction();

    this->characterMenu->addAction(this->copyCharacterAction);
    this->characterMenu->addAction(this->cutCharacterAction);
    this->characterMenu->addAction(this->removeCharacterAction);
    this->characterMenu->addSeparator();
    this->characterMenu->addAction(this->editCharacterAction);

    this->wallMenu->addAction(this->copyWallAction);
    this->wallMenu->addAction(this->cutWallAction);
    this->wallMenu->addAction(this->removeWallAction);
    this->wallMenu->addSeparator();
    this->wallMenu->addAction(this->editWallAction);

    this->floorMenu->addAction(this->copyFloorAction);
    this->floorMenu->addAction(this->cutFloorAction);
    this->floorMenu->addAction(this->removeFloorAction);
    this->floorMenu->addSeparator();
    this->floorMenu->addAction(this->editFloorAction);

    this->itemsMenu->addAction(this->copyItemsAction);
    this->itemsMenu->addAction(this->cutItemsAction);
    this->itemsMenu->addAction(this->removeItemsAction);
    this->itemsMenu->addSeparator();
    this->itemsMenu->addAction(this->editItemsAction);

    this->specialsMenu->addAction(this->copySpecialsAction);
    this->specialsMenu->addAction(this->cutSpecialsAction);
    this->specialsMenu->addAction(this->removeSpecialsAction);
    this->specialsMenu->addSeparator();
    this->specialsMenu->addAction(this->editSpecialsAction);

    this->contextMenu->addMenu(this->characterMenu);
    this->contextMenu->addMenu(this->wallMenu);
    this->contextMenu->addMenu(this->floorMenu);
    this->contextMenu->addMenu(this->itemsMenu);
    this->contextMenu->addMenu(this->specialsMenu);
    this->contextMenu->addSeparator();
    this->contextMenu->addAction(this->pasteObjectAction);
    this->contextMenu->addSeparator();
    this->contextMenu->addAction(this->removeAllAction);

    if(!this->contextMenu->isEmpty())
    {
        emit showContextMenu(stackModel);
    }

    return;
}

void MouseEditorInput::checkRemoveAllAction()
{
    this->removeAllAction->setEnabled(!this->contextMenuStack->isEmpty());
    return;
}

void MouseEditorInput::copyCharacter()
{
    // Command Copy Character

    return;
}

void MouseEditorInput::cutCharacter()
{
    // Command Cut Character

    return;
}

void MouseEditorInput::removeCharacter()
{
    // Command Remove Character

    return;
}

void MouseEditorInput::editCharacter()
{
    // Command Edit Character

    return;
}

void MouseEditorInput::checkCharacterActions()
{
    bool enable = this->contextMenuStack->refCharacter();

    this->copyCharacterAction->setEnabled(enable);
    this->cutCharacterAction->setEnabled(enable);
    this->removeCharacterAction->setEnabled(enable);
    this->editCharacterAction->setEnabled(enable);

    this->checkRemoveAllAction();

    this->characterMenu->setEnabled(this->copyCharacterAction->isEnabled() ||
                                    this->cutCharacterAction->isEnabled() ||
                                    this->removeCharacterAction->isEnabled() ||
                                    this->editCharacterAction->isEnabled());

    return;
}

void MouseEditorInput::copyItems()
{
    // Command CopyItems

    return;
}

void MouseEditorInput::cutItems()
{
    // Command CutItems

    return;
}

void MouseEditorInput::removeItems()
{
    // Command RemoveItems

    return;
}

void MouseEditorInput::editItems()
{
    // Command CutItems

    return;
}

void MouseEditorInput::checkItemsActions()
{
    bool enable = !this->contextMenuStack->refItemList()->isEmpty();

    this->copyItemsAction->setEnabled(enable);
    this->cutItemsAction->setEnabled(enable);
    this->removeItemsAction->setEnabled(enable);
    this->editItemsAction->setEnabled(enable);
    this->checkRemoveAllAction();

    this->itemsMenu->setEnabled(this->copyItemsAction->isEnabled() ||
                                this->cutItemsAction->isEnabled() ||
                                this->removeItemsAction->isEnabled() ||
                                this->editItemsAction->isEnabled());

    return;
}

void MouseEditorInput::copySpecials()
{
    // Command CopySpecial

    return;
}

void MouseEditorInput::cutSpecials()
{
    // Command CutSpecial

    return;
}

void MouseEditorInput::removeSpecials()
{
    // RemoveSpecial

    return;
}

void MouseEditorInput::editSpecials()
{
    // EditSpecial

    return;
}

void MouseEditorInput::checkSpecialsActions()
{
    bool enable = !this->contextMenuStack->refSpecialList()->isEmpty();

    this->copySpecialsAction->setEnabled(enable);
    this->cutSpecialsAction->setEnabled(enable);
    this->removeSpecialsAction->setEnabled(enable);
    this->editSpecialsAction->setEnabled(enable);
    this->checkRemoveAllAction();

    this->specialsMenu->setEnabled(this->copySpecialsAction->isEnabled() ||
                                   this->cutSpecialsAction->isEnabled() ||
                                   this->removeSpecialsAction->isEnabled() ||
                                   this->editSpecialsAction->isEnabled());

    return;
}

void MouseEditorInput::copyWall()
{
    this->processor->execute(new CopyWall(this->contextMenuStack));

    return;
}

void MouseEditorInput::cutWall()
{
    this->processor->execute(new CutWall(this->contextMenuStack));

    return;
}

void MouseEditorInput::removeWall()
{
    this->processor->execute(new RemoveWall(this->contextMenuStack));

    return;
}

void MouseEditorInput::editWall()
{
    // Command Edit Wall

    return;
}

void MouseEditorInput::checkWallActions()
{
    bool enable = this->contextMenuStack->refWall();

    this->copyWallAction->setEnabled(enable);
    this->cutWallAction->setEnabled(enable);
    this->removeWallAction->setEnabled(enable);
    this->editWallAction->setEnabled(enable);
    this->checkRemoveAllAction();

    this->wallMenu->setEnabled(this->copyWallAction->isEnabled() ||
                               this->cutWallAction->isEnabled() ||
                               this->removeWallAction->isEnabled() ||
                               this->editWallAction->isEnabled());

    return;
}

void MouseEditorInput::copyFloor()
{
    // Command Copy Floor

    return;
}

void MouseEditorInput::cutFloor()
{
    // Command Cut Floor

    return;
}

void MouseEditorInput::removeFloor()
{
    // Command removeFloor

    return;
}

void MouseEditorInput::editFloor()
{
    // Command Edit Floor

    return;
}

void MouseEditorInput::checkFloorActions()
{
    bool enable = this->contextMenuStack->refFloor();

    this->copyFloorAction->setEnabled(enable);
    this->cutFloorAction->setEnabled(enable);
    this->removeFloorAction->setEnabled(enable);
    this->editFloorAction->setEnabled(enable);
    this->checkRemoveAllAction();

    this->floorMenu->setEnabled(this->copyFloorAction->isEnabled() ||
                                this->cutFloorAction->isEnabled() ||
                                this->removeFloorAction->isEnabled() ||
                                this->editFloorAction->isEnabled());

    return;
}

void MouseEditorInput::checkPasteAction()
{
    this->pasteObjectAction->setEnabled(this->mapModel->refClipboardObject());
    return;
}

void MouseEditorInput::pasteObject()
{
    this->processor->execute(new PasteObject(this->contextMenuStack));

    return;
}

void MouseEditorInput::removeAll()
{
    this->processor->execute(new RemoveAllObjects(this->contextMenuStack));
    return;
}
