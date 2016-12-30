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
#ifndef XMEAWRITER_H
#define XMEAWRITER_H

#include <QXmlStreamWriter>
#include "lien.h"
#include "entite.h"
#include "mainwindow.h"

/**
 * @brief The XMeaWriter class
 * this class is used to write xml mea file
 */
class XMeaWriter : public QXmlStreamWriter
{
private:
    MainWindow * mum;
public:
    /**
     * @brief XMeaWriter
     * @param maman
     * Constructor
     */
    XMeaWriter(MainWindow* maman);
    ///destructor
    ~XMeaWriter();
    /**
     * @brief writeEntites
     * Write all entities
     */
    void writeEntites();
    /**
     * @brief writeEntite
     *Write one entity
     */
    void writeEntite(Entite*);
    /**
     * @brief writeLiens
     * Write all links
     */
    void writeLiens();
    /**
     * @brief writeLien
     *Write One link
     */
    void writeLien(Lien*);
    /**
     * @brief writeMea
     * Write Mea section( main container)
     */
    void writeMea();
    /**
     * @brief writeFile
     * @param device
     * @return generally true false if filesystem connot be written
     * write the xml .mea file
     */
    bool writeFile(QIODevice *device);
};
#endif // XMEAWRITER_H
