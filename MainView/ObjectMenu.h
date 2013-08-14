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

#ifndef OBJECT_MENU_H
#define OBJECT_MENU_H

#include <QMenu>

#include "Command/Processor.h"
#include "Object/ObjectBase.h"

/** \addtogroup GUI
  * \{
  * \class ObjectMenu
  *
  * \brief The menu which is created by the command actions created through the given object.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class ObjectMenu : public QMenu
{
    Q_OBJECT
    Processor * processor;
    ObjectBase *object;    ///< The copy of a given object which is constant here. If any changes are to be made to this, they won't be shown on the actual object and vice versa.

public:
    ObjectMenu(ObjectBase *object, Processor *processor, QWidget *parent = 0);

private slots:
    void triggerCommandByName(const QString &name);
};

#endif // OBJECT_MENU_H
