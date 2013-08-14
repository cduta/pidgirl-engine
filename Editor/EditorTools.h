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

#ifndef EDITOR_TOOLS_H
#define EDITOR_TOOLS_H

#include <QObject>
#include <QVector>
#include <QWidget>
#include <QGridLayout>
#include <QButtonGroup>
#include <QToolButton>

#include "Command/Processor.h"
#include "Editor/Model/EditorModel.h"
#include "Editor/EditorCommon.h"

/** \addtogroup GUI
  * \{
  * \class EditorTools
  *
  * \brief The tools to be used in the editor.
  *
  * \note To add more Buttons, just add one to the Editor Model MainToolButton enum and the adding of ButtonVector.
  *       Showing a different amount of Buttons per row, you'll have to modify the MAX_TOOL_BUTTONS_IN_ROW in Common.h.
  *       Should be changed later to just all the possible objects.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class EditorTools : public QWidget
{
    Q_OBJECT

private:
    Processor *             processor;
    EditorModel *           editorModel;

    QButtonGroup            toolButtons;    ///< All the possible objects to be chosen.
    QVector<QToolButton *>  buttonVector;   ///< The list of buttons to click on to choose tools.

    // Layout
    QGridLayout *           gridLayout;     ///< Grid Layout for the buttons to choose a tool.

public:
    explicit EditorTools(Processor *processor, EditorModel *editorModel, QWidget *parent = 0);

private:
    /**
      * \brief Puts a new button in the grid layout.
      * \param buttonID Enum that represents the button used when selecting this button.
      * \param x X coordinate inside the grid layout.
      * \param y Y coordinate inside the grid layout.
      */
    void initializeToolButtons(PIDGIRL::MainToolButton buttonID, int x, int y);

    /**
      * \brief Append a new Button showing a given icon.
      * \param iconPath The path to the icon to be used as button.
      */
    void addButton(const QString &iconPath);

private slots:
    void setMainTool(int button);

};

#endif // EDITOR_TOOLS_H
