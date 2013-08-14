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

#ifndef MOUSE_EDITOR_INPUT_H
#define MOUSE_EDITOR_INPUT_H

#include <QMenu>
#include <QAction>

#include "MainView/Model/MouseInput/MouseInput.h"

/** \addtogroup State
  * \{
  * \class MouseEditorInput
  *
  * \brief The mouse input manager for the editor.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MouseEditorInput : public MouseInput
{
    Q_OBJECT

    StackModel *    contextMenuStack;

    // Editor Menus
    QMenu *         characterMenu;
    QMenu *         wallMenu;
    QMenu *         floorMenu;
    QMenu *         itemsMenu;
    QMenu *         specialsMenu;

    // Actions
    // Editor
    QAction *       copyCharacterAction;
    QAction *       cutCharacterAction;
    QAction *       removeCharacterAction;
    QAction *       editCharacterAction;

    QAction *       copyWallAction;
    QAction *       cutWallAction;
    QAction *       removeWallAction;
    QAction *       editWallAction;

    QAction *       copyFloorAction;
    QAction *       cutFloorAction;
    QAction *       removeFloorAction;
    QAction *       editFloorAction;

    QAction *       copyItemsAction;
    QAction *       cutItemsAction;
    QAction *       removeItemsAction;
    QAction *       editItemsAction;

    QAction *       copySpecialsAction;
    QAction *       cutSpecialsAction;
    QAction *       removeSpecialsAction;
    QAction *       editSpecialsAction;

    QAction *       pasteObjectAction;

    QAction *       removeAllAction;

public:
    MouseEditorInput(GameModel *gameModel, MapModel *mapModel, Processor *processor, QObject *parent = 0);

    virtual void nextState(MouseState::MouseEventType type, QMouseEvent *event, StackModel *targetStack);

    void showEditorContextMenu(StackModel *contextMenuStack);

private slots:
    /**
      * \brief Enables the remove all action, if there is anything on the stack.
      */
    void checkRemoveAllAction();

    /**
      * \brief Create a copy of the character to maybe paste it later.
      */
    void copyCharacter();

    /**
      * \brief Cut the character to maybe paste it later.
      */
    void cutCharacter();

    /**
      * \brief Set the character to 0. Should it have been already set to 0, do nothing.
      */
    void removeCharacter();

    /**
      * \brief Edit the character.
      */
    void editCharacter();

    /**
      * \brief Change the state of the actions associated with the character.
      */
    void checkCharacterActions();

    /**
      * \brief Create a copy of items to maybe paste it later.
      */
    void copyItems();

    /**
      * \brief Cut items to maybe paste it later.
      */
    void cutItems();

    /**
      * \brief Remove items from the stack.
      */
    void removeItems();

    /**
      * \brief Edit an item.
      */
    void editItems();

    /**
      * \brief Change the state of the actions associated with the items.
      */
    void checkItemsActions();

    /**
      * @brief Create a copy of specials to maybe paste it later.
      */
    void copySpecials();

    /**
      * @brief Cut specials to maybe paste them later.
      */
    void cutSpecials();

    /**
      * @brief Remove specials from the stack.
      */
    void removeSpecials();

    /**
      * @brief Edit a special.
      */
    void editSpecials();

    /**
      * @brief Change the stateo f the actions associated with the specials.
      */
    void checkSpecialsActions();

    /**
      * \brief Create a copy of the wall to maybe paste it later.
      */
    void copyWall();

    /**
      * \brief Cut the wall to maybe paste it later.
      */
    void cutWall();

    /**
      * \brief Set the wall to 0. Should it have been already set to 0, do nothing.
      */
    void removeWall();

    /**
      * \brief Edit the wall.
      */
    void editWall();

    /**
      * \brief Change the state of the actions associated with the wall.
      */
    void checkWallActions();

    /**
      * \brief Create a copy of the wall to maybe paste it later.
      */
    void copyFloor();

    /**
      * \brief Cut the wall to maybe paste it later.
      */
    void cutFloor();

    /**
      * \brief Set the wall to 0. Should it have been already set to 0, do nothing.
      */
    void removeFloor();

    /**
      * \brief Edit the wall.
      */
    void editFloor();

    /**
      * \brief Change the state of the actions associated with the floor.
      */
    void checkFloorActions();

    /**
      * \brief Change the state of the paste action according what object was given.
      */
    void checkPasteAction();

    /**
      * \brief Paste the content of the clipboard if it's not 0.
      */
    void pasteObject();

    /**
      * @brief Action represents the functionality to remove everything on a stack.
      */
    void removeAll();
};

#endif // MOUSE_EDITOR_INPUT_H
