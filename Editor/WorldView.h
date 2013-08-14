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

#ifndef WORLD_VIEW_H
#define WORLD_VIEW_H

#include <QWidget>

#include "Command/Processor.h"
#include "Editor/WorldFileTree.h"
#include "Editor/Model/WorldModel.h"

/** \addtogroup GUI
  * \{
  * \class WorldView
  *
  * \brief The widget of the world Management.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class WorldView : public QWidget
{
    Q_OBJECT

    Processor *       processor;
    WorldModel *      worldModel;

    WorldFileTree *   fileTree; ///< The world file tree representing the world and its maps.

public:
    explicit WorldView(Processor *processor, WorldModel *worldModel, QWidget *parent = 0);

public slots:
    void resizeWorldView();
};

#endif // WORLD_VIEW_H
