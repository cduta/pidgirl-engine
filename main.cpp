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

#include <QApplication>
#include <QString>
#include <QTranslator>
#include <QCoreApplication>
#include <QLocale>

#include "MainWindow.h"
#include "Common/Common.h"

const QString &checkLocale(const QString& locale)
{
    if(locale != "en" && locale != "de")
    {
        PIDGIRL::showUsage();
        std::cout << "\nThe 'PIDGIRL_" << locale.toStdString() << ".qm' corresponding to the translation is missing." << std::endl;
        std::cout << "It has to be put into the same directory as this executable." << std::endl;
        exit(2);
    }

    return locale;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(true);

    if(QCoreApplication::arguments().contains("-h") ||
       QCoreApplication::arguments().contains("--help") ||
       (!(QCoreApplication::arguments().contains("-e") ||
          QCoreApplication::arguments().contains("-l") ||
          QCoreApplication::arguments().contains("-m")) &&
          QCoreApplication::arguments().size() > 1))
    {
        PIDGIRL::showUsage();
        return 1;
    }

    QTranslator translator;
    QString locale;

    if(QCoreApplication::arguments().contains("-l"))
    {
        int localeLocation = QCoreApplication::arguments().indexOf(QRegExp(QString("-l")));

        if(localeLocation + 1 < QCoreApplication::arguments().size())
        {
            locale = checkLocale(QCoreApplication::arguments().at(localeLocation + 1));
        }
        else
        {
            PIDGIRL::showUsage();
            return 1;
        }
    }
    else
    {
        locale = QLocale::system().name();
    }

    translator.load(QString("pidgirl_") + locale);

    app.installTranslator(&translator);

    PIDGIRL::writeLog("Initialize Window");

    MainWindow mainWindow;

    if(PIDGIRL::done)
    {
        return 0;
    }

    std::cout << "[STARTUP COMPLETE]" << std::endl;
    mainWindow.show();

    return app.exec();
}
