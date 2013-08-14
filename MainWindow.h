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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "Editor/EditorTools.h"
#include "Editor/EditorMenu.h"
#include "Editor/WorldView.h"
#include "Editor/Model/EditorModel.h"
#include "Editor/Model/WorldModel.h"
#include "Game/Model/GameModel.h"
#include "MainView/MainViewMap.h"
#include "MainView/Model/MapModel.h"
#include "Command/Processor.h"
#include "Common/Common.h"

namespace PIDGIRL
{
    /**
      * \brief Needed for canceling the program before the application has been started yet (Before app.exec() in main()). Only set with the Quit Command.
      **/
    extern bool done;
}

/** \addtogroup GUI
  * \{
  * \class MainWindow
  *
  * \brief Holds all the models and GUIs and initializes them.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void windowSizeChanged();

private:
    EditorModel *       editorModel;
    WorldModel *        worldModel;
    MapModel *          mapModel;

    MainViewMap *       mainViewMap;    ///< The MainView Map that represents the world, the game takes place in.
    EditorTools *       editorTools;    ///< The tools dialog for the editor.
    EditorMenu *        editorMenu;     ///< The menu dialog, having all sorts of functionallity to change editor and game related things.
    WorldView *         worldView;      ///< The side pane, showing the world structure and maps.

    GameModel *         gameModel;

    QDockWidget *       editorToolsDock;
    QDockWidget *       worldViewDock;

    Processor *         processor;

    bool                done;

public:
    explicit MainWindow(QWidget *parent = 0);

private:
    /**
      * \brief Initialize the main window completely.
      * \returns If the initialization was a success.
      */
    void init();

    /**
      * \brief Initialize the editor correctly.
      * Make user choose wether to load an existing editor or create a new one.
      * \returns If the initialization was a success.
      */
    bool initializeEditor();

    /**
      * \brief Initialize Game, so the current map can be loaded.
      * Make the user choose wether to start a new game, load an existing game (I.e.: E-Mail Game),
      * set some options (if any) or exit the game.
      * \returns If the initialization was a success.
      */
    bool initializeGame();

private slots:
    /**
      * \brief Updates the size of the main window depending on the mapsize.
      */
    void updateSize();

    /**
      * \brief Updates the size of the main window depending on the mapsize and the dockwidgets.
      */
    void updateEditorSize();

    /**
      * \brief Updates the title of the window to whatever the current mapfilename is.
      */
    void updateWindowTitle();

    /**
      * \brief Creates a new MainViewMap.
      */
    void createMainViewMap();

    /**
      * @brief Sets a new map.
      * @param mapModel The given map to be set.
      */
    void setNewMap(MapModel *mapModel);

protected:
    virtual void closeEvent(QCloseEvent *event);
};

#endif // MAIN_WINDOW_H
