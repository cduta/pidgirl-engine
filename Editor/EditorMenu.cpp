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

#include "Editor/EditorMenu.h"

#include <QKeySequence>

#include "Editor/EditorCommon.h"
#include "Command/Backend/UseRedo.h"
#include "Command/Backend/UseUndo.h"
#include "Command/Backend/Editor/World/NewWorld.h"
#include "Command/Backend/Editor/World/SaveWorld.h"
#include "Command/Backend/Editor/World/SaveWorldAs.h"
#include "Command/Backend/Editor/World/LoadWorld.h"
#include "Command/Backend/Common/Quit.h"
#include "Command/Backend/Editor/World/SaveMap.h"
#include "Command/Backend/Editor/World/SaveMapAs.h"
#include "Command/Backend/Editor/Map/ChangeZoomFactor.h"
#include "Command/Backend/ShowAbout.h"

EditorMenu::EditorMenu(Processor *processor, EditorModel *editorModel, WorldModel *worldModel, QWidget *parent)
    : QMenuBar(parent), mapPropertiesDialog(processor, this), worldPropertiesDialog(processor, worldModel, this)
{
    this->processor = processor;
    this->editorModel = editorModel;
    this->worldModel = worldModel;

    // Initiate actions.

    this->newWorldAction = new QAction(tr("New World..."), this);
    this->newWorldAction->setShortcut(QKeySequence::New);
    connect(this->newWorldAction, SIGNAL(triggered()), this, SLOT(createNewWorld()));
    this->saveMapAction = new QAction(tr("Save Map..."), this);
    this->saveMapAction->setShortcut(QKeySequence::Save);
    connect(this->saveMapAction, SIGNAL(triggered()), this, SLOT(saveMap()));
    this->saveMapAsAction = new QAction(tr("Save Map As..."), this);
    this->saveMapAsAction->setShortcut(QKeySequence::SaveAs);
    connect(this->saveMapAsAction, SIGNAL(triggered()), this, SLOT(saveMapAs()));
    this->saveWorldAction = new QAction(tr("Save World..."), this);
    connect(this->saveWorldAction, SIGNAL(triggered()), this, SLOT(saveWorld()));
    this->saveWorldAsAction = new QAction(tr("Save World As..."), this);
    connect(this->saveWorldAsAction, SIGNAL(triggered()), this, SLOT(saveWorldAs()));
    this->loadWorldAction = new QAction(tr("Load World..."), this);
    this->loadWorldAction->setShortcut(QKeySequence::Open);
    connect(this->loadWorldAction, SIGNAL(triggered()), this, SLOT(loadWorld()));
    this->quitAction = new QAction(tr("Quit"), this);
    this->quitAction->setShortcut(QKeySequence::Quit);
    connect(this->quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    this->undoAction = new QAction(tr("Undo"), this);
    this->undoAction->setShortcut(QKeySequence::Undo);
    this->undoAction->setEnabled(false);
    connect(this->undoAction, SIGNAL(triggered()), this, SLOT(useUndo()));
    connect(this->processor->refUndoRedo(), SIGNAL(undoChanged(bool)), this->undoAction, SLOT(setEnabled(bool)));
    this->redoAction = new QAction(tr("Redo"), this);
    this->redoAction->setShortcut(QKeySequence::Redo);
    this->redoAction->setEnabled(false);
    connect(this->redoAction, SIGNAL(triggered()), this, SLOT(useRedo()));
    connect(this->processor->refUndoRedo(), SIGNAL(redoChanged(bool)), this->redoAction, SLOT(setEnabled(bool)));

    this->mapPropertiesAction = new QAction(tr("Map Properties..."), this);
    connect(this->mapPropertiesAction, SIGNAL(triggered()), this, SLOT(showMapProperties()));
    this->worldPropertiesAction = new QAction(tr("World Properties..."), this);
    connect(this->worldPropertiesAction, SIGNAL(triggered()), this, SLOT(showWorldProperties()));

    this->zoomActionGroup = new QActionGroup(this);
    this->zoomActionGroup->addAction(new QAction("x1", this));
    this->zoomActionGroup->actions().at(0)->setCheckable(true);
    this->zoomActionGroup->actions().at(0)->setChecked(true);
    this->zoomActionGroup->addAction(new QAction("x2", this));
    this->zoomActionGroup->actions().at(1)->setCheckable(true);
    this->zoomActionGroup->addAction(new QAction("x3", this));
    this->zoomActionGroup->actions().at(2)->setCheckable(true);
    this->zoomActionGroup->setExclusive(true);
    connect(this->zoomActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(zoom(QAction *)));

    this->aboutAction = new QAction(tr("About..."), this);
    connect(this->aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    // Setup Menu

    this->fileMenu = new QMenu(tr("File"), this);
    this->fileMenu->addAction(this->newWorldAction);
    this->fileMenu->addSeparator();
    this->fileMenu->addAction(this->saveMapAction);
    this->fileMenu->addAction(this->saveMapAsAction);
    this->fileMenu->addAction(this->saveWorldAction);
    this->saveWorldAsAction->setEnabled(false);
    this->fileMenu->addAction(this->saveWorldAsAction);
    this->fileMenu->addSeparator();
    this->fileMenu->addAction(this->loadWorldAction);
    this->fileMenu->addSeparator();
    this->fileMenu->addAction(this->quitAction);

    this->editMenu = new QMenu(tr("Edit"), this);
    this->editMenu->addAction(this->undoAction);
    this->editMenu->addAction(this->redoAction);
    this->editMenu->addSeparator();
    this->editMenu->addAction(this->mapPropertiesAction);
    this->editMenu->addSeparator();
    this->editMenu->addAction(this->worldPropertiesAction);

    this->viewMenu = new QMenu(tr("View"), this);
    this->zoomMenu = new QMenu(tr("Zoom"), this->viewMenu);
    this->zoomMenu->addActions(this->zoomActionGroup->actions());

    this->helpMenu = new QMenu(tr("Help"), this);
    this->helpMenu->addAction(this->aboutAction);

    // Set up the MenuBar
    this->addMenu(this->fileMenu);
    this->addMenu(this->editMenu);
    this->viewMenu->addMenu(this->zoomMenu);
    this->addMenu(this->viewMenu);
    this->addMenu(this->helpMenu);

    this->setEnabled(true);
    this->setVisible(true);
}

void EditorMenu::updateSize(int horizontal, int vertical, int maxHeight)
{
    this->mapPropertiesDialog.updateHorizontal(horizontal);
    this->mapPropertiesDialog.updateVertical(vertical);
    this->mapPropertiesDialog.updateMaxHeight(maxHeight);
}

void EditorMenu::createNewWorld()
{
    this->processor->execute(new NewWorld());
    return;
}

void EditorMenu::saveMap()
{
    this->processor->execute(new SaveMap());
    return;
}

void EditorMenu::saveMapAs()
{
    this->processor->execute(new SaveMapAs());
    return;
}

void EditorMenu::saveWorld()
{
    this->processor->execute(new SaveWorld());
    return;
}

void EditorMenu::saveWorldAs()
{
    this->processor->execute(new SaveWorldAs());
    return;
}

void EditorMenu::loadWorld()
{
    this->processor->execute(new LoadWorld());
    return;
}

void EditorMenu::useUndo()
{
    this->processor->execute(new UseUndo());
    return;
}

void EditorMenu::useRedo()
{
    this->processor->execute(new UseRedo());
    return;
}

void EditorMenu::showMapProperties()
{
    this->mapPropertiesDialog.exec();
    return;
}

void EditorMenu::showWorldProperties()
{
    this->worldPropertiesDialog.exec();
    return;
}

void EditorMenu::zoom(QAction *zoomAction)
{
    int zoomFactor = this->zoomActionGroup->actions().indexOf(zoomAction) + 1;
    this->processor->execute(new ChangeZoomFactor(zoomFactor));
    zoomAction->setChecked(true);
    return;
}

void EditorMenu::quit()
{
    this->processor->execute(new Quit());
    return;
}

void EditorMenu::about()
{
    this->processor->execute(new ShowAbout());
    return;
}
