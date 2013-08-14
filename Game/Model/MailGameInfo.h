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

#ifndef MAIL_GAME_INFO_H
#define MAIL_GAME_INFO_H

#include <QObject>
#include <QDir>
#include <QDataStream>

#include <string>

#include "Common/Serialize.h"

/** \addtogroup Game
  * \{
  * \class MailGameInfo
  *
  * \brief Holds all the informations about your E-Mail Game.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class MailGameInfo : public QObject, public Serialize
{
    Q_OBJECT
    bool        emailGameDirSet;
    QDir        emailGameDir;
    std::string cipherText;
    bool        saveDirSet;
    QDir        saveDir;

public:
    MailGameInfo(QObject *parent = 0);

    bool initializeMailGameInfo();

    /**
      * @brief Check if the player requesting the authentication decrypts the cipherText correctly.
      * @return True, if you are the player authenticating. Otherwise, false.
      */
    bool authenticatePlayer();

public:
    // Get-Methods
    bool hasEMailGameDirSet() const;
    QDir getEMailGameDir() const;
    QString getLocalEMailGamePath() const;
    std::string getEnctyptedText() const;
    bool hasSaveDirSet() const;
    QDir getSaveDir() const;
    QString getSaveDirAbsolutePath() const;

    // Set-Methods
    void setLocalEMailGamePath(const QString &localEMailGamePath);
public slots:
    void setSaveDir(const QString &saveDirAbsolutePath);

public:
    // Serialize
    virtual void serialize(QIODevice *device) const;
    void serialize(QDataStream &stream) const;
    virtual void deserialize(QIODevice *device);
    void deserialize(QDataStream &stream);
};

#endif // MAIL_GAME_INFO_H
