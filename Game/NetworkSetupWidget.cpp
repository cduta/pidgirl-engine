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

#include "NetworkSetupWidget.h"

NetworkSetupWidget::NetworkSetupWidget(QWidget *parent) :
    QWidget(parent)
{
    this->networkWidgetLayout = new QGridLayout(this);
    this->networkWidgetLayout->setAlignment(Qt::AlignTop);
    this->setLayout(this->networkWidgetLayout);

    this->portLabel = new QLabel("Port:", this);
    this->portEdit = new QLineEdit("64120", this);
    this->portValidator = new QIntValidator(1025, 65535, this->portEdit);
    this->portEdit->setValidator(this->portValidator);
    this->gameStartButton = new QPushButton(tr("Start Game"), this);

    this->networkWidgetLayout->addWidget(this->portLabel,0,0,Qt::AlignLeft);
    this->networkWidgetLayout->addWidget(this->portEdit,0,1,Qt::AlignLeft);
    this->networkWidgetLayout->addWidget(this->gameStartButton,1,1,Qt::AlignRight);
}
