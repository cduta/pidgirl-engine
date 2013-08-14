#---------------------------------------------------------------------------
# A flexible rogue-like engine with easy-to-use mouse interface, editor,
# solo, hotseat, network multiplayer and E-Mail game functionality in mind.
# Copyright (C) 2013  Ryoga Unryu
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#---------------------------------------------------------------------------

QT       += core gui widgets network

TARGET = pidgirl-test
TEMPLATE = app
LIBS += -lcryptopp

SOURCES += main.cpp\
        MainWindow.cpp \
    Editor/Model/EditorModel.cpp \
    Command/Processor.cpp \
    Editor/EditorMenu.cpp \
    Editor/EditorTools.cpp \
    Object/ObjectBase.cpp \
    Object/ObjectCharacter.cpp \
    Object/ObjectItem.cpp \
    Object/ObjectImage.cpp \
    Object/ObjectTile.cpp \
    Command/UndoRedo.cpp \
    Command/Backend/BaseCommand.cpp \
    Command/Backend/Undoable.cpp \
    Command/Backend/NotUndoable.cpp \
    Command/Backend/UseUndo.cpp \
    Command/Backend/UseRedo.cpp \
    Common/FileManager.cpp \
    Common/YesNoCancelDialog.cpp \
    Command/Backend/Editor/AskForSave.cpp \
    Command/Backend/ShowAbout.cpp \
    Command/Backend/Editor/Map/RemoveAllObjects.cpp \
    Command/Backend/Editor/Map/PlaceWall.cpp \
    Command/Backend/Editor/Map/PasteObject.cpp \
    Command/Backend/Editor/Map/CutWall.cpp \
    Command/Backend/Editor/Map/CopyWall.cpp \
    Command/Backend/Editor/Map/AskForSaveMap.cpp \
    Command/Backend/Editor/Tools/ChooseMainTool.cpp \
    Command/Backend/Editor/Map/RemoveWall.cpp \
    Command/Backend/Editor/Map/ChangeZoomFactor.cpp \
    Editor/MapPropertiesDialog.cpp \
    Command/Backend/Editor/Map/ApplyMapGeometryChanges.cpp \
    Common/OptionsLayout.cpp \
    Command/Backend/Editor/Map/LoadMap.cpp \
    Command/Backend/Editor/Map/LoadMapByIndex.cpp \
    Command/Backend/Game/Startmenu/SetupNewGame.cpp \
    Command/Backend/Game/Startmenu/ResumeEMailGame.cpp \
    Command/Backend/Game/GameCommand.cpp \
    Command/Backend/Game/Startmenu/ConnectTo.cpp \
    Command/Backend/Game/Startmenu/LoadGame.cpp \
    Command/Backend/Common/Quit.cpp \
    Command/Backend/Common/CopyFolder.cpp \
    Command/Backend/Common/CommonCommand.cpp \
    Command/Backend/Common/RemoveFolder.cpp \
    Game/Model/GameModel.cpp \
    Command/Backend/Game/Ingame/EndTurn.cpp \
    Command/Backend/Game/Ingame/CreateCharacter.cpp \
    Command/Backend/Command.cpp \
    Common/Serialize.cpp \
    Command/Backend/Editor/Map/PlaceEditorObject.cpp \
    Command/Backend/Game/Map/FindPath.cpp \
    AStar/AStarMap.cpp \
    AStar/AStarMapEntry.cpp \
    Common/Common.cpp \
    Common/FileNameConventions.cpp \
    Network/NetworkModel.cpp \
    Network/ClientModel.cpp \
    Network/ServerModel.cpp \
    Network/ClientSocket.cpp \
    Command/Backend/Network/Client/ReceiveInitialPlayerInformation.cpp \
    Command/Backend/Network/NetworkCommand.cpp \
    Command/Backend/Network/Server/SendInitialPlayerInformation.cpp \
    Command/Backend/Game/Ingame/LoadStartMapFromIndex.cpp \
    Game/Model/LocalGameModel.cpp \
    Game/Model/ClientGameModel.cpp \
    Game/Model/ServerGameModel.cpp \
    Game/Model/HotseatGameModel.cpp \
    Game/Model/EMailGameModel.cpp \
    Game/Model/PlayerModel.cpp \
    Command/Backend/Game/Ingame/SpawnGameObject.cpp \
    Object/ObjectID.cpp \
    Object/Tile/BrickWall.cpp \
    Object/ObjectFromID.cpp \
    Object/ObjectSpecial.cpp \
    Object/Special/StartPosition.cpp \
    Command/Backend/Editor/Map/PlaceSpecial.cpp \
    Object/Character/Player.cpp \
    Command/Backend/Game/Ingame/PreloadAllMaps.cpp \
    Command/Backend/Game/Ingame/SpawnPlayerOnCurrentMap.cpp \
    Command/Backend/Network/Client/RequestMapFromServer.cpp \
    Network/WaitingForDataDialog.cpp \
    Command/Backend/Network/Server/ReplyToRequestForMap.cpp \
    Command/Backend/Network/Client/ReceiveMap.cpp \
    Command/Backend/Object/ObjectCommand.cpp \
    Command/Backend/Network/Server/SendToClientNextTurn.cpp \
    Command/Backend/Network/Client/ClientCommand.cpp \
    Command/Backend/Network/Server/ServerCommand.cpp \
    Command/Backend/Network/Client/SendToServerEndTurn.cpp \
    Command/Backend/Game/Ingame/FirstTurn.cpp \
    Command/Backend/Game/Ingame/NextTurn.cpp \
    Command/Backend/Game/Map/MoveCharacter.cpp \
    Command/Backend/Network/Server/ClientDisconnected.cpp \
    Command/Backend/Network/ReceiveUpdateCharacterFrom.cpp \
    Command/Backend/Network/Client/SendUpdateCharacterToServer.cpp \
    Command/Backend/Network/Server/Broadcast/BroadcastCommand.cpp \
    Command/Backend/Network/Server/Broadcast/BroadcastUpdateCharacter.cpp \
    Command/Backend/Network/Client/SendSpawnCharacterToServer.cpp \
    Command/Backend/Network/ReceiveSpawnCharacterFrom.cpp \
    Command/Backend/Network/Server/Broadcast/BroadcastSpawnCharacter.cpp \
    Command/Backend/Game/Map/ClearPath.cpp \
    Command/Backend/Object/ShowDescription.cpp \
    Editor/Model/WorldModel.cpp \
    Command/Backend/Game/Startmenu/PreloadWorld.cpp \
    Command/Backend/Editor/World/AddToChosenList.cpp \
    Command/Backend/Editor/World/ApplyWorldPropertiesChanges.cpp \
    Command/Backend/Editor/World/AskForSaveWorld.cpp \
    Command/Backend/Editor/World/DuplicateWorldEntry.cpp \
    Command/Backend/Editor/World/LoadWorld.cpp \
    Command/Backend/Editor/World/MoveFile.cpp \
    Command/Backend/Editor/World/NewFolder.cpp \
    Command/Backend/Editor/World/NewMapFile.cpp \
    Command/Backend/Editor/World/NewWorld.cpp \
    Command/Backend/Editor/World/RemoveFromChosenList.cpp \
    Command/Backend/Editor/World/RemoveWorldEntry.cpp \
    Command/Backend/Editor/World/RenameWorldEntry.cpp \
    Command/Backend/Editor/World/SaveMap.cpp \
    Command/Backend/Editor/World/SaveMapAs.cpp \
    Command/Backend/Editor/World/SaveWorld.cpp \
    Command/Backend/Editor/World/SaveWorldAs.cpp \
    Editor/WorldFileTree.cpp \
    Editor/WorldPropertiesDialog.cpp \
    Editor/WorldView.cpp \
    Editor/Model/LocalFilePaths.cpp \
    MainView/CommandAction.cpp \
    MainView/MainViewMap.cpp \
    MainView/MainViewStack.cpp \
    MainView/ObjectMenu.cpp \
    MainView/Model/MapModel.cpp \
    MainView/Model/StackModel.cpp \
    MainView/Model/MouseInput/ContextEditorMenuState.cpp \
    MainView/Model/MouseInput/ContextGameMenuState.cpp \
    MainView/Model/MouseInput/IdleEditorMouseState.cpp \
    MainView/Model/MouseInput/IdleGameMouseState.cpp \
    MainView/Model/MouseInput/MouseEditorInput.cpp \
    MainView/Model/MouseInput/MouseGameInput.cpp \
    MainView/Model/MouseInput/MouseInput.cpp \
    MainView/Model/MouseInput/MouseState.cpp \
    MainView/Model/MouseInput/PlaceObjectsState.cpp \
    MainView/Model/MouseInput/RemoveObjectsState.cpp \
    MainView/Model/MouseInput/TargetChosenState.cpp \
    MainView/Model/MouseInput/TargetConfirmedState.cpp \
    MainView/Model/MouseInput/TargetMoveState.cpp \
    Command/Backend/Network/Client/RequestPlayerModelsFromServer.cpp \
    Command/Backend/Network/Client/ReceivePlayerModels.cpp \
    Command/Backend/Network/Server/ReplyToRequestForPlayerModels.cpp \
    Command/Backend/Network/Client/RequestPlayerFromServer.cpp \
    Command/Backend/Network/Client/ReceivePlayer.cpp \
    Command/Backend/Network/Server/ReplyToRequestForPlayer.cpp \
    Command/Backend/Network/Client/ChangePlayerIDOnServer.cpp \
    Command/Backend/Network/Server/ReceiveChangePlayerID.cpp \
    Command/Backend/Game/Ingame/YourTurnInformation.cpp \
    Command/Backend/Game/Ingame/ShowGameOptions.cpp \
    Command/Backend/Game/Ingame/SaveGame.cpp \
    Game/Model/SaveGameFile.cpp \
    Game/GeneralSetupWidget.cpp \
    Game/NetworkSetupWidget.cpp \
    Game/SoloHotseatSetupWidget.cpp \
    Game/EMailSetupWidget.cpp \
    Game/Model/MailGameInfo.cpp \
    RSA/RSAMethod.cpp \
    Command/Backend/Game/Ingame/SaveEMailGame.cpp

