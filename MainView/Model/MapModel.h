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

#ifndef MAP_MODEL_H
#define MAP_MODEL_H

#include <QSize>
#include <QObject>
#include <QPoint>
#include <QFileInfo>

#include "MainView/Model/StackModel.h"
#include "Object/ObjectBase.h"
#include "Common/Serialize.h"
#include "AStar/AStarMapEntry.h"

/** \addtogroup Model
  * \{
  * \class MapModel
  *
  * \brief Represents the map.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MapModel : public QObject, public Serialize
{
    Q_OBJECT

public:
    enum Side {Left=0, Right};

signals:
    void gridChanged();
    void horizontalSizeChanged();
    void verticalSizeChanged();
    void heightSizeChanged();
    void squareSizeChanged();
    void gridLineSizeChanged();
    void clipboardObjectSet();
    void mapPathChanged();

private:
    QVector
    <QVector
    <QVector
    <StackModel *> > >      stackModelGrid;         ///< The actual representation of the mainView map as a grid.

    QString                 localMapPath;        ///< Is the unique ID and path for this map.
    int                     squareSize;             ///< The size of a single square on the mainView grid.
    int                     gridLineSize;           /** \brief The size of the grid lines.
                                                      * It works that 0 means there will be only a line with a width of 1px.
                                                      * Therefore 1 means that the width will be increased by one on both sides of the line,
                                                      * resulting in a line with a width of 3px. 2 would mean 5px and so on.
                                                      */
    int                     squareSizeZoomFactor;
    int                     currentHeight;
    QVector< StackModel *>  startPositionStacks;    ///< The stack of start positions.
    QVector< StackModel *>  playerStacks;           ///< The stacks of the player characters.
    QVector< StackModel *>  currentPath;            ///< The path that, if confirmed, will be taken by the current player.
    ObjectBase *            clipboardObject;        ///< The object that has been copied and will be pasted if issued.

public:
    explicit MapModel(QObject *parent = 0);
    explicit MapModel(int hSquareCount, int vSquareCount, int maxHeight, int gridLineSize, QObject *parent = 0);

private:
    /**
      * \brief First and only initialization of the map model for the first time.
      */
    void firstTimeInit();

public:

    /**
      * \brief Initialize the map model.
      */
    void initMapModel(int hSquareCount, int vSquareCount, int maxHeight, int gridLineSize);

    /**
      * \brief Resize the stack model grid.
      * \param hSquareCount The new horizontal square count.
      * \param hDirection Vertical resize direction.
      * \param vSquareCount The new vertical square count.
      * \param vDirection Horizontal resize direction.
      * \param maxHeight The new max height.
      * \param heightDirection Height resize direction.
      */
    void resizeStackModelGrid(int newHSquareCount, MapModel::Side hDirection, int newVSquareCount, MapModel::Side vDirection, int newMaxHeight, MapModel::Side heightDirection);


    /**
      * \brief Clear everything from the stack model grid.
      */
    void clearStackModelGrid();

    /**
      * \brief Clears the map model and loads the stnadard map.
      */
    void setNewStandardMap();

    /**
      * \brief Correct the position entries of every single stack model to represent their actual position.
      */
    void correctPositionEntries();

