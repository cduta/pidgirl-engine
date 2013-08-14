#include "SaveGameFile.h"

#include <QDataStream>

#include "Command/Backend/Common/Quit.h"
#include "Game/Model/ServerGameModel.h"
#include "Game/Model/HotseatGameModel.h"

SaveGameFile::SaveGameFile(Processor *processor, WorldModel *worldModel, GameModel *gameModel, QObject *parent)
    : QObject(parent)
{
    this->processor = processor;
    this->worldModel = worldModel;
    this->gameModel = gameModel;
}

void SaveGameFile::serialize(QIODevice *device) const
{
    QDataStream stream(device);

    worldModel->serialize(stream);

    stream << gameModel->getGameType();

    gameModel->serialize(stream);

    return;
}

void SaveGameFile::deserialize(QIODevice *device)
{
    QDataStream stream(device);

    worldModel->deserialize(stream);

    int gameTypeInteger;
    PIDGIRL::GameType gameType;
    stream >> gameTypeInteger;
    gameType = PIDGIRL::GameType(gameTypeInteger);

    if(gameType == gameModel->getGameType())
    {
        gameModel->deserialize(stream);
    }
    else
    {
        GameModel *differentGameModel = this->fromGameType(gameType);

        if(!differentGameModel)
        {
            qDebug() << "Could not convert the given game type to the actual game type.\nGiven Type:"
                     << gameType
                     << " Actual Type:"
                     << gameModel->getGameType();
            return;
        }

        differentGameModel->deserialize(stream);

        qDebug() << "Converting Game Model...";
        this->gameModel->convertFromDifferentGameModel(differentGameModel);
    }

    return;
}

GameModel *SaveGameFile::fromGameType(PIDGIRL::GameType type)
{
    GameModel *gameModel = 0;

    switch(type)
    {
    case PIDGIRL::HOTSEAT:
    {
        gameModel = new HotseatGameModel(0,this);
        break;
    }
    case PIDGIRL::NETWORK:
    {
        gameModel = new ServerGameModel(0,this);
        break;
    }
    default: qDebug() << "The given game type is not supported to be created. Type was" << type; break;
    }

    return gameModel;
}
