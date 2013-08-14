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

#include "FileManager.h"

#include <QDir>
#include <QByteArray>
#include <QBuffer>

#include "Common/Common.h"

#ifdef Q_OS_UNIX
    #include <unistd.h>
#endif

FileManager::FileManager(QObject *parent)
    : QObject(parent)
{}

bool FileManager::fileExists()
{
    return this->file.exists();
}

bool FileManager::fileRemove()
{
    if(this->fileExists())
    {
        int retry = 0;

        while(!this->file.remove())
        {
            if(retry >= PIDGIRL::MAX_FILE_ACCESS_RETRIES)
            {
                PIDGIRL::writeLogFail(QString("Trying to remove a given file failed too often. MAX_FILE_ACCESS_RETRIES: ").append(QString::number(PIDGIRL::MAX_FILE_ACCESS_RETRIES)).append("\nReason: ").append(this->file.errorString()));
                return false;
            }

            retry++;
#ifdef Q_OS_UNIX
            std::cout << "\nError: Old existing file couldn't be removed. Trying again in " << PIDGIRL::SECONDS_UNTIL_RETRYING_FILE_ACCESS << " seconds.\nNumber of retries: " << retry << " / " << PIDGIRL::MAX_FILE_ACCESS_RETRIES << std::endl;
            sleep(PIDGIRL::SECONDS_UNTIL_RETRYING_FILE_ACCESS);
#endif
        }
    }

    return true;
}

bool FileManager::fileOpen(QIODevice::OpenModeFlag openFlag)
{
    int retry = 0;

    while(!this->file.open(openFlag))
    {
        if(retry >= PIDGIRL::MAX_FILE_ACCESS_RETRIES)
        {
            PIDGIRL::writeLogFail(QString("Trying to access the given file failed too often. MAX_FILE_ACCESS_RETRIES: ").append(QString::number(PIDGIRL::MAX_FILE_ACCESS_RETRIES)).append("\nReason: ").append(this->file.errorString()));
            return false;
        }

        retry++;
#ifdef Q_OS_UNIX
        std::cout << "\nError: File Handle couldn't be created. Trying again in " << PIDGIRL::SECONDS_UNTIL_RETRYING_FILE_ACCESS << " seconds." << std::endl;
        sleep(PIDGIRL::SECONDS_UNTIL_RETRYING_FILE_ACCESS);
#endif
    }

    return true;
}

bool FileManager::fileClose()
{
    this->file.close();
    return true;
}

void FileManager::setFilePath(const QString &path)
{
    this->file.setFileName(path);
    return;
}

bool FileManager::serialize(Serialize *serializable, const QString &path)
{
    this->setFilePath(path);

    if(!this->fileRemove())
    {
        qDebug("Could not remove the old found file");
        return false;
    }

    this->setFilePath(path);

    if(!this->fileOpen(QIODevice::WriteOnly))
    {
        qDebug("File could not be opened in write only mode.");
        return false;
    }

    QDataStream stream(this->refFile());

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QBuffer::ReadWrite);
    serializable->serialize(&buffer);

    stream << qCompress(bytes,7);
    serializable->setFileInfo(path);

    return this->fileClose();
}

bool FileManager::deserialize(Serialize *serializable, const QString &path)
{
    this->setFilePath(path);

    if(!this->fileExists())
    {
        qDebug("File did not exist.");
        return false;
    }

    if(!this->fileOpen(QIODevice::ReadOnly))
    {
        qDebug("File could not be opened in read only mode.");
        return false;
    }

    QDataStream stream(this->refFile());

    QByteArray byteData;
    stream >> byteData;
    byteData = qUncompress(byteData);

    QBuffer buffer(&byteData);
    buffer.open(QBuffer::ReadWrite);

    serializable->deserialize(&buffer);
    serializable->setFileInfo(path);

    buffer.close();

    return this->fileClose();
}

QFile *FileManager::refFile()
{
    return &this->file;
}
