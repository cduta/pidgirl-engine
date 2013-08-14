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

#include "WorldFileTree.h"

#include <QMouseEvent>
#include <QModelIndexList>
#include <QApplication>
#include <QPoint>
#include <QSize>
#include <QHeaderView>

#include "Command/Backend/Editor/Map/LoadMapByIndex.h"
#include "Command/Backend/Editor/World/NewMapFile.h"
#include "Command/Backend/Editor/World/NewFolder.h"
#include "Command/Backend/Editor/World/RenameWorldEntry.h"
#include "Command/Backend/Editor/World/DuplicateWorldEntry.h"
#include "Command/Backend/Editor/World/RemoveWorldEntry.h"
#include "Command/Backend/Editor/World/MoveFile.h"

WorldFileTree::WorldFileTree(Processor *processor, WorldModel *worldModel, QWidget *parent) :
    QTreeView(parent)
{
    this->processor = processor;
    this->worldModel = worldModel;

    this->setModel(this->worldModel);
    this->updateRootIndex();

    for(int i = 1; i < this->worldModel->columnCount(); ++i)
    {
        this->hideColumn(i);
    }

    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setAcceptDrops(true);
    this->setDragEnabled(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->header()->hide();
    this->setAutoScrollMargin(16);

    this->newMapAction = new QAction(tr("New Map..."), this);
    connect(this->newMapAction, SIGNAL(triggered()), this, SLOT(newMap()));
    connect(this->newMapAction, SIGNAL(triggered()), this, SLOT(updateColumnWidth()));
    this->newFolderAction = new QAction(tr("New Folder..."), this);
    connect(this->newFolderAction, SIGNAL(triggered()), this, SLOT(newFolder()));
    connect(this->newFolderAction, SIGNAL(triggered()), this, SLOT(updateColumnWidth()));

    this->renameAction = new QAction(tr("Rename"), this);
    connect(this->renameAction, SIGNAL(triggered()), this, SLOT(rename()));
    connect(this->renameAction, SIGNAL(triggered()), this, SLOT(updateColumnWidth()));
    this->removeAction = new QAction(tr("Remove"), this);
    connect(this->removeAction, SIGNAL(triggered()), this, SLOT(remove()));
    connect(this->removeAction, SIGNAL(triggered()), this, SLOT(updateColumnWidth()));
    this->duplicateAction = new QAction(tr("Duplicate"), this);
    connect(this->duplicateAction, SIGNAL(triggered()), this, SLOT(duplicate()));
    connect(this->duplicateAction, SIGNAL(triggered()), this, SLOT(updateColumnWidth()));

    this->contextMenu = new QMenu(this);
    this->contextMenu->addAction(this->newMapAction);
    this->contextMenu->addAction(this->newFolderAction);
    this->contextMenu->addSeparator();
    this->contextMenu->addAction(this->renameAction);
    this->contextMenu->addAction(this->removeAction);
    this->contextMenu->addAction(this->duplicateAction);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(indexDoubleClicked(QModelIndex)));
    connect(this->worldModel, SIGNAL(fileChanged()), this, SLOT(updateRootIndex()));
    connect(this->worldModel, SIGNAL(directoryLoaded(QString)), this, SLOT(updateColumnWidth()));
}

QMenu *WorldFileTree::refContexMenu()
{
    return this->contextMenu;
}

void WorldFileTree::mouseReleaseEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::RightButton :
        {
            if(this->selectedIndexes().size() == 1)
            {
                this->renameAction->setEnabled(true);
                this->removeAction->setEnabled(true);

                QFileInfo fileInfo = QFileInfo(this->worldModel->filePath(this->selectedIndexes().at(0)));

                if(fileInfo.isDir())
                {
                    this->duplicateAction->setEnabled(false);
                }
                else
                {
                    this->duplicateAction->setEnabled(true);
                }

                this->contextMenu->exec(this->mapToGlobal(event->pos()));
            }
            else if(this->selectedIndexes().size() == 0)
            {
                this->renameAction->setEnabled(false);
                this->duplicateAction->setEnabled(false);
                this->removeAction->setEnabled(false);
                this->contextMenu->exec(this->mapToGlobal(event->pos()));
            }

            break;
        }

        default: break;
    }

    this->QTreeView::mouseReleaseEvent(event);

    return;
}

void WorldFileTree::mousePressEvent(QMouseEvent *event)
{
    this->QTreeView::mousePressEvent(event);

    switch(event->button())
    {
        case Qt::LeftButton :
        {
            if(this->selectedIndexes().size() == 1)
            {
                this->draggedIndex = this->selectedIndexes().at(0);
            }
            break;
        }
        default: break;
    }

    return;
}

void WorldFileTree::dragMoveEvent(QDragMoveEvent *event)
{
    this->setCurrentIndex(this->indexAt(event->pos()));
    this->QTreeView::dragMoveEvent(event);
    return;
}

void WorldFileTree::dropEvent(QDropEvent *)
{
    if(this->selectedIndexes().size() == 1)
    {
        this->processor->execute(new MoveFile(this->draggedIndex, this->selectedIndexes().at(0)));
    }
    else if(this->selectedIndexes().empty())
    {
        this->processor->execute(new MoveFile(this->draggedIndex, this->rootIndex()));
    }
    return;
}

void WorldFileTree::indexDoubleClicked(QModelIndex index)
{
    this->processor->execute(new LoadMapByIndex(index));
    return;
}

void WorldFileTree::updateRootIndex()
{
    this->setRootIndex(worldModel->index(worldModel->refWorldFileInfo()->absolutePath()));
    return;
}

void WorldFileTree::updateColumnWidth()
{
    this->resizeColumnToContents(0);
    return;
}

void WorldFileTree::newMap()
{
    QModelIndex index;

    if(this->selectedIndexes().empty())
    {
        index = this->rootIndex();
    }
    else
    {
        index = this->selectedIndexes().at(0);
    }

    this->processor->execute(new NewMapFile(index, this->worldModel));

    return;
}

void WorldFileTree::newFolder()
{
    QModelIndex index;

    if(this->selectedIndexes().empty())
    {
        index = this->rootIndex();
    }
    else
    {
        index = this->selectedIndexes().at(0);
    }

    this->processor->execute(new NewFolder(index, this->worldModel));

    return;
}

void WorldFileTree::rename()
{
    this->processor->execute(new RenameWorldEntry(this->selectedIndexes().at(0)));
    return;
}

void WorldFileTree::duplicate()
{
    this->processor->execute(new DuplicateWorldEntry(this->selectedIndexes().at(0)));
    return;
}

void WorldFileTree::remove()
{
    this->processor->execute(new RemoveWorldEntry(this->selectedIndexes().at(0), true));
    return;
}
