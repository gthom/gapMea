#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T08:41:30
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = bin/
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lien.cpp \
    qcustomgraphicsscene.cpp \
    customgraphicsview.cpp \
    dialogtypejointure.cpp \
    entite.cpp \
    property.cpp \
    association.cpp \
    xmeawriter.cpp \
    xmeareader.cpp \
    dialogaboutme.cpp \
    lienreflexif.cpp

HEADERS  += mainwindow.h \
    lien.h \
    customgraphicsview.h \
    qcustomgraphicsscene.h \
    dialogtypejointure.h \
    entite.h \
    property.h \
    association.h \
    xmeawriter.h \
    xmeareader.h \
    dialogaboutme.h \
    lienreflexif.h

FORMS    += mainwindow.ui \
    dialogtypejointure.ui \
    dialogaboutme.ui

RESOURCES += \
    mesressources.qrc
TRANSLATIONS += gapMea_fr_FR.ts\
            gapMea_es.ts

INSTALLS += target
