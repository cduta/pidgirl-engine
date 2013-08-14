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

#include "MapPropertiesDialog.h"

#include <QLabel>

#include "Common/Common.h"
#include "Command/Backend/Editor/Map/ApplyMapGeometryChanges.h"

MapPropertiesDialog::MapPropertiesDialog(Processor *processor, QWidget *parent) :
    QDialog(parent)
{
    this->processor = processor;

    this->optionsLayout = new OptionsLayout(this);

    this->geometryPropetries = new QWidget(this);
    this->geometryPropetriesLayout = new QGridLayout(this->geometryPropetries);
    this->geometryPropetriesLayout->setAlignment(Qt::AlignTop);

    this->horizontalSquareSpinBox = new QSpinBox(this->geometryPropetries);
    this->horizontalSquareSpinBox->setRange(PIDGIRL::MIN_HORIZONTAL_SQUARE_COUNT, PIDGIRL::MAX_HORIZONTAL_SQUARE_COUNT);

    this->horizontalSquareSideComboBox = new QComboBox(this->geometryPropetries);
    this->horizontalSquareSideComboBox->addItem(tr("Left"));
    this->horizontalSquareSideComboBox->addItem(tr("Right"));

    this->verticalSquareSpinBox = new QSpinBox(this->geometryPropetries);
    this->verticalSquareSpinBox->setRange(PIDGIRL::MIN_VERTICAL_SQUARE_COUNT, PIDGIRL::MAX_VERTICAL_SQUARE_COUNT);

    this->verticalSquareSideComboBox = new QComboBox(this->geometryPropetries);
    this->verticalSquareSideComboBox->addItem(tr("Up"));
    this->verticalSquareSideComboBox->addItem(tr("Down"));

    this->maxHeightSpinBox = new QSpinBox(this->geometryPropetries);
    this->maxHeightSpinBox->setRange(PIDGIRL::MIN_HEIGHT, PIDGIRL::MAX_HEIGHT);

    this->maxHeightComboBox = new QComboBox(this->geometryPropetries);
    this->maxHeightComboBox->addItem(tr("Top"));
    this->maxHeightComboBox->addItem(tr("Bottom"));

    // Buttons
    connect(this->optionsLayout->refOkButton(), SIGNAL(clicked()), this, SLOT(applyChanges()));
    connect(this->optionsLayout->refOkButton(),SIGNAL(clicked()), this, SLOT(close()));
    connect(this->optionsLayout->refApplyButton(), SIGNAL(clicked()), this, SLOT(applyChanges()));

    // Properties
    this->geometryPropetries->setLayout(this->geometryPropetriesLayout);
    this->geometryPropetriesLayout->addWidget(new QLabel(tr("Horizontal Square Count: ")), 0,0);
    this->geometryPropetriesLayout->addWidget(this->horizontalSquareSpinBox, 0, 1);
    this->geometryPropetriesLayout->addWidget(this->horizontalSquareSideComboBox, 0, 2);
    this->geometryPropetriesLayout->addWidget(new QLabel(tr("Vertical Square Count: ")), 1,0);
    this->geometryPropetriesLayout->addWidget(this->verticalSquareSpinBox, 1, 1);
    this->geometryPropetriesLayout->addWidget(this->verticalSquareSideComboBox, 1, 2);
    this->geometryPropetriesLayout->addWidget(new QLabel(tr("Max Height: ")), 2,0);
    this->geometryPropetriesLayout->addWidget(this->maxHeightSpinBox, 2, 1);
    this->geometryPropetriesLayout->addWidget(this->maxHeightComboBox, 2, 2);
    this->geometryPropetriesLayout->addWidget(this->optionsLayout->refOkButton(), this->geometryPropetriesLayout->rowCount(), 1);
    this->geometryPropetriesLayout->addWidget(this->optionsLayout->refApplyButton(), this->geometryPropetriesLayout->rowCount()-1, 2);

    this->optionsLayout->addPropertyWidget(tr("Geometry"), this->geometryPropetries);

    // Finish
    this->setLayout(this->optionsLayout);
}

void MapPropertiesDialog::updateHorizontal(int horizontalSize)
{
    this->horizontalSquareSpinBox->setValue(horizontalSize);
    return;
}

void MapPropertiesDialog::updateVertical(int verticalSize)
{
    this->verticalSquareSpinBox->setValue(verticalSize);
    return;
}

void MapPropertiesDialog::updateMaxHeight(int maxHeight)
{
    this->maxHeightSpinBox->setValue(maxHeight);
    return;
}

void MapPropertiesDialog::applyChanges()
{
    this->processor->execute(new ApplyMapGeometryChanges(this->horizontalSquareSpinBox->value(), this->horizontalSquareSideComboBox->currentIndex(),
                                                         this->verticalSquareSpinBox->value(), this->verticalSquareSideComboBox->currentIndex(),
                                                         this->maxHeightSpinBox->value(), this->maxHeightComboBox->currentIndex()));
}
