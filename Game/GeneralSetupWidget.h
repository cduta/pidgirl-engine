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

#ifndef GENERAL_SETUP_WIDGET_H
#define GENERAL_SETUP_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QCheckBox>

#include "Editor/Model/WorldModel.h"

/** \addtogroup GUI
  * \{
  * \class GeneralSetupWidget
  *
  * \brief The widget to set up general options for every game before it begins.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class GeneralSetupWidget : public QWidget
{
    Q_OBJECT

public:
    QGridLayout *       generalSetupWidgetLayout;
    QCheckBox *         playerChoosesStartLocation;

public:
    explicit GeneralSetupWidget(QWidget *parent = 0);
};

#endif // GENERAL_SETUP_WIDGET_H
