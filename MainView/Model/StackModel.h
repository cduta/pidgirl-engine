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

#ifndef STACK_MODEL_H
#define STACK_MODEL_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QDataStream>
#include <QAction>
#include <QMouseEvent>

#include "Object/ObjectItem.h"
#include "Object/ObjectCharacter.h"
#include "Object/ObjectTile.h"
#include "Object/ObjectSpecial.h"

/** \addtogroup Model
  * \{
  * \class StackModel
  *
  * \brief A single stack (square) holding a stack of items and informations about the square which holds them.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class StackModel : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Indicates the path where the next step is going.
     * @note It is made, so that you can combine N and S with W and E with the logical OR or addition to result in a combination of both.
     */
    enum PathIndication {NONE=0,N=1,S=2,W=4,NW=5,SW=6,E=8,NE=9,SE=10,DESTINATION};

signals:
    void characterChanged();
    void startPositionSet(StackModel *);
    void startPositionRemoved(StackModel *);
    void playerSet(StackModel *);
    void playerRemoved(StackModel *);
    void itemListChanged();
    void specialListChanged();
    void pathIndicationChanged();
    void wallChanged();
    void floorChanged();

private:
    QPoint                  squarePos;
    int                     height;

    PathIndication          pathIndication;
    ObjectCharacter *       character;
    QList<ObjectItem *>     itemList;
    QList<ObjectSpecial *>  specialList;
    ObjectTile *            wall;
    ObjectTile *            floor;

