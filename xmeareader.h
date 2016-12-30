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
#ifndef XMEAREADER_H
#define XMEAREADER_H

#include <QXmlStreamReader>
#include "lien.h"
#include "entite.h"
#include "association.h"
#include "mainwindow.h"

/**
 * @brief The XMeaReader class
 * this is to read an xml  .mea file
 */
class XMeaReader : public QXmlStreamReader
{
private:
    MainWindow * mum;
public:
    /**
     * @brief XMeaReader
     * Constructor
     */
    XMeaReader(MainWindow *);
    /**
     * @brief readFile
     * @param device
     * @return true if file is ok
     */
    bool readFile(QIODevice* device);
    /**
     * @brief readMea
     * read MEA main content
     */
    void readMea();
    /**
     * @brief readEntites
     *read Entites Section
     */
    void readEntites();
    /**
     * @brief readEntite
     *read one Entity
     */
    void readEntite();
    /**
     * @brief readLiens
     *read Links Section
     */
    void readLiens();
    /**
     * @brief readLien
     *read one link
     */
    void readLien();  
    ///destructor
    ~XMeaReader();
    /**
     * @brief readFields
     * @param lEntite
     * read fields section of an entity
     */
    void readFields(Entite *lEntite);
    /**
     * @brief readField
     * @param lEntite
     *Read one field
     */
    void readField(Entite *lEntite);
};
#endif // XMEAREADER_H
