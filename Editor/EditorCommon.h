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

#ifndef EDITOR_COMMON_H
#define EDITOR_COMMON_H

/**
  * \brief The PIDGIRL namespace.
  */
namespace PIDGIRL
{
    /**
      * \brief The width of the Editor View.
      */
    const int EDITOR_VIEW_WIDTH = 200;

    /**
      * \brief The minimal height of the Editor View.
      */
    const int EDITOR_VIEW_HEIGHT = 250;

    /**
      * \brief The amount of tool buttons per row.
      */
    const int TOOL_BUTTON_COUNT_IN_ROW = 4;
}

#endif // EDITOR_COMMON_H
