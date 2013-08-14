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

#include "YesNoCancelDialog.h"

#include "Common/Common.h"

YesNoCancelDialog::YesNoCancelDialog()
{
    this->yesButton = this->addButton(tr("Yes"), QMessageBox::ActionRole);
    this->noButton = this->addButton(tr("No"), QMessageBox::ActionRole);
    this->addButton(tr("Cancel"), QMessageBox::RejectRole);
}

void YesNoCancelDialog::showDialog(const QString &windowTitle, const QString &text)
{
    this->setWindowTitle(windowTitle);
    this->setText(text);

    this->setIcon(QMessageBox::Question);
    this->setDefaultButton(this->yesButton);
    this->exec();

    if(this->clickedButton() == this->yesButton)
    {
        this->buttonClicked = YesNoCancelDialog::YES_BUTTON;
    }
    else if(this->clickedButton() == this->noButton)
    {
        this->buttonClicked = YesNoCancelDialog::NO_BUTTON;
    }
    else
    {
        this->buttonClicked = YesNoCancelDialog::CANCEL_BUTTON;
    }

    return;
}

YesNoCancelDialog::ButtonClicked YesNoCancelDialog::getButtonClicked()
{
    return this->buttonClicked;
}
