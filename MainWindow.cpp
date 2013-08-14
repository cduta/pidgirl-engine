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

#include "MainWindow.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QDockWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QString>

#include "Command/Backend/Editor/World/NewWorld.h"
#include "Command/Backend/Editor/World/LoadWorld.h"
#include "Command/Backend/Editor/World/SaveWorld.h"
#include "Command/Backend/Common/Quit.h"
#include "Command/Backend/Game/Startmenu/LoadGame.h"
#include "Command/Backend/Game/Startmenu/SetupNewGame.h"
#include "Command/Backend/Game/Startmenu/ResumeEMailGame.h"
#include "Command/Backend/Game/Startmenu/ConnectTo.h"
#include "Game/Model/ClientGameModel.h"
#include "Game/Model/EMailGameModel.h"
#include "Common/YesNoCancelDialog.h"
#include "Common/Common.h"

#include <iostream>

namespace PIDGIRL
{
    bool done = false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Initialize MainWindow.
    init();
}

void MainWindow::init()
{
    this->editorModel = new EditorModel(QCoreApplication::arguments().contains("-e"), this);
    this->setObjectName(QString::fromUtf8("mainWindow"));

    PIDGIRL::writeLogDone();

    this->processor = new Processor(this);
    this->processor->setEditorModel(this->editorModel);
    this->done = false;

    // Initialize the Editor or Game.
    // NOTE: The mapModel will be initialized in here as well as a standard map model.
    if(this->editorModel->getIsEditor())
    {
        while(!PIDGIRL::done && !this->initializeEditor())
        {
        }
    }
    else
    {
        while(!PIDGIRL::done && !this->initializeGame())
        {
        }
    }

    if(PIDGIRL::done)
    {
        return;
    }

    PIDGIRL::writeLog("Initialize MapView");

    this->mainViewMap = 0;

    PIDGIRL::writeLogDone();

    // Initialize the Editor Toolbox, if the editor flag is set.
    if(this->editorModel->getIsEditor())
    {
        PIDGIRL::writeLog("Initialize Editor");

        this->editorMenu = new EditorMenu(this->processor, this->editorModel, this->worldModel, this);
        this->setMenuBar(this->editorMenu);

        this->worldView = new WorldView(this->processor, this->worldModel, this);
        this->worldViewDock = new QDockWidget(this);
        this->worldViewDock->setWindowTitle(tr(" World Manager"));
        this->worldViewDock->setFeatures(QDockWidget::DockWidgetFloatable);
        this->worldViewDock->setAllowedAreas(Qt::LeftDockWidgetArea);
        this->worldViewDock->setWidget(this->worldView);
        this->worldViewDock->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        this->addDockWidget(Qt::LeftDockWidgetArea, this->worldViewDock);

        this->editorTools = new EditorTools(this->processor, this->editorModel, this);
        this->editorToolsDock = new QDockWidget(this);
        this->editorToolsDock->setWindowTitle(tr("Editor Tools"));
        this->editorToolsDock->setFeatures(QDockWidget::DockWidgetFloatable);
        this->editorToolsDock->setAllowedAreas(Qt::RightDockWidgetArea);
        this->editorToolsDock->setWidget(this->editorTools);
        this->addDockWidget(Qt::RightDockWidgetArea, this->editorToolsDock);

        connect(this, SIGNAL(windowSizeChanged()), this->worldView, SLOT(resizeWorldView()));
        connect(this->worldViewDock, SIGNAL(topLevelChanged(bool)), this, SLOT(updateEditorSize()));
        connect(this->editorToolsDock, SIGNAL(topLevelChanged(bool)), this, SLOT(updateEditorSize()));
        connect(this->processor, SIGNAL(commandProcessed()), this, SLOT(updateWindowTitle()));

        this->mapModel->deleteLater();
        this->setNewMap(new MapModel(this));

        PIDGIRL::writeLogDone();
    }
    else
    {
        this->editorTools = 0;
        this->editorMenu = 0;
        this->worldView = 0;

        connect(this->gameModel, SIGNAL(setNewMapSignal(MapModel *)), this, SLOT(setNewMap(MapModel*)));

        qDebug(QString("Your ID: %1").arg(QString::number(this->gameModel->getPlayerID())).toStdString().c_str());

        // Start Game
        if(!this->gameModel->firstTurn())
        {
            this->processor->execute(new Quit());
        }
    }

    this->setWindowIcon(QIcon(":/objects/characters/hero"));
    this->setFocusPolicy(Qt::WheelFocus);

    return;
}

