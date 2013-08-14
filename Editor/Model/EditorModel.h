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

#ifndef EDITOR_MODEL_H
#define EDITOR_MODEL_H

#include <QObject>

#include "Object/ObjectBase.h"

namespace PIDGIRL
{
    /**
      * \enum MainToolButton
      * \brief Represents every maintool button.
      */
    enum MainToolButton {START_POSITION=0, BRICKWALL};
}

/** \addtogroup Model
  * \{
  * \class EditorModel
  *
  * \brief Represents the editor state.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class EditorModel : public QObject
{
private:
    Q_OBJECT

    bool        isEditor;         ///< Is true, if the programm ist used as a editor.
    ObjectBase *mainToolObject;   ///< The object that is to be used, when setting the object.

public:
    explicit EditorModel(bool isEditor, QObject *parent = 0);

    // Get-Methods
    bool getIsEditor() const;

    // Set-Methods
    void setMainToolObject(ObjectBase* object);

    // Ref-Methods
    ObjectBase *refMainObject();
};

#endif // EDITOR_MODEL_H