private:

    /**
      * \brief Create a new StackModel at a given position.
      * \param x The x position of the stack.
      * \param y The y position of the stack.
      * \param z The z position of the stack.
      */
    void createStackModelAt(int x, int y, int z);

    /**
      * \brief Remove a StackModel at a given position.
      * \param x The x position of the stack.
      * \param y The y position of the stack.
      * \param z The z position of the stack.
      */
    void removeStackModelAt(int x, int y, int z);

    /**
      * \brief Delete a StackModel at a given position.
      * \param x The x position of the stack.
      * \param y The y position of the stack.
      * \param z The z position of the stack.
      */
    void deleteStackModelAt(int x, int y, int z);

    /**
      * \brief Remove elements of the vector so the horizontal square count changes while still maintaining the other vectors from left.
      * \param amount The count to which the horizontal squares should be removed.
      * \param from The side from which to remove from.
      */
    void removeHorizontalLeft(int amount);

    /**
      * \brief Remove elements of the vector so the horizontal square count changes while still maintaining the other vectors from right.
      * \param amount The count to which the horizontal squares should be removed.
      * \param from The side from which to remove from.
      */
    void removeHorizontalRight(int amount);

    /**
      * \brief Append elements of the vector so the horizontal square count changes while still maintaining the other vectors from left.
      * \param amount The count to which the horizontal squares should be appended.
      * \param from The side from which to append from.
      */
    void appendHorizontalLeft(int amount);

    /**
      * \brief Append elements of the vector so the horizontal square count changes while still maintaining the other vectors from right.
      * \param amount The count to which the horizontal squares should be appended.
      * \param from The side from which to append from.
      */
    void appendHorizontalRight(int amount);

    /**
      * \brief Resize the vector so the horizontal square count changes while still maintaining the other vectors.
      * \param hSquareCount The count to which the horizontal squares should be appended or removed.
      * \param from The side from which to append or remove from.
      */
    void setHSquareCount(int hSquareCount, MapModel::Side from = MapModel::Right);

    /**
      * \brief Remove elements of the vector so the vertical square count changes while still maintaining the other vectors from left.
      * \param amount The count to which the vertical squares should be removed.
      */
    void removeVerticalLeft(int amount);

    /**
      * \brief Remove elements of the vector so the vertical square count changes while still maintaining the other vectors from right.
      * \param amount The count to which the vertical squares should be removed.
      */
    void removeVerticalRight(int amount);

    /**
      * \brief Append elements of the vector so the vertical square count changes while still maintaining the other vectors from left.
      * \param amount The count to which the vertical squares should be appended.
      * \param from The side from which to append from.
      */
    void appendVerticalLeft(int amount);

    /**
      * \brief Append elements of the vector so the vertical square count changes while still maintaining the other vectors from right.
      * \param amount The count to which the vertical squares should be appended.
      * \param from The side from which to append from.
      */
    void appendVerticalRight(int amount);

    /**
      * \brief Resize the vector so the vertical square count changes while still maintaining the other vectors.
      * \param vSquareCount The count to which the vertical squares should be appended or removed.
      * \param from The side from which to append or remove from.
      */
    void setVSquareCount(int vSquareCount, MapModel::Side from = MapModel::Right);

    /**
      * \brief Remove elements of the vector so the height square count changes while still maintaining the other vectors.
      * \param amount The count to which the height squares should be removed.
      * \param from The side from which to remove from.
      */
    void removeHeightLeft(int amount);

    /**
      * \brief Remove elements of the vector so the height square count changes while still maintaining the other vectors.
      * \param amount The count to which the height squares should be removed.
      * \param from The side from which to remove from.
      */
    void removeHeightRight(int amount);

    /**
      * \brief Append elements of the vector so the height square count changes while still maintaining the other vectors.
      * \param amount The count to which the height squares should be appended.
      * \param from The side from which to append from.
      */
    void appendHeightLeft(int amount);

    /**
      * \brief Append elements of the vector so the height square count changes while still maintaining the other vectors.
      * \param amount The count to which the height squares should be appended.
      * \param from The side from which to append from.
      */
    void appendHeightRight(int amount);

    /**
      * \brief Resize the vector so the height square count changes while still maintaining the other vectors.
      * \param vSquareCount The count to which the height squares should be appended or removed.
      * \param from The side from which to append or remove from.
      */
    void setMaxHeight(int maxHeight, MapModel::Side from = MapModel::Right);

public:

    /**
      * \brief Clear the current path.
      */
    void clearPath();

public:
    // Get-Methods
    QString getLocalMapPath() const;
    int getHSquareCount() const;
    int getVSquareCount() const;
    int getSquareSizeZoomFactor() const;
    int getSquareSize() const;
    int getGridLineSize() const;
    int getMaxHeight() const;
    int getCurrentHeight() const;
    QSize getMapSize() const;
    QVector<StackModel *> getCurrentPath() const;
    bool hasStartPositions() const;

    // Set-Method
public slots:
    void addStartPositionStack(StackModel *startPositionStack);
    void removeStartPositionStack(StackModel *startPositionStack);
    void addPlayerStack(StackModel *playerStacks);
    void removePlayerStack(StackModel *playerStack);
public:
    void setLocalMapPath(const QString &localMapPath);
    void setSquareSizeZoomFactor(int zoomFactor);
    void updateSquareSize();
    void setGridLineSize(int gridLineSize, bool willEmit = true);
    void setCurrentHeight(int currentHeight);
    void setClipboardObject(ObjectBase *object);
    void setConvertedPath(QVector<AStarMapEntry> path);

    // Ref-Methods
    StackModel *refStartPositionStack() const;
    StackModel *refPlayerStack(unsigned int playerID) const;
    StackModel *refDestinationStackModel() const;
    StackModel *refStackModel(int x, int y) const;
    StackModel *refStackModel(int x, int y, int z) const;
    StackModel *refStackModel(const QPoint &pos) const;
    ObjectBase *refClipboardObject() const;

    // Serialize
    virtual void serialize(QIODevice *device) const;
    void serialize(QDataStream &dataStream) const;
    virtual void deserialize(QIODevice *device);
    void deserialize(QDataStream &dataStream);
};

#endif // MAP_MODEL_H
