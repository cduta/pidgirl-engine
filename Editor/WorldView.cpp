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

#include "WorldView.h"

#include <QStringList>
#include <QMouseEvent>
#include <QBoxLayout>

#include "Editor/EditorCommon.h"
#include "Common/FileNameConventions.h"

WorldView::WorldView(Processor *processor, WorldModel *worldModel, QWidget *parent) :
    QWidget(parent)
{
    this->processor = processor;
    this->worldModel = worldModel;
    this->worldModel->setRootPath(this->worldModel->refWorldFileInfo()->absolutePath());
    this->worldModel->setNameFilters(QStringList(QString("*").append(PIDGIRL::MAP_SUFFIX)));
    this->worldModel->setNameFilterDisables(false);

    this->fileTree = new WorldFileTree(this->processor, this->worldModel, this);

    this->setLayout(new QBoxLayout(QBoxLayout::TopToBottom, this));
    this->layout()->setAlignment(Qt::AlignTop);
    this->layout()->addWidget(this->fileTree);

    this->setEnabled(true);
    this->setVisible(true);
}

void WorldView::resizeWorldView()
{
    this->fileTree->setFixedSize(200, this->parentWidget()->size().height() - 70);
    return;
}
