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

#include "EMailSetupWidget.h"

#include "Common/Common.h"

EMailSetupWidget::EMailSetupWidget(QWidget *parent) :
    QWidget(parent)
{
    this->emailWidgetLayout = new QGridLayout(this);
    this->emailWidgetLayout->setAlignment(Qt::AlignTop);
    this->setLayout(this->emailWidgetLayout);

    this->playerCountLabel = new QLabel(tr("Player Count:"),this);
    this->emailWidgetLayout->addWidget(this->playerCountLabel, 0, 0);

    this->playerCountSpinBox = new QSpinBox(this);
    this->playerCountSpinBox->setAccelerated(true);
    this->playerCountSpinBox->setMaximum(PIDGIRL::MAX_EMAIL_PLAYER_COUNT);
    this->playerCountSpinBox->setMinimum(1);
    this->playerCountSpinBox->setSingleStep(1);
    this->playerCountSpinBox->setToolTip(tr("This is only the amount of players you can start with with the maximum being %1.\nEven more players than that can be later added in-game.").arg(PIDGIRL::MAX_EMAIL_PLAYER_COUNT));
    this->emailWidgetLayout->addWidget(this->playerCountSpinBox, 0, 1);

    this->gameStartButton = new QPushButton(tr("Start Game"), this);
    this->emailWidgetLayout->addWidget(this->gameStartButton, 1, 1, Qt::AlignRight);
}