HEADERS  += MainWindow.h \
    Editor/Model/EditorModel.h \
    Command/Processor.h \
    Editor/EditorMenu.h \
    Editor/EditorTools.h \
    Object/ObjectBase.h \
    Object/ObjectImage.h \
    Object/ObjectCharacter.h \
    Object/ObjectItem.h \
    Object/ObjectTile.h \
    Command/UndoRedo.h \
    Command/Backend/BaseCommand.h \
    Command/Backend/Undoable.h \
    Command/Backend/NotUndoable.h \
    Command/Backend/UseUndo.h \
    Command/Backend/UseRedo.h \
    Common/Common.h \
    Common/FileManager.h \
    Common/YesNoCancelDialog.h \
    Command/Backend/Editor/AskForSave.h \
    Command/Backend/ShowAbout.h \
    Common/FileNameConventions.h \
    Command/Backend/Editor/Map/RemoveAllObjects.h \
    Command/Backend/Editor/Map/PlaceWall.h \
    Command/Backend/Editor/Map/PasteObject.h \
    Command/Backend/Editor/Map/CutWall.h \
    Command/Backend/Editor/Map/CopyWall.h \
    Command/Backend/Editor/Map/AskForSaveMap.h \
    Command/Backend/Editor/Tools/ChooseMainTool.h \
    Command/Backend/Editor/Map/RemoveWall.h \
    Command/Backend/Editor/Map/ChangeZoomFactor.h \
    Editor/MapPropertiesDialog.h \
    Command/Backend/Editor/Map/ApplyMapGeometryChanges.h \
    Common/OptionsLayout.h \
    Command/Backend/Editor/Map/LoadMap.h \
    Command/Backend/Editor/Map/LoadMapByIndex.h \
    Command/Backend/Game/Startmenu/SetupNewGame.h \
    Command/Backend/Game/Startmenu/ResumeEMailGame.h \
    Command/Backend/Game/GameCommand.h \
    Command/Backend/Game/Startmenu/ConnectTo.h \
    Command/Backend/Game/Startmenu/LoadGame.h \
    Command/Backend/Common/Quit.h \
    Command/Backend/Common/CopyFolder.h \
    Command/Backend/Common/CommonCommand.h \
    Command/Backend/Common/RemoveFolder.h \
    Game/Model/GameModel.h \
    Command/Backend/Game/Ingame/EndTurn.h \
    Command/Backend/Game/Ingame/CreateCharacter.h \
    Command/Backend/Command.h \
    Common/Serialize.h \
    Command/Backend/Editor/Map/PlaceEditorObject.h \
    Command/Backend/Game/Map/FindPath.h \
    AStar/AStarMap.h \
    AStar/AStarMapEntry.h \
    Network/NetworkModel.h \
    Network/ClientModel.h \
    Network/ServerModel.h \
    Network/ClientSocket.h \
    Command/Backend/Network/Client/ReceiveInitialPlayerInformation.h \
    Command/Backend/Network/NetworkCommand.h \
    Command/Backend/Network/Server/SendInitialPlayerInformation.h \
    Command/Backend/Game/Ingame/LoadStartMapFromIndex.h \
    Game/Model/LocalGameModel.h \
    Game/Model/ClientGameModel.h \
    Game/Model/ServerGameModel.h \
    Game/Model/HotseatGameModel.h \
    Game/Model/EMailGameModel.h \
    Game/Model/PlayerModel.h \
    Command/Backend/Game/Ingame/SpawnGameObject.h \
    Object/ObjectID.h \
    Object/Tile/BrickWall.h \
    Object/ObjectFromID.h \
    Object/ObjectSpecial.h \
    Object/Special/StartPosition.h \
    Command/Backend/Editor/Map/PlaceSpecial.h \
    Object/Character/Player.h \
    Command/Backend/Game/Ingame/PreloadAllMaps.h \
    Command/Backend/Game/Ingame/SpawnPlayerOnCurrentMap.h \
    Command/Backend/Network/Client/RequestMapFromServer.h \
    Network/WaitingForDataDialog.h \
    Command/Backend/Network/Server/ReplyToRequestForMap.h \
    Command/Backend/Network/Client/ReceiveMap.h \
    Command/Backend/Object/ObjectCommand.h \
    Command/Backend/Network/Server/SendToClientNextTurn.h \
    Command/Backend/Network/Client/ClientCommand.h \
    Command/Backend/Network/Server/ServerCommand.h \
    Command/Backend/Network/Client/SendToServerEndTurn.h \
    Command/Backend/Game/Ingame/FirstTurn.h \
    Command/Backend/Game/Ingame/NextTurn.h \
    Command/Backend/Game/Map/MoveCharacter.h \
    Command/Backend/Network/Server/ClientDisconnected.h \
    Command/Backend/Network/ReceiveUpdateCharacterFrom.h \
    Command/Backend/Network/Client/SendUpdateCharacterToServer.h \
    Command/Backend/Network/Server/Broadcast/BroadcastCommand.h \
    Command/Backend/Network/Server/Broadcast/BroadcastUpdateCharacter.h \
    Command/Backend/Network/Client/SendSpawnCharacterToServer.h \
    Command/Backend/Network/ReceiveSpawnCharacterFrom.h \
    Command/Backend/Network/Server/Broadcast/BroadcastSpawnCharacter.h \
    Editor/EditorCommon.h \
    Command/Backend/Game/Map/ClearPath.h \
    Command/Backend/Object/ShowDescription.h \
    Editor/Model/WorldModel.h \
    Command/Backend/Game/Startmenu/PreloadWorld.h \
    Command/Backend/Editor/World/AddToChosenList.h \
    Command/Backend/Editor/World/ApplyWorldPropertiesChanges.h \
    Command/Backend/Editor/World/AskForSaveWorld.h \
    Command/Backend/Editor/World/DuplicateWorldEntry.h \
    Command/Backend/Editor/World/LoadWorld.h \
    Command/Backend/Editor/World/MoveFile.h \
    Command/Backend/Editor/World/NewFolder.h \
    Command/Backend/Editor/World/NewMapFile.h \
    Command/Backend/Editor/World/NewWorld.h \
    Command/Backend/Editor/World/RemoveFromChosenList.h \
    Command/Backend/Editor/World/RemoveWorldEntry.h \
    Command/Backend/Editor/World/RenameWorldEntry.h \
    Command/Backend/Editor/World/SaveMap.h \
    Command/Backend/Editor/World/SaveMapAs.h \
    Command/Backend/Editor/World/SaveWorld.h \
    Command/Backend/Editor/World/SaveWorldAs.h \
    Editor/WorldFileTree.h \
    Editor/WorldPropertiesDialog.h \
    Editor/WorldView.h \
    Editor/Model/LocalFilePaths.h \
    MainView/CommandAction.h \
    MainView/MainViewMap.h \
    MainView/MainViewStack.h \
    MainView/ObjectMenu.h \
    MainView/Model/MapModel.h \
    MainView/Model/StackModel.h \
    MainView/Model/MouseInput/ContextEditorMenuState.h \
    MainView/Model/MouseInput/ContextGameMenuState.h \
    MainView/Model/MouseInput/IdleEditorMouseState.h \
    MainView/Model/MouseInput/IdleGameMouseState.h \
    MainView/Model/MouseInput/MouseEditorInput.h \
    MainView/Model/MouseInput/MouseGameInput.h \
    MainView/Model/MouseInput/MouseInput.h \
    MainView/Model/MouseInput/MouseState.h \
    MainView/Model/MouseInput/PlaceObjectsState.h \
    MainView/Model/MouseInput/RemoveObjectsState.h \
    MainView/Model/MouseInput/TargetChosenState.h \
    MainView/Model/MouseInput/TargetConfirmedState.h \
    MainView/Model/MouseInput/TargetMoveState.h \
    Command/Backend/Network/Client/RequestPlayerModelsFromServer.h \
    Command/Backend/Network/Client/ReceivePlayerModels.h \
    Command/Backend/Network/Server/ReplyToRequestForPlayerModels.h \
    Command/Backend/Network/Client/RequestPlayerFromServer.h \
    Command/Backend/Network/Client/ReceivePlayer.h \
    Command/Backend/Network/Server/ReplyToRequestForPlayer.h \
    Command/Backend/Network/Client/ChangePlayerIDOnServer.h \
    Command/Backend/Network/Server/ReceiveChangePlayerID.h \
    Command/Backend/Game/Ingame/YourTurnInformation.h \
    Command/Backend/Game/Ingame/ShowGameOptions.h \
    Command/Backend/Game/Ingame/SaveGame.h \
    Game/Model/SaveGameFile.h \
    Game/GeneralSetupWidget.h \
    Game/NetworkSetupWidget.h \
    Game/SoloHotseatSetupWidget.h \
    Game/EMailSetupWidget.h \
    Game/Model/MailGameInfo.h \
    RSA/RSAMethod.h \
    Command/Backend/Game/Ingame/SaveEMailGame.h

RESOURCES += pidgirlRessource.qrc

TRANSLATIONS = pidgirl_de.ts

OTHER_FILES +=





























