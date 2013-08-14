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

#ifndef MAIN_VIEW_STACK_H
#define MAIN_VIEW_STACK_H

#include <QWidget>
#include <QMenu>

#include "MainView/Model/StackModel.h"
#include "MainView/Model/MapModel.h"
#include "MainView/Model/MouseInput/MouseInput.h"
#include "Editor/Model/EditorModel.h"
#include "Command/Processor.h"

/** \addtogroup GUI
  * \{
  * \class MainViewStack
  *
  * \brief Graphicaly represents a stack of a square in the game.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MainViewStack : public QWidget
{
    Q_OBJECT

private:
    Processor *     processor;

    StackModel *    stackModel;
    MapModel *      mapModel;
    EditorModel *   editorModel;
    GameModel *     gameModel;
    MouseInput *    mouseInput;

public:
    explicit MainViewStack(Processor *processor, StackModel *stackModel, MapModel *mapModel, EditorModel *editorModel, GameModel *gameModel, MouseInput *mouseInput, QWidget *parent = 0);

    /**
      * \brief Draw a given object.
      * \param painter The painter with which to paint the given object.
      * \param objectBase The object to be painted.
      */
    void drawObject(QPainter *painter, ObjectBase *objectBase);

    /**
      * @brief Draw a direction indicator if there is one.
      */
    void drawDirectionIndicator(QPainter *painter);

    /**
      * \brief Override paint event to make the mainView Stack draw itself everytime it needs to be updated.
      */
    virtual void paintEvent(QPaintEvent *);

protected:
    /**
      * \brief The events that occur when the mousebutton is pressed.
      */
    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

public:
    // Set-Methods
    void setStackModel(StackModel *stackModel);

public slots:
    /**
      * \param Update all buttons.
      */
    void updateAll();

private slots:
    // General Slots
    /**
      * \param Update size of the stack.
      */
    void updateSize();
};

#endif // MAIN_VIEW_STACK_H