bool MainWindow::initializeEditor()
{
    PIDGIRL::writeLog("Initialize World");

    QMessageBox initEditor;

    initEditor.setText(tr("Welcome to the PIDGIRL Editor."));
    initEditor.setInformativeText(tr("I'm sorry to interrupt you, but I need to ask you one question before we can begin.\n\nShould I create a new world or load an existing one?"));
    QPushButton *newButton = initEditor.addButton(tr("New World..."), QMessageBox::ActionRole);
    QPushButton *loadButton = initEditor.addButton(tr("Load World..."), QMessageBox::ActionRole);
    QPushButton *quitButton = initEditor.addButton(tr("Quit"), QMessageBox::RejectRole);
    initEditor.setIcon(QMessageBox::Question);
    initEditor.setDefaultButton(newButton);
    int result = initEditor.exec();

    if(initEditor.clickedButton() == newButton)
    {
        PIDGIRL::writeLogDone();

        this->worldModel = new WorldModel(this);
        this->mapModel = new MapModel(this);
        this->processor->setWorldModel(this->worldModel);

        if(!this->processor->execute(new NewWorld()))
        {
            return false;
        }
    }
    else if(initEditor.clickedButton() == loadButton)
    {
        PIDGIRL::writeLogDone();

        this->worldModel = new WorldModel(this);
        this->mapModel = new MapModel(this);
        this->processor->setWorldModel(this->worldModel);

        if(!this->processor->execute(new LoadWorld(false)))
        {
            return false;
        }
    }
    else if(initEditor.clickedButton() == quitButton || result == QMessageBox::Rejected)
    {
        PIDGIRL::writeLogDone("[EXIT]");
        this->processor->execute(new Quit());
        return true;
    }
    else
    {
        PIDGIRL::writeLogFail("None of the expected functions to initialize the editor was used. Something went wrong.");
        return false;
    }

    this->gameModel = 0;

    return true;
}


bool MainWindow::initializeGame()
{
    PIDGIRL::writeLog("Initialize Game");

    QMessageBox mainMenu;

    this->worldModel = new WorldModel(this);
    this->mapModel = new MapModel(this);
    this->processor->setWorldModel(this->worldModel);

    mainMenu.setText(tr("PIDGIRL Main Menu"));
    mainMenu.setInformativeText(tr("What do you want to do?"));
    QPushButton *newWorldButton = mainMenu.addButton(tr("Play a New World..."), QMessageBox::ActionRole);
    QPushButton *loadGameButton = mainMenu.addButton(tr("Load Game..."), QMessageBox::ActionRole);
    QPushButton *connectToButton = mainMenu.addButton(tr("Connect to..."), QMessageBox::ActionRole);
    QPushButton *resumeEMailGameButton = mainMenu.addButton(tr("Resume E-Mail Game..."), QMessageBox::ActionRole);
    QPushButton *quitButton = mainMenu.addButton(tr("Quit"), QMessageBox::RejectRole);
    mainMenu.setIcon(QMessageBox::Question);
    mainMenu.setDefaultButton(newWorldButton);

    int result = QMessageBox::Accepted;
    bool continueEMailGameFlag = QCoreApplication::arguments().contains("-m");

    if(!continueEMailGameFlag)
    {
        result = mainMenu.exec();
    }

    if(mainMenu.clickedButton() == newWorldButton)
    {
        PIDGIRL::writeLogDone();
        if(!this->processor->execute(new SetupNewGame(&this->gameModel)))
        {
            return false;
        }

        this->gameModel->setParent(this);
        return true;
    }
    else if(mainMenu.clickedButton() == loadGameButton)
    {
        if(!this->processor->execute(new LoadGame(&this->gameModel)))
        {
            return false;
        }

        this->gameModel->setParent(this);
        return true;
    }
    else if(mainMenu.clickedButton() == connectToButton)
    {
        PIDGIRL::writeLogDone();
        this->gameModel = new ClientGameModel(this->processor, this);
        this->processor->setGameModel(this->gameModel);
        return this->processor->execute(new ConnectTo());
    }
    else if(continueEMailGameFlag || mainMenu.clickedButton() == resumeEMailGameButton)
    {
        PIDGIRL::writeLogDone();
        this->gameModel = new EMailGameModel(this->processor, this);
        this->processor->setGameModel(this->gameModel);
        return this->processor->execute(new ResumeEMailGame());
    }
    else if(result == QMessageBox::Rejected || mainMenu.clickedButton() == quitButton)
    {
        PIDGIRL::writeLogDone("[EXIT]");
        this->processor->execute(new Quit());
        return true;
    }

    PIDGIRL::writeLogFail("None of the expected functions to initialize the editor was used. Something went wrong.");
    return true;
}

