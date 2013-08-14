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

#include "Editor/EditorTools.h"
#include "Editor/EditorCommon.h"
#include "Command/Backend/Editor/Tools/ChooseMainTool.h"

#include <QPoint>

EditorTools::EditorTools(Processor *processor, EditorModel *editorModel, QWidget *parent)
    : QWidget(parent)
{
    this->processor = processor;
    this->editorModel = editorModel;

    // Set Tooldialog settings.
    this->setWindowFlags(Qt::Tool);
    this->setMinimumWidth(100);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Initialize button vector.
    this->addButton(":/objects/characters/hero");
    this->addButton(":/objects/walls/brick_wall");

    // Set up the grid layout
    this->gridLayout = new QGridLayout(this);
    this->gridLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);

    int i = 0;
    for(int y = 0; i < this->buttonVector.size(); ++y)
    {
        for(int x = 0; x < PIDGIRL::TOOL_BUTTON_COUNT_IN_ROW && i < this->buttonVector.size(); ++x)
        {
            this->initializeToolButtons(PIDGIRL::MainToolButton(i), x, y);
            i++;
        }
    }

    connect(&this->toolButtons, SIGNAL(buttonClicked(int)), this, SLOT(setMainTool(int)));

    this->setMainTool(PIDGIRL::START_POSITION);
    this->buttonVector[PIDGIRL::START_POSITION]->setChecked(true);

    // Finish it up, by making the tools usable.
    this->setEnabled(true);
    this->setVisible(true);
}

void EditorTools::initializeToolButtons(PIDGIRL::MainToolButton buttonID, int x, int y)
{
    QAbstractButton *button = this->buttonVector[buttonID];
    button->setParent(this);
    this->toolButtons.addButton(button, buttonID);
    this->gridLayout->addWidget(button,y,x);
    return;
}

void EditorTools::addButton(const QString &iconPath)
{
    QToolButton *button = new QToolButton(this);
    button->setIcon(QIcon(QPixmap(iconPath)));
    button->setCheckable(true);
    this->buttonVector.append(button);
    return;
}

void EditorTools::setMainTool(int button)
{
    this->processor->execute(new ChooseMainTool(PIDGIRL::MainToolButton(button)));
    return;
}
