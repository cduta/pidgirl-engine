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

#ifndef WORLD_FILE_TREE_H
#define WORLD_FILE_TREE_H

#include <QTreeView>
#include <QMenu>
#include <QAction>

#include "Command/Processor.h"
#include "Editor/Model/WorldModel.h"

/** \addtogroup GUI
  * \{
  * \class WorldFileTree
  *
  * \brief Showing the FileTree of an opened world.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class WorldFileTree : public QTreeView
{
    Q_OBJECT

    Processor *     processor;
    WorldModel *    worldModel;
    QMenu *         contextMenu;

    QModelIndex     draggedIndex;

    // Actions
    QAction *       newMapAction;
    QAction *       newFolderAction;
    QAction *       renameAction;
    QAction *       duplicateAction;
    QAction *       removeAction;

public:
    explicit WorldFileTree(Processor *processor, WorldModel *worldModel, QWidget *parent = 0);

    // Ref-Methods
    QMenu *refContexMenu();

protected:
    /**
      * \brief The events that occur when the mousebutton is released.
      */
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void dragMoveEvent(QDragMoveEvent *event);

    virtual void dropEvent(QDropEvent *);

private slots:
    /**
      * \brief The slot that occurs when someone doubleclicks on an entry.
      */
    void indexDoubleClicked(QModelIndex index);

    /**
      * \brief Update the index according to the fileinfo located in the worldWorld.
      */
    void updateRootIndex();

    /**
      * \brief Update the column width according to whatever is to be shown.
      */
    void updateColumnWidth();

    /**
      * \brief Create a new map.
      */
    void newMap();

    /**
      * \brief Create a new folder.
      */
    void newFolder();

    /**
      * \brief Rename a selected entry.
      */
    void rename();

    /**
      * \brief Duplicate a selected entry.
      */
    void duplicate();

    /**
      * \brief Remove a selected entry.
      */
    void remove();
};

#endif // WORLD_FILE_TREE_H
