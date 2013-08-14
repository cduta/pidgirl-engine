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

#include "OptionsLayout.h"

#include <iostream>

OptionsLayout::OptionsLayout(QWidget *parent)
    : QGridLayout(parent)
{
    this->propertyList = new List(this->parentWidget());
    this->propertyList->setFixedWidth(150);
    this->propertyList->setMinimumHeight(250);
    this->propertyList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->propertyList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->propertyList->setSortingEnabled(false);
    this->propertyList->setAlternatingRowColors(true);

    this->stackedProperties = new QWidget(this->parentWidget());
    this->stackedProperties->setMinimumSize(300,250);
    this->stackLayout = new QStackedLayout(this->stackedProperties);
    this->stackLayout->setAlignment(Qt::AlignLeft);
    this->stackedProperties->setLayout(this->stackLayout);

    this->addWidget(this->propertyList, 0,0);
    this->addWidget(this->stackedProperties,0,1,2,1);
    this->setAlignment(Qt::AlignCenter);

    this->okButton = new QPushButton(tr("Ok"), this->parentWidget());
    this->applyButton = new QPushButton(tr("Apply"), this->parentWidget());

    connect(this->propertyList, SIGNAL(itemSelectionChanged()), this, SLOT(showCurrentWidget()));
}

void OptionsLayout::addPropertyWidget(const QString &listEntry, QWidget *widget)
{
    if(!widget || listEntry.isEmpty())
    {
        std::cout << "Error: Adding a property widget to the OptionLayout failed." << std::endl;
        return;
    }

    this->propertyList->addItem(listEntry);
    if(this->propertyList->count() == 1)
    {
        this->propertyList->setItemSelected(this->propertyList->item(0),true);
    }

    this->stackLayout->addWidget(widget);

    return;
}

void OptionsLayout::setPropertyListWidth(int propertyListWidth)
{
    this->propertyList->setFixedWidth(propertyListWidth);
    return;
}

QPushButton *OptionsLayout::refOkButton()
{
    return this->okButton;
}

QPushButton *OptionsLayout::refApplyButton()
{
    return this->applyButton;
}

void OptionsLayout::showCurrentWidget()
{
    QModelIndex currentIndex = this->propertyList->currentIndex();
    this->stackLayout->setCurrentIndex(currentIndex.row());
    emit currentIndexChangedTo(currentIndex.row());
    return;
}


