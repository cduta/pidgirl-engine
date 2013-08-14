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

#ifndef WORLD_PROPERTIES_DIALOG_H
#define WORLD_PROPERTIES_DIALOG_H

#include <QDialog>
#include <QTreeView>
#include <QListView>
#include <QPushButton>
#include <QFileSystemModel>
#include <QStandardItemModel>

#include "Command/Processor.h"
#include "Editor/Model/WorldModel.h"
#include "Common/OptionsLayout.h"

/** \addtogroup GUI
  * \{
  * \class WorldPropertiesDialog
  *
  * \brief Shows the properties of a world to change it.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class WorldPropertiesDialog : public QDialog
{
    Q_OBJECT
private:
    Processor *         processor;
    WorldModel *        worldModel;

    OptionsLayout *     optionsLayout;

    // Widgets
    QWidget *           manageStartingMaps;

    // Starting Maps Widgets
    QTreeView *         availableTreeView;
    QFileSystemModel *  availableFileSystemModel;

    QListView *         chosenListView;
    QStandardItemModel *chosenListModel;

    // Starting Maps Buttons
    QPushButton *       addButton;
    QPushButton *       removeButton;

    // Layouts
    QGridLayout *       manageStartingMapsLayout;

public:
    WorldPropertiesDialog(Processor *processor, WorldModel *worldModel, QWidget *parent = 0);

    void updateChosenMaps();

public slots:
    int exec();

    void addPathToChosen();

    void removePathFromChosen();

    void applyChanges();

    void updateAvailableFileSystemModel();

private slots:
    void availableTreeUpdateColumnWidth();
};

#endif // WORLD_PROPERTIES_DIALOG_H
