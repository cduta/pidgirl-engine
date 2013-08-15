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

#include "MailGameInfo.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "Common/FileNameConventions.h"
#include "Common/Common.h"
#include "RSA/RSAMethod.h"

MailGameInfo::MailGameInfo(QObject *parent)
    : QObject(parent)
{
    this->emailGameDirSet = false;
    this->saveDirSet = false;
}

bool MailGameInfo::initializeMailGameInfo()
{
    QDir emailDir(QDir::current());

    if(!emailDir.cd(PIDGIRL::EMAIL_FOLDER_NAME))
    {
        emailDir.mkdir(PIDGIRL::EMAIL_FOLDER_NAME);
        emailDir.cd(PIDGIRL::EMAIL_FOLDER_NAME);
    }

    QString currentEMailDir = "game";
    unsigned int gameNr = 0;

    while(emailDir.cd(QString(currentEMailDir).append(QString::number(gameNr))))
    {
        emailDir.cdUp();
        gameNr++;
    }

    currentEMailDir.append(QString::number(gameNr));

    emailDir.mkdir(currentEMailDir);
    emailDir.cd(currentEMailDir);

    if(!this->hasSaveDirSet())
    {
        this->setSaveDir(emailDir.absolutePath());
    }

    if(!this->hasEMailGameDirSet())
    {
        this->emailGameDir = emailDir;
        this->emailGameDirSet = true;
    }

    QDir RSADir(this->emailGameDir);
    RSADir.mkdir(PIDGIRL::RSA_FOLDER_NAME);
    RSADir.cd(PIDGIRL::RSA_FOLDER_NAME);

    RSAMethod rsa(1024,
                  QFileInfo(RSADir, PIDGIRL::RSA_PRIVATE_KEY_FILE_NAME).absoluteFilePath().toStdString(),
                  QFileInfo(RSADir, PIDGIRL::RSA_PUBLIC_KEY_FILE_NAME).absoluteFilePath().toStdString());

    QFile file(QFileInfo(RSADir, PIDGIRL::RSA_PLAINTEXT_FILE_NAME).absoluteFilePath());

    std::string randomText;
    PIDGIRL::newSeed();

    for(size_t i = 0; i < rsa.getMaxPlainTextLength(); ++i)
    {
        randomText.push_back((char) ((rand()%96)+32));
    }

    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    QTextStream stream(&file);
    stream << randomText.c_str();

    file.close();

    this->cipherText = rsa.encryptString(randomText);

    return true;
}

bool MailGameInfo::authenticatePlayer()
{

    QDir RSADir(this->emailGameDir);
    RSADir.cd(PIDGIRL::RSA_FOLDER_NAME);

    if(!RSADir.exists())
    {
        return false;
    }

    RSAMethod rsa(QFileInfo(RSADir, PIDGIRL::RSA_PRIVATE_KEY_FILE_NAME).absoluteFilePath().toStdString(),
                  QFileInfo(RSADir, PIDGIRL::RSA_PUBLIC_KEY_FILE_NAME).absoluteFilePath().toStdString());

    QFile file(QFileInfo(RSADir, PIDGIRL::RSA_PLAINTEXT_FILE_NAME).absoluteFilePath());

    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QTextStream stream(&file);
    QString plainText = stream.readAll();

    file.close();

    QString recoveredText = QString(rsa.decryptString(this->cipherText).c_str());

    return recoveredText.compare(plainText) == 0;
}

bool MailGameInfo::hasEMailGameDirSet() const
{
    return this->emailGameDirSet;
}

QDir MailGameInfo::getEMailGameDir() const
{
    if(this->hasEMailGameDirSet())
    {
        return this->emailGameDir;
    }
    else
    {
        return QDir::current();
    }
}

QString MailGameInfo::getLocalEMailGamePath() const
{
    return QString(this->emailGameDir.absolutePath()).remove(0, QDir::current().absolutePath().size());;
}

std::string MailGameInfo::getEnctyptedText() const
{
    return this->cipherText;
}

bool MailGameInfo::hasSaveDirSet() const
{
    return this->saveDirSet;
}

QDir MailGameInfo::getSaveDir() const
{
    return this->saveDir;
}

QString MailGameInfo::getSaveDirAbsolutePath() const
{
    if(this->hasSaveDirSet())
    {
        return this->getSaveDir().absolutePath();
    }
    else
    {
        return QString("");
    }
}

void MailGameInfo::setLocalEMailGamePath(const QString &localEMailGamePath)
{
    this->emailGameDir = QDir(QString((QDir::current().absolutePath()).append(localEMailGamePath)));
    this->emailGameDirSet = true;
    return;
}

void MailGameInfo::setSaveDir(const QString &saveDirAbsolutePath)
{
    if(saveDirAbsolutePath.isEmpty())
    {
        this->saveDir = QDir();

        if(this->hasEMailGameDirSet())
        {
            this->saveDir = this->getEMailGameDir();
        }
        else
        {
            this->saveDirSet = false;
        }
    }
    else
    {
        this->saveDir = QDir(saveDirAbsolutePath);
        this->saveDirSet = true;
    }

    return;
}

void MailGameInfo::serialize(QIODevice *device) const
{
    QDataStream stream(device);
    this->serialize(stream);
    return;
}

void MailGameInfo::serialize(QDataStream &stream) const
{
    stream << this->hasEMailGameDirSet();
    stream << this->getLocalEMailGamePath();
    stream << QByteArray(this->cipherText.c_str(), this->cipherText.size());
    stream << this->hasSaveDirSet();
    stream << this->saveDir.path();
    return;
}

void MailGameInfo::deserialize(QIODevice *device)
{
    QDataStream stream(device);
    this->deserialize(stream);
    return;
}

void MailGameInfo::deserialize(QDataStream &stream)
{
    bool emailGameDirSet;
    stream >> emailGameDirSet;
    this->emailGameDirSet = emailGameDirSet;

    QString localEMailGamePath;
    stream >> localEMailGamePath;

    // If the E-Mail Game Dir has been set before.
    if(emailGameDirSet)
    {
        this->setLocalEMailGamePath(localEMailGamePath);
    }

    QByteArray cipherBytes;
    stream >> cipherBytes;

    for(int i = 0; i < cipherBytes.size(); ++i)
    {
        this->cipherText.push_back(cipherBytes.at(i));
    }

    bool saveDirSet;
    stream >> saveDirSet;
    this->saveDirSet = saveDirSet;

    QString saveDir;
    stream >> saveDir;

    // If the Save Dir has been set before.
    if(saveDirSet)
    {
        this->setSaveDir(saveDir);
    }
    return;
}
