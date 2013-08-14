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

#include "WorldPropertiesDialog.h"

#include <QLabel>
#include <QHeaderView>

#include "Common/FileNameConventions.h"
#include "Command/Backend/Editor/World/AddToChosenList.h"
#include "Command/Backend/Editor/World/RemoveFromChosenList.h"
#include "Command/Backend/Editor/World/ApplyWorldPropertiesChanges.h"

WorldPropertiesDialog::WorldPropertiesDialog(Processor *processor, WorldModel *worldModel, QWidget* parent)
    : QDialog(parent)
{
    this->processor = processor;
    this->worldModel = worldModel;
    this->optionsLayout = new OptionsLayout(this);

    this->manageStartingMaps = new QWidget(this);
    this->manageStartingMapsLayout = new QGridLayout(this->manageStartingMaps);

    this->availableTreeView = new QTreeView(this->manageStartingMaps);
    this->availableFileSystemModel = new QFileSystemModel(this->availableTreeView);
    this->availableTreeView->setModel(this->availableFileSystemModel);

    for(int i = 1; i < this->availableFileSystemModel->columnCount(); ++i)
    {
        this->availableTreeView->hideColumn(i);
    }
    this->availableTreeView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->availableTreeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->availableTreeView->header()->hide();
    this->availableTreeView->setAutoScrollMargin(16);
    this->availableFileSystemModel->setNameFilterDisables(false);
    this->availableFileSystemModel->setNameFilters(QStringList(QString("*").append(PIDGIRL::MAP_SUFFIX)));
    connect(this->availableFileSystemModel, SIGNAL(directoryLoaded(QString)), this, SLOT(availableTreeUpdateColumnWidth()));
    connect(this->availableTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addPathToChosen()));

    this->chosenListView = new QListView(this->manageStartingMaps);
    this->chosenListModel = new QStandardItemModel(this->chosenListView);
    this->chosenListView->setModel(this->chosenListModel);
    connect(this->chosenListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(removePathFromChosen()));

    this->addButton = new QPushButton(tr("Add >>"), this->manageStartingMaps);
    connect(this->addButton,SIGNAL(clicked()), this, SLOT(addPathToChosen()));
    this->removeButton = new QPushButton(tr("<< Remove"), this->manageStartingMaps);
    connect(this->removeButton, SIGNAL(clicked()), this, SLOT(removePathFromChosen()));

    this->manageStartingMapsLayout->addWidget(new QLabel(tr("Available Maps:"), this->manageStartingMaps),0,0);
    this->manageStartingMapsLayout->addWidget(new QLabel(tr("Starting Maps:"), this->manageStartingMaps),0,2);
    this->manageStartingMapsLayout->addWidget(this->availableTreeView, 1,0,4,1);
    this->manageStartingMapsLayout->addWidget(this->chosenListView, 1,2,4,1);
    this->manageStartingMapsLayout->addWidget(this->addButton, 1,1);
    this->manageStartingMapsLayout->addWidget(this->removeButton, 2,1);
    this->manageStartingMapsLayout->addWidget(this->optionsLayout->refOkButton(), this->manageStartingMapsLayout->rowCount(), 0);
    this->manageStartingMapsLayout->addWidget(this->optionsLayout->refApplyButton(), this->manageStartingMapsLayout->rowCount()-1, 2);

    connect(this->optionsLayout->refOkButton(), SIGNAL(clicked()), this, SLOT(applyChanges()));
    connect(this->optionsLayout->refOkButton(), SIGNAL(clicked()), this, SLOT(close()));
    connect(this->optionsLayout->refApplyButton(), SIGNAL(clicked()), this, SLOT(applyChanges()));
    connect(this->worldModel, SIGNAL(fileChanged()), this, SLOT(updateAvailableFileSystemModel()));

    this->updateAvailableFileSystemModel();
    this->optionsLayout->addPropertyWidget(tr("Starting Maps"), this->manageStartingMaps);
    this->setLayout(this->optionsLayout);
}

void WorldPropertiesDialog::updateChosenMaps()
{
    QVector<QString> mapPaths = this->worldModel->getStartMapWorldPaths();

    this->chosenListModel->clear();

    for(int i = 0; i < mapPaths.size(); ++i)
    {
        this->chosenListModel->appendRow(new QStandardItem(mapPaths[i]));
    }

    this->update();
    return;
}

int WorldPropertiesDialog::exec()
{
    this->availableFileSystemModel->setRootPath(this->worldModel->refWorldFileInfo()->absoluteFilePath());
    this->availableTreeView->setRootIndex(this->availableFileSystemModel->index(this->availableFileSystemModel->rootPath()));
    this->updateChosenMaps();

    return QDialog::exec();
}

void WorldPropertiesDialog::addPathToChosen()
{
    this->processor->execute(new AddToChosenList(this->availableFileSystemModel, this->chosenListModel, this->availableTreeView->currentIndex()));
    return;
}

void WorldPropertiesDialog::removePathFromChosen()
{
    this->processor->execute(new RemoveFromChosenList(this->chosenListModel, this->chosenListView->currentIndex()));
    return;
}

void WorldPropertiesDialog::applyChanges()
{
    this->processor->execute(new ApplyWorldPropertiesChanges(this->chosenListModel));
    return;
}

void WorldPropertiesDialog::updateAvailableFileSystemModel()
{
    this->availableFileSystemModel->setRootPath(this->worldModel->refWorldFileInfo()->absolutePath());
    return;
}

void WorldPropertiesDialog::availableTreeUpdateColumnWidth()
{
    this->availableTreeView->resizeColumnToContents(0);
    return;
}


