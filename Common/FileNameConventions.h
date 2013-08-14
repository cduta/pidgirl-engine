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

#ifndef FILE_NAME_CONVENTIONS_H
#define FILE_NAME_CONVENTIONS_H

#include <QString>

namespace PIDGIRL
{
    /**
      * \brief The map suffix.
      */
    const QString MAP_SUFFIX = ".tmap";

    /**
      * @brief The World Folder Name.
      **/
    const QString WORLD_FOLDER_NAME = "worlds";

    /**
      * \brief The world suffix.
      */
    const QString WORLD_SUFFIX = ".tworld";

    /**
      * \brief The game information suffix.
      */
    const QString GAME_INFO_SUFFIX = ".tgameinfo";

    /**
      * \brief The save suffix.
      */
    const QString SAVE_SUFFIX = ".tsave";

    /**
      * @brief The Save Folder Name.
      */
    const QString SAVE_FOLDER_NAME = "saves";

    /**
      * \brief The email file suffix.
      */
    const QString EMAIL_SUFFIX = ".tmail";

    /**
      * @brief The EMail Folder Name.
      */
    const QString EMAIL_FOLDER_NAME = "email";

    /**
      * @brief The RSA Folder Name.
      */
    const QString RSA_FOLDER_NAME = "RSA-Encryption";

    /**
      * @brief The RSA Private Key File Name.
      */
    const QString RSA_PRIVATE_KEY_FILE_NAME = "private.key";

    /**
      * @brief The RSA Public Key File Name.
      */
    const QString RSA_PUBLIC_KEY_FILE_NAME = "public.key";

    /**
      * @brief The Plaintext File Name.
      */
    const QString RSA_PLAINTEXT_FILE_NAME = "plain.text";
}

#endif // FILE_NAME_CONVENTIONS_H
