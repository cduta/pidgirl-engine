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

#ifndef YES_NO_CANCEL_DIALOG_H
#define YES_NO_CANCEL_DIALOG_H

#include <QMessageBox>
#include <QPushButton>

/** \addtogroup Common
  * \{
  * \class YesNoCancelDialog
  *
  * \brief A wrapper to show yes no cancel dialogs more easily.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class YesNoCancelDialog : public QMessageBox
{
    Q_OBJECT
public:
    enum ButtonClicked {YES_BUTTON, NO_BUTTON, CANCEL_BUTTON};

private:
    ButtonClicked   buttonClicked; /// Represents the button that has been clicked. Standard value is CANCEL.
    QPushButton *   yesButton;
    QPushButton *   noButton;

public:
    YesNoCancelDialog();

    /**
      * \brief Shows a dialog with the given caption and text and saves the button clicked by the user.
      * \param windowTitle The caption shown.
      * \param text The text shown.
      */
    void showDialog(const QString &windowTitle, const QString &text);

    // Get-Methods
    ButtonClicked getButtonClicked();
};

#endif // YES_NO_CANCEL_DIALOG_H
