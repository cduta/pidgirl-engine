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

#ifndef MAP_PROPERTIES_DIALOG_H
#define MAP_PROPERTIES_DIALOG_H

#include <QDialog>
#include <QAction>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

#include "Command/Processor.h"
#include "Common/OptionsLayout.h"

/** \addtogroup GUI
  * \{
  * \class MapInfos
  *
  * \brief Information about maps.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MapPropertiesDialog : public QDialog
{
    Q_OBJECT

private:
    Processor *     processor;

    OptionsLayout * optionsLayout;

    // Stacked Widgets
    QWidget *       geometryPropetries;
    QGridLayout *   geometryPropetriesLayout;

    // Geometry Widgets
    QSpinBox *      horizontalSquareSpinBox;
    QComboBox *     horizontalSquareSideComboBox;

    QSpinBox *      verticalSquareSpinBox;
    QComboBox *     verticalSquareSideComboBox;

    QSpinBox *      maxHeightSpinBox;
    QComboBox *     maxHeightComboBox;

public:
    explicit MapPropertiesDialog(Processor *processor, QWidget *parent = 0);
    
public:
    void updateHorizontal(int horizontalSize);
    void updateVertical(int verticalSize);
    void updateMaxHeight(int maxHeight);

private slots:
    void applyChanges();
};

#endif // MAP_PROPERTIES_DIALOG_H
