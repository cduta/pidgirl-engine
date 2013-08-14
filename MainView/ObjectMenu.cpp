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

#include "ObjectMenu.h"

#include <QAction>

#include "Command/Backend/BaseCommand.h"
#include "MainView/CommandAction.h"

ObjectMenu::ObjectMenu(ObjectBase *object, Processor *processor, QWidget *parent)
    : QMenu(parent)
{
    this->processor = processor;
    this->object = object->copyBase();

    this->object->setParent(this);
    this->setTitle(this->object->getObjectName());
    this->setIcon(QIcon(QPixmap::fromImage(*this->object->refImage())));

    QList<BaseCommand *> commandList = object->getCommandList().values();
    QList<QString> keys = object->getCommandList().keys();

    if(commandList.isEmpty())
    {
        QAction *action = new QAction(tr("No Interactions..."), this);
        action->setEnabled(false);
        this->addAction(action);
    }
    else
    {
        BaseCommand * command;
        CommandAction * commandAction;
        for(int i = 0; i < commandList.size(); ++i)
        {
            command = commandList[i];
            if(command && this->processor->isExecutable(command))
            {
                commandAction = new CommandAction(QIcon(command->getCommandIcon()), keys[i], this);
                connect(commandAction, SIGNAL(triggerWithName(const QString &)), this, SLOT(triggerCommandByName(const QString &)));
                this->addAction(commandAction);
                command->deleteLater();
            }
        }
    }
}

void ObjectMenu::triggerCommandByName(const QString &name)
{
    QMap<QString, BaseCommand *> commandMap = this->object->getCommandList();
    BaseCommand *command = commandMap.value(name);
    bool failed = false;

    if(!command)
    {
        qDebug(QString("Command was not found therefore %1 cannot be triggered.").arg(name).toStdString().c_str());
        failed = true;
    }

    if(command && !processor->isExecutable(command))
    {
        qDebug(QString("Command '%1' was not executable. Therefore could not be triggered.").arg(name).toStdString().c_str());
        failed = true;
    }

    if(!failed)
    {
        this->processor->execute(commandMap.take(name));
    }

    QList<BaseCommand *> commandList = commandMap.values();

    for(int i = 0; i < commandList.size(); ++i)
    {
        commandList[i]->deleteLater();
    }

    return;
}

