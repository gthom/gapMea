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
        myappTranslator.load("/usr/share/applications/gapmea/translations/gapMea_" + QLocale::system().name()+".qm");
        a.installTranslator(&myappTranslator);
        qDebug()<<QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    MainWindow w;
    w.show();

    return a.exec();
}
