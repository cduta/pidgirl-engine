#ifndef SAVE_GAME_FILE_H
#define SAVE_GAME_FILE_H

#include <QObject>

#include "Common/Serialize.h"
#include "Command/Processor.h"
#include "Editor/Model/WorldModel.h"
#include "Game/Model/GameModel.h"

/** \addtogroup Game
  * \{
  * \class SaveGameFile
  *
  * \brief Represents everything needed to Serialize and Deserialize a complete game save file.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class SaveGameFile : public QObject, public Serialize
{
    Q_OBJECT

    Processor * processor;
    WorldModel *worldModel;
    GameModel * gameModel;

public:
    SaveGameFile(Processor *processor, WorldModel *worldModel, GameModel *gameModel, QObject *parent = 0);

    // Serialize
    virtual void serialize(QIODevice *device) const;
    virtual void deserialize(QIODevice *device);

private:
    /**
      * @brief Creates a GameModel with the correct gametype.
      * @param type The game type.
      * @return A certain game model.
      */
    GameModel *fromGameType(PIDGIRL::GameType type);
};

#endif // SAVE_GAME_FILE_H
