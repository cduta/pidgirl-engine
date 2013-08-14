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

#ifndef SOLO_HOTSEAT_SETUP_WIDGET_H
#define SOLO_HOTSEAT_SETUP_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

/** \addtogroup GUI
  * \{
  * \class SoloHotseatSetupWidget
  *
  * \brief The widget to set up an Solo / Hotseat Game.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class SoloHotseatSetupWidget : public QWidget
{
    Q_OBJECT
public:
    QGridLayout *soloHotseatWidgetLayout;
    QPushButton *gameStartButton;

public:
    explicit SoloHotseatSetupWidget(QWidget *parent = 0);
};

#endif // SOLO_HOTSEAT_SETUP_WIDGET_H
