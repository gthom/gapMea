/*
« Copyright 2016 Gilles Thomassin <gthomassingap@gmail.com> »

 This file is part of GapMea.

    GapMea is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3.

    GapMea is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GapMea.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>
/**
 * @brief main
 * @param argc
 * @param argv
 * @return application result
 * create instance of MainWindow
 * open translations files gapMea_??.qm
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
        qtTranslator.load("qt_" + QLocale::system().name(),
                QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        a.installTranslator(&qtTranslator);
        QTranslator myappTranslator;
        QString nomFichier="gapMea_" + QLocale::system().name()+".qm";
        qDebug()<<nomFichier;
        QString baseName;
//defining paths to translations
#ifdef Q_OS_LINUX
        baseName="/usr/share/applications/gapmea/translations/";
#endif
#ifdef Q_OS_MACOS
        baseName=QApplication::applicationDirPath()+QLatin1String("/../Resources/translations/"); // path defaults to app dir.
#endif
#ifdef Q_OS_DARWIN
        baseName=QApplication::applicationDirPath()+QLatin1String("/translations/"); // path defaults to app dir.
#endif
#ifdef Q_OS_WIN
        baseName=QApplication::applicationDirPath();
#endif
       myappTranslator.load(baseName+nomFichier);
        //myappTranslator.load("/usr/share/applications/gapmea/translations/gapMea_" + QLocale::system().name()+".qm");
        a.installTranslator(&myappTranslator);
        qDebug()<<QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    MainWindow w;
    w.show();
    return a.exec();
}