public:
    explicit StackModel(int xPos, int yPos, int height, QObject *parent = 0);
    explicit StackModel(QPoint pos, int height, QObject *parent = 0);
    explicit StackModel(const StackModel& stackModel);

    /**
     * @brief Checks if the id is present on this stack.
     * @param id The id to be checked for.
     * @return True if the stack contains this special id.
     */
    bool specialIDExists(ObjectID::SpecialID id) const;

    /**
      * \brief Clear the stack.
      */
    void removeAll();

    /**
      * \brief Clear the stack and free all the memory.
      */
    void deleteAll();

    /**
      * \brief Initialize Attributes
      */
    void initStack(const QPoint &squarePos, int height);

    /**
      * \brief Delete the path direction.
      */
    void resetPathDirection();

    /**
      * \brief Prepend an item to the list of items.
      * \param item The item to be prepended.
      */
    void prependItem(ObjectItem *item);

    /**
      * \brief Remove i-th element from the list.
      * \param i The index of the element to be removed. 0 if no argument given.
      */
    void removeItem(int i = 0);

    /**
      * \brief Take i-th element from the list.
      * \param i The index of the element to be taken. 0 if no argument given.
      * \return The i-th element.
      */
    ObjectItem *takeItem(int i = 0);

    /**
      * \brief Delete the i-th element of the list by freeing the space and removing it from the list.
      * \param i The index of the element to be deleted. 0 if no argument given.
      */
    void deleteItem(int i = 0);

    /**
      * \brief Remove all items by removing it from the list.
      */
    void removeAllItems();

    /**
      * \brief Take the whole list of items.
      * \return A list with all items.
      */
    QList<ObjectItem *> takeAllItems();

    /**
      * \brief Delete all items by freeing the space and removing it from the list.
      */
    void deleteAllItems();

    /**
      * \brief Return the size of the list of items.
      * \return The size of the list of items.
      */
    int itemListSize() const;

    /**
      * @brief Prepend a special to the list of specials.
      * @param special The special to be prepended.
      */
    void prependSpecial(ObjectSpecial *special);

    /**
      * @brief Remove i-th element from the list.
      * @param i The index of the element to be removed. 0 if no argument given.
      */
    void removeSpecial(int i = 0);

    /**
      * @brief Take i-th element from the list.
      * @param i The index of the element to be taken. 0 if no argument given.
      * @return The i-th element.
      */
    ObjectSpecial *takeSpecial(int i = 0);

    /**
      * @brief Delete the i-th element of the list by freeing the space and removing it from the list.
      * @param i The index of the element to be deleted. 0 if no argument given.
      */
    void deleteSpecial(int i = 0);

    /**
      * @brief Remove all specials by removing it from the list.
      */
    void removeAllSpecials();

    /**
      * @brief Take the whole list of specials.
      * @return A list with all specials.
      */
    QList<ObjectSpecial *> takeAllSpecial();

    /**
      * @brief Delete all specials by freeing the space and removing it from the list.
      */
    void deleteAllSpecials();

    /**
      * \brief Return the size of the list of specials.
      * \return The size of the list of specials.
      */
    int specialListSize() const;

    /**
      * @brief Check if special can be fit into the list of specials.
      * @param special The special to be checked if there is still space left to put it in.
      * @return True if it fits, False otherwise.
      */
    bool hasSpaceForSpecial(ObjectSpecial *special) const;

    /**
      * \brief Replace the old primary character.
      * \param primaryCharacter The primary character to be added to this stack.
      * \returns The old primary character or 0.
      */
    ObjectCharacter *replaceCharacter(ObjectCharacter *character);

    /**
      * \brief Take the primary character and return it.
      * \returns The previously used primary character or 0.
      */
    ObjectCharacter *takeCharacter();

    /**
      * \brief Remove the primary character by setting it to 0.
      */
    void removeCharacter();

    /**
      * \brief Delete the primary character by freeing the space and setting it to 0.
      */
    void deleteCharacter();

    /**
      * @brief Checks if there is already a character set.
      * @return Returns true, if the stack already has a character. Otherwise, false.
      */
    bool hasCharacter() const;

    /**
      * @brief Checks if a given character exists.
      * @param character The character to be checked.
      * @return Returns true, if there exists the given character. Otherwise false.
      */
    bool characterExists(ObjectCharacter *character) const;
    bool characterExists(ObjectID::CharacterID characterID, unsigned int spawnID) const;

    /**
      * \brief Replace the old wall.
      * \param wall The wall to be added to this stack.
      * \returns The old wall or 0.
      */
    ObjectTile *replaceWall(ObjectTile *wall);

    /**
      * \brief Take the wall and return it.
      * \returns The previously used wall or 0.
      */
    ObjectTile *takeWall();

    /**
      * \brief Remove the wall by setting it to 0.
      */
    void removeWall();

    /**
      * \brief Delete the wall by freeing the space and setting it to 0.
      */
    void deleteWall();

    /**
      * @brief Checks if there is already a wall set.
      * @return Returns true, if the stack already has a wall. Otherwise, false.
      */
    bool hasWall() const;

    /**
      * \brief Replace the old floor.
      * \param wall The floor to be added to this stack.
      * \returns The old floor or 0.
      */
    ObjectTile *replaceFloor(ObjectTile *floor);

    /**
      * \brief Take the floor and return it.
      * \returns The previously used floor or 0.
      */
    ObjectTile *takeFloor();

    /**
      * \brief Remove the floor by setting it to 0.
      */
    void removeFloor();

    /**
      * \brief Delete the floor by freeing the space and setting it to 0.
      */
    void deleteFloor();

    /**
      * @brief Checks if there is already a floor set.
      * @return Returns true, if the stack already has a floor. Otherwise, false.
      */
    bool hasFloor() const;

public:
    // Get-Methods
    QPoint getSquarePos() const;
    int getHeight() const;
    bool isEmpty() const;

    // Set-Methods
    void setPosition(int x, int y, int z);
    void setItemList(const QList<ObjectItem *> &itemList);
    void setSpecialList(const QList<ObjectSpecial *> &specialList);
    void setPathIndication(StackModel::PathIndication pathIndication);
    void setCharacter(ObjectCharacter *character);
    void setWall(ObjectTile *wall);
    void setFloor(ObjectTile *floor);

    // Ref-Methods
    StackModel::PathIndication getPathIndication() const;
    ObjectCharacter *refCharacter() const;
    QList<ObjectItem *> *refItemList();
    ObjectItem *refItem(int i) const;
    QList<ObjectSpecial *> *refSpecialList();
    ObjectSpecial *refSpecial(int i) const;
    ObjectTile *refWall() const;
    ObjectTile *refFloor() const;

    // Serialize
    void serialize(QDataStream &dataStream) const;
    void deserialize(QDataStream &dataStream);
};
#endif // STACK_MODEL_H