void MainWindow::updateSize()
{
    this->setFixedSize(this->mapModel->getMapSize());
    emit this->windowSizeChanged();
    return;
}

void MainWindow::updateEditorSize()
{
    int widthIncrement = 0;

    if(!this->worldViewDock->isFloating())
    {
        widthIncrement = widthIncrement + 218;
    }

    if(!this->editorToolsDock->isFloating())
    {
        widthIncrement = widthIncrement + this->editorToolsDock->frameSize().width() + 20;
    }

    QSize size = this->mapModel->getMapSize();

    this->setFixedSize(size + QSize(widthIncrement,this->menuWidget()->size().height()));
    this->worldViewDock->setFixedHeight(this->size().height());
    this->worldViewDock->setFixedWidth(218);
    emit this->windowSizeChanged();
    return;
}

void MainWindow::updateWindowTitle()
{
    QString windowTitle;
    QString path = this->mapModel->getFileInfo().absoluteFilePath();

    if(path == "")
    {
        windowTitle = tr("New Map");
    }
    else
    {
        windowTitle = QFileInfo(path).fileName();
    }

    if(!this->processor->refUndoRedo()->hasOnlySavedMapChanges() || !this->processor->refUndoRedo()->hasOnlySavedWorldChanges())
    {
        windowTitle.append("*");
    }

    this->setWindowTitle(windowTitle);
    return;
}

void MainWindow::createMainViewMap()
{
    if(this->mainViewMap)
    {
        this->mainViewMap->deleteLater();
        this->mainViewMap = 0;
    }

    this->mainViewMap = new MainViewMap(this->processor, this->mapModel, this->editorModel, this->gameModel, this);
    this->setCentralWidget(this->mainViewMap);

    if(this->editorModel->getIsEditor())
    {
        //this->editorMenu->updateSize(this->mapModel->getHSquareCount(), this->mapModel->getVSquareCount(), this->mapModel->getMaxHeight());
        connect(this->mainViewMap, SIGNAL(mapSizeUpdated()) , this, SLOT(updateEditorSize()));
    }

    this->update();
}

void MainWindow::setNewMap(MapModel *mapModel)
{
    if(!mapModel)
    {
        qDebug("Map coould not be loaded because it was 0.");
        return;
    }

    this->mapModel->setParent(this);
    this->mapModel = mapModel;
    this->processor->setMapModel(mapModel);

    PIDGIRL::writeLog(QString("Load New Map: %1").arg(this->mapModel->getFileInfo().fileName()).toStdString().c_str());

    this->createMainViewMap();
    connect(this->mapModel, SIGNAL(gridChanged()), this, SLOT(createMainViewMap()));

    if(this->editorModel->getIsEditor())
    {
        this->updateEditorSize();
        connect(this->mapModel, SIGNAL(gridChanged()), this, SLOT(updateEditorSize()));
        this->updateWindowTitle();
        connect(this->mapModel, SIGNAL(mapPathChanged()), this, SLOT(updateWindowTitle()));
    }
    else
    {
        this->updateSize();
        connect(this->mapModel, SIGNAL(gridChanged()), this, SLOT(updateSize()));
    }

    PIDGIRL::writeLogDone();

    return;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->processor->execute(new Quit(true));
    event->ignore();
    return;
}
