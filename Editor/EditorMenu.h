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

#ifndef EDITOR_MENU_H
#define EDITOR_MENU_H

#include <QEvent>
#include <QMenuBar>
#include <QMenu>

#include "Editor/Model/EditorModel.h"
#include "Editor/Model/WorldModel.h"
#include "Editor/MapPropertiesDialog.h"
#include "Editor/WorldPropertiesDialog.h"
#include "Command/Processor.h"

/** \addtogroup GUI
  * \{
  * \class EditorMenu
  *
  * \brief Represents the menubar of the editor.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class EditorMenu : public QMenuBar
{
    Q_OBJECT

private:
    Processor *             processor;
    EditorModel *           editorModel;
    WorldModel *            worldModel;

    MapPropertiesDialog     mapPropertiesDialog;
    WorldPropertiesDialog   worldPropertiesDialog;

    // Actions
    // File
    QMenu *                 fileMenu;

    QAction *               newWorldAction;
    QAction *               saveMapAction;
    QAction *               saveMapAsAction;
    QAction *               saveWorldAction;
    QAction *               saveWorldAsAction;
    QAction *               loadWorldAction;
    QAction *               quitAction;

    // Edit
    QMenu *                 editMenu;

    QAction *               undoAction;
    QAction *               redoAction;

    QAction *               mapPropertiesAction;
    QAction *               worldPropertiesAction;

    // View
    QMenu *                 viewMenu;

    QMenu *                 zoomMenu;
    QActionGroup *          zoomActionGroup;

    // Help
    QMenu *                 helpMenu;

    QAction *               aboutAction;

public:
    explicit EditorMenu(Processor *processor, EditorModel *editorModel, WorldModel *worldModel, QWidget *parent = 0);

    void updateSize(int horizontal, int vertical, int maxHeight);

public slots:
    /**
      * \brief Create and save a new empty World, load it into the world model and open a new empty map.
      */
    void createNewWorld();

    /**
      * \brief Save map as is. If unsafed map, use Save As.
      */
    void saveMap();

    /**
      * \brief Save map as a new map.
      */
    void saveMapAs();

    /**
      * \brief Save world as is.
      */
    void saveWorld();

    /**
      * \brief Save a copy of the world and its maps under a new path.
      */
    void saveWorldAs();

    /**
      * \brief Load an existing world and its designated first map.
      */
    void loadWorld();

    /**
      * \brief Undo last command.
      */
    void useUndo();

    /**
      * \brief Redo last undone command.
      */
    void useRedo();

    /**
      * \brief Shows the map properties dialog to edit them.
      */
    void showMapProperties();

    /**
      * \brief Shows the world properties dialog to edit the world.
      */
    void showWorldProperties();

    /**
      * \brief Zoom the map.
      */
    void zoom(QAction *zoomAction);

    /**
      * \brief Quit editor.
      */
    void quit();

    /**
      * \brief Show an about dialog.
      */
    void about();
};

#endif // EDITOR_MENU_H
