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

#ifndef CREATE_CHARACTER_H
#define CREATE_CHARACTER_H

#include <QDialog>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QVector>
#include <QLabel>

#include "Command/Backend/Game/GameCommand.h"
#include "Common/OptionsLayout.h"
#include "Common/FileManager.h"

/** \addtogroup Commands
  * \{
  * \class CreateCharacter
  *
  * \brief Create a character and put his starting information into the game model.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class CreateCharacter : public GameCommand
{
    Q_OBJECT
private:
    // Character Creation Dialog Information
    QDialog                     characterCreationDialog;
    OptionsLayout *             characterCreationLayout;

    // Information Widget
    QWidget *                   informationWidget;
    QGridLayout *               informationWidgetLayout;
    QRegExpValidator            playerNameValidator;
    QLineEdit *                 playerNameEdit;

    // Start Map Chooser
    QWidget *                   chooseStartMap;
    QGridLayout *               chooseStartMapLayout;
    QListView *                 chooseListView;
    QVector< QStandardItem * >  chooseListItems;
    QStandardItemModel *        chooseListModel;

    // Server Overview
    QWidget *                   serverOverview;
    QGridLayout *               serverOverviewLayout;
    QLabel *                    connectionLabel;
    QListView *                 connectionListView;
    QVector< QStandardItem * >  connectionListItems;
    QStandardItemModel *        connectionListModel;


public:
    CreateCharacter(QObject *parent = 0);
    ~CreateCharacter();

    virtual bool execute();

private:
    /**
      * @brief Initialize Create Character.
      * @return True, if initialization was succsesful. Otherwise, false.
      */
    bool init();

    /**
      * @brief Delete the connection list items.
      */
    void deleteConnectionListItems();

private slots:
    /**
      * @brief Check for character being done, and triggering accept if so.
      */
    void characterDone();

    /**
      * @brief Connection has changed.
      */
    void connectionsChanged();
};

#endif // CREATE_CHARACTER_H
