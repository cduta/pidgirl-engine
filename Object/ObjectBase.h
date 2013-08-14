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

#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDataStream>
#include <QImage>

#include "Object/ObjectImage.h"
#include "Object/ObjectID.h"
#include "Command/Backend/BaseCommand.h"
#include "Common/Serialize.h"

/** \addtogroup Object
  * \{
  * \class ObjectBase
  *
  * \brief The baseclass for the Objects to be placed into the game's mainView.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ObjectBase : public QObject, public Serialize
{
    Q_OBJECT

public:
    /**
      * \enum ObjectType
      * \brief Specifies the type of the object via an enum value.
      */
    enum ObjectType {ITEM, CHARACTER, SPECIAL, TILE};

protected:
    int                     x,y,z;          ///< The position of the objects. (-1,-1,-1), if not set anywhere.
    unsigned int            spawnID;        ///< Denotes the spawn of that object. UINT_MAX when initialized.

    QString                 description;    ///< Description of this object.

    QVector<ObjectImage>    imageList;      ///< The list of images shown and their respective paths.
    int                     usedImageIndex; /** \brief Represents the image to be shown in \a imageList.
                                              * Can't be less than 0 or more than the \a imageList.size()-1.
                                              * In case of -1, there is no image to be shown in the list.
                                              */
    bool                    isVisible;      ///< True, if you want to show the image.

public:
    explicit ObjectBase();
    explicit ObjectBase(const ObjectBase& objectBase);
    explicit ObjectBase(const QString &name, const QString &description, const QString &imagePath, bool isVisible = true, QObject *parent = 0);
    explicit ObjectBase(const QString &name = "", const QString &description = "", bool isVisible = true, QObject *parent = 0);

protected:
    /**
      * \brief Initialize Attributes.
      */
    void initObjectBase(const QString &name = "", const QString &description = "", int usedImageIndex = -1, bool isVisible = true);
    void initObjectBase(const QVector<QString> &imagePathList, const QString &name = "", const QString &description = "", int usedImageIndex = -1, bool isVisible = true);

public:

    // ImageList functionality.

    /**
      * \brief Clear the list of images and set the \a usedImageIndex to -1.
      */
    void clearImageList();

    /**
      * \brief Load and append an image from a given path.
      * The \a usedImageIndex will be set to 0, if it was -1 before.
      * \param imagePath The path to the image to be loaded.
      */
    void appendImage(const QString &imagePath);

    /**
      * \brief Load and append an image from a given path.
      * The \a usedImageIndex will be set to 0, if it was -1 before.
      * \param imagePath The path to the image to be loaded.
      */
    void appendImages(const QVector<QString>& imagePathList);

    /**
      * \brief Loads an image from a path.
      * Clears the vector of images and sets a new one at position. \a usedImageIndex to 0.
      * \param imagePath Is the path to the image used.
      */
    void loadImage(const QString &imagePath);

    /**
      * \brief Clears and then appends a new list of images.
      * \a usedImageIndex will be set to 0.
      * \param imagePathList A list containing the paths to all the images to be loaded.
      */
    void loadImages(const QVector<QString>& imagePathList);

    /**
      * \brief Toggle visibility of an object.
      */
    void toggleVisibility();

    /**
      * @brief Create a copy of the object.
      */
    virtual ObjectBase *copyBase() const = 0;

    /**
      * @brief Checks if position is (-1,-1,-1) or not. If it's a mix, something went wrong.
      * @returns
      */
    virtual bool isSet() const;

    /**
      * @brief Set the positions to (-1,-1,-1) to indicate the unset state.
      */
    void unsetPosition();

    /**
      * @brief Updates this object with another object.
      * @param object The object to be updating with.
      */
    void updateBase(const ObjectBase &object);
    virtual void update(const ObjectBase &object) = 0;

    /**
      * @brief Create an information widget from an object to show informations about it.
      * @param parent The parent for the created information widget.
      * @return The widget that represents this object.
      */
    virtual QWidget *createInformationWidget(QWidget *parent) const = 0;

public:
    // Get-Methods
    virtual ObjectType getType() const = 0;
    virtual int getObjectIDNumber() const = 0;
    QVector<QString> getImagePathList() const;
    QString getCurrentImagePath() const;
    int getUsedImageIndex() const;
    QString getObjectName() const;
    bool getIsVisible() const;
    unsigned int getSpawnID() const;
    int getX() const;
    int getY() const;
    int getZ() const;
    virtual QMap<QString, BaseCommand *> getCommandList() const = 0;
    QString getDescription() const;

    // Set-Methods
    void setUsedImageIndex(int usedImageIndex);
    void setIsVisible(bool isVisible);
    void setSpawnID(unsigned int spawnID);
    void setPosition(int x, int y, int z);
    void setDescription(const QString &description);

    // Ref-Methods
    /**
      * \brief Reference the image given by the \a usedImageIndex.
      * \returns A image from the \a imageList or NULL, if the \a usedImageIndex was out-of-range
      * or if the object isn't visible.
      */
    QImage *refImage();

    /**
      * \brief Reference the image given by the given \a index.
      * \param index The index of whichever image from the \a imageList.
      * \returns A image from the \a imageList or NULL, if the \a index was out-of-range
      * ot if the object isn't visible.
      */
    QImage *refImage(int index);

    // Serialize
    virtual void serialize(QDataStream &dataStream) const;
    virtual void serialize(QIODevice *device) const = 0;
    virtual void deserialize(QDataStream &dataStream);
    virtual void deserialize(QIODevice *device) = 0;
};

#endif // OBJECT_BASE_H
