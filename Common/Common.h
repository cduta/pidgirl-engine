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

#ifndef COMMON_H
#define COMMON_H

#include <QCursor>
#include <QSize>
#include <QString>
#include <QtGlobal>
#include <QTime>

#include <iostream>
#include <climits>

/**
  * \brief The PIDGIRL namespace.
  */
namespace PIDGIRL
{
    /**
      * \brief Version Number.
      */
    const QString PIDGIRL_VERSION = "0.5";

    /**
      * \brief Specifies the milliseconds until a file access should be retried. 1 sec = 1 millisecond.
      */
    const int SECONDS_UNTIL_RETRYING_FILE_ACCESS = 1;

    /**
      * \brief Specifies how many times a fileaccess should be retried until it's canceled.
      */
    const int MAX_FILE_ACCESS_RETRIES = 5;

    /**
      * \brief The minimum horizontal square count.
      */
    const int MIN_HORIZONTAL_SQUARE_COUNT = 3;

    /**
      * \brief The maximum horizontal square count.
      */
    const int MAX_HORIZONTAL_SQUARE_COUNT =30;

    /**
      * \brief The standard horizontal square count.
      */
    const int STANDARD_HORIZONTAL_SQUARE_COUNT = 10;

    /**
      * \brief The minimum vertical square count.
      */
    const int MIN_VERTICAL_SQUARE_COUNT = 3;

    /**
      * \brief The maximum vertical square count.
      */
    const int MAX_VERTICAL_SQUARE_COUNT = 20;

    /**
      * \brief The standard vertical square count.
      */
    const int STANDARD_VERTICAL_SQUARE_COUNT = 10;

    /**
      * \brief The minimum height.
      */
    const int MIN_HEIGHT = 1;

    /**
      * \brief The maximum height.
      */
    const int MAX_HEIGHT = 30;

    /**
      * \brief The standard height.
      */
    const int STANDARD_HEIGHT = 1;

    /**
      * \brief The minimum zoomfactor for the square size.
      */
    const int MIN_ZOOM_FACTOR = 1;

    /**
      * \brief The maximum zoomfactor for the square size.
      */
    const int MAX_ZOOM_FACTOR = 3;

    /**
      * \brief The standard zoomfactor for the square size.
      */
    const int STANDARD_ZOOM_FACTOR = 1;

    /**
      * \brief The minimum size of a square in SIZE x SIZE pixel.
      */
    const int MIN_SQUARE_SIZE = MIN_ZOOM_FACTOR*30;

    /**
      * \brief The maximum size of a square in SIZE x SIZE pixel.
      */
    const int MAX_SQUARE_SIZE = MAX_ZOOM_FACTOR*MIN_SQUARE_SIZE;

    /**
      * \brief The standard size of a square in SIZE x SIZE pixel.
      */
    const int STANDARD_SQUARE_SIZE = MIN_SQUARE_SIZE;

    /**
      * \brief The minimum size of a grid line.
      */
    const int MIN_GRID_LINE_SIZE = 1;

    /**
      * \brief The maximum size of a grid line.
      */
    const int MAX_GRID_LINE_SIZE = 8;

    /**
      * \brief The standard size of a grid line.
      */
    const int STANDARD_GRID_LINE_SIZE = 1;

    /**
      * \brief The minimum of characters that has to be used when naming a character.
      */
    const int MIN_PLAYER_NAME_LENGTH = 4;

    /**
      * \brief The maximum of characters that can be used when naming a character.
      */
    const int MAX_PLAYER_NAME_LENGTH = 30;

    /**
      * \brief Regular expression for names the player can enter.
      */
    const QString NAME_REG_EXP_STRING = QString("(\\s|\\w){%1,%2}").arg(PIDGIRL::MIN_PLAYER_NAME_LENGTH).arg(PIDGIRL::MAX_PLAYER_NAME_LENGTH);

    /**
      * \brief Regular experssion for IP Addresses. According to RFC952 and RFC1123.
      */
    const QString IP_ADDRESS_REG_EXP_STRING = QString("([0-9]|[a-z]|[A-Z])([0-9]|-|.|[a-z]|[A-Z])*");

    /**
      * \brief The amount of retries before canceling the sending process.
      */
    const int SEND_DATA_RETRIES = 3;

    /**
      * @brief Represents the player ID used by the server.
      */
    const unsigned int SERVER_PLAYER_ID = 0;

    /**
      * @brief The initial maximum amount of players in an E-Mail Game.
      */
    const int MAX_EMAIL_PLAYER_COUNT = 128;

    /**
      * @brief Show the usage of PIDGIRL.
      */
    inline void showUsage()
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "PIDGIRL [Options] " << std::endl;
        std::cout << "Options: " << std::endl;
        std::cout << "  -m <e-mail game>    Continue an E-Mail Game." << std::endl;
        std::cout << "  -e                  Starts the editor." << std::endl;
        std::cout << "  -l <locale>         Choose a language with giving a locale corseponding" << std::endl;
        std::cout << "                      with the PIDGIRL_XX.qm file, where XX is the locale." << std::endl;
        std::cout << "  -h, --help          Show this message." << std::endl;
        std::cout << "I.e.: 'PIDGIRL -e -l de' for the PIDGIRL editor to be translated in german.\n" << std::endl;
        return;
    }

    /**
      * \brief Write a log output in the outputbuffer, so 6 characters are left to be written.
      * \param s
      */
    inline void writeLog(const QString &s)
    {
        std::cout << s.toStdString() << "..." << std::endl;
        return;
    }

    /**
      * \brief Write a certain string.
      * \param s Is [DONE] if nothing is given.
      */
    inline void writeLogDone(const QString &s = "[DONE]")
    {
        std::cout << s.toStdString() << std::endl;
        return;
    }

    /**
      * \brief Something failed and a given error is written after [FAIL] is written.
      * \param error The error to be written out.
      */
    inline void writeLogFail(const QString &error = "")
    {
        writeLogDone("[FAIL]");
        if(!error.isEmpty())
        {
            qDebug(error.toStdString().c_str());
        }
        return;
    }

    /**
      * \brief Create a new seed for random numbers.
      */
    inline void newSeed()
    {
        QTime time = QTime::currentTime();
        QPoint pos = QCursor::pos();
        qsrand((time.msec() * time.second() * time.minute() * time.hour()) - (pos.x() * pos.y()));
        return;
    }

    /**
      * \brief Get the next higher possible ID.
      */
    inline unsigned int nextID(unsigned int id, const unsigned int lowestID = 0)
    {
        if(id < UINT_MAX)
        {
            id++;
        }
        else
        {
            id = lowestID;
        }

        return id;
    }
}

#endif // COMMON_H
