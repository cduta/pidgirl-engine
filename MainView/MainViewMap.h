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

#ifndef MAIN_VIEW_MAP_H
#define MAIN_VIEW_MAP_H

#include <QWidget>

#include "Command/Processor.h"
#include "Editor/Model/EditorModel.h"
#include "MainView/MainViewStack.h"
#include "MainView/Model/StackModel.h"
#include "MainView/Model/MapModel.h"
#include "MainView/Model/MouseInput/MouseInput.h"
#include "Game/Model/GameModel.h"

/** \addtogroup GUI
  * \{
  * \class MainViewMap
  *
  * \brief The main view showing every stack on an grid.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MainViewMap : public QWidget
{
    Q_OBJECT

signals:
    void mapSizeUpdated();

private:
    Processor *     processor;

    EditorModel *   editorModel;
    MapModel *      mapModel;
    GameModel *     gameModel;
    MouseInput *    mouseInput;

    QVector
    <QVector
    <MainViewStack *> > stackGrid;
public:
    explicit MainViewMap(Processor *processor, MapModel *mapModel, EditorModel *editorModel, GameModel *gameModel, QWidget *parent);

private slots:

    /**
      * \brief Paints the grid.
      */
    void paintGrid();

    /**
      * \brief Update the complete stack grid.
      */
    void updateMap();

protected:
    /**
      * \brief Overload paint event to make the mainview view draw itself everytime it needs to be updated.
      */
    virtual void paintEvent(QPaintEvent *);

private:
    /**
      * \brief Create an mainViewStack.
      * \param x X Coordinate for the MainViewStack.
      * \param y Y Coordinate for the MainViewStack.
      */
    void createStackGrid(int x, int y);

    /**
      * \brief Delete and set to 0 one of the mainViewStack.
      * \param x X Coordinate for the MainViewStack.
      * \param y Y Coordinate for the MainViewStack.
      */
    void deleteStackGrid(int x, int y);

private slots:
    void showContextMenu(StackModel *stackModel);
};

#endif // MAIN_VIEW_MAP_H
