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

#ifndef OPTIONS_LAYOUT_H
#define OPTIONS_LAYOUT_H

#include <QListWidget>
#include <QStackedLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QDragMoveEvent>

/** \addtogroup Common
  * \{
  * \class List
  *
  * \brief The list for widgets with reimplemted mouse events.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class List : public QListWidget
{
public:
    List(QWidget *parent = 0)
        : QListWidget(parent)
    {}

protected:
    virtual void mousePressEvent(QMouseEvent *event)
    {
        this->QListWidget::mousePressEvent(event);
        this->mouseReleaseEvent(event);
        return;
    }

    virtual void mouseMoveEvent(QMouseEvent *event)
    {
        event->ignore();
        return;
    }
};

/** \addtogroup Common
  * \{
  * \class OptionsLayout
  *
  * \brief The layout for options to be chosen.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class OptionsLayout : public QGridLayout
{
    Q_OBJECT
signals:
    void currentIndexChangedTo(int);

private:
    List *          propertyList;
    QWidget *       stackedProperties;
    QStackedLayout *stackLayout;

    QPushButton *   okButton;
    QPushButton *   applyButton;
public:
    OptionsLayout(QWidget *parent = 0);

    void addPropertyWidget(const QString &listEntry, QWidget *widget);

public:
    // Set-Methods
    void setPropertyListWidth(int propertyListWidth);

    // Ref-Methods
    QPushButton *refOkButton();
    QPushButton *refApplyButton();

private slots:
    void showCurrentWidget();
};

#endif // OPTIONS_LAYOUT_H
