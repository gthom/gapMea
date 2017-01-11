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
#ifndef PROPERTY_H
#define PROPERTY_H

#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QTextDocument>
#include "types.h"
#include "entite.h"
#include "mainwindow.h"

class Entite;
class MainWindow;
/**
 * @brief The Property class
 *property is a field it can be placed into entity or relation
 */
class Property :   public QGraphicsTextItem
{
    Q_OBJECT
private:
    MainWindow * maman;

public:
    enum { Type = FIELD};
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    //constructeur
    /**
     * @brief Property
     * @param mum
     * @param pScene
     * @param pName
     * @param pType
     * @param pRole
     * @param pTaille
     * @param pParent
     *Constructor
     */
    Property(MainWindow* mum , QString pName="'something'", QString pType="", QString pRole="", QString pTaille="", QGraphicsItem* pParent=0);
    //destructeur
    ~Property();
    //son nom
    /**
     * @brief nom
     *his name for example weight
     */
    QString nom;
    //en dehors des tables
    bool freeField;
    //table dans laquelle il est NULL si pas de table
    /**
     * @brief lEntite
     * object wich contains it
     */
    Entite * lEntite;
    //
    /**
     * @brief sonType
     * his type ex varchar(25) ou integer
     */
    QString sonType;
    //son role
    /**
     * @brief role
     *his role ex father our chief ...
     */
    QString role;
    /**
     * @brief taille
     * whenever field type need size
     */
    QString taille;
   //quelques méthodes
    //menu contextuel
    /**
     * @brief contextMenuEvent
     * @param event
     *show context menu
     */
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief getNomComplet
     * @return complete name of field
     */
    QString getNomComplet(){return nom;}

    void dropEvent( QGraphicsSceneDragDropEvent* event);
    void dragEnterEvent( QGraphicsSceneDragDropEvent* event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    /**
     * @brief toSql
     * @return ex customerName varchar(25)
     */
    QString toSql();
    /**
     * @brief emmettreSelected
     * emit signal wich is used by application when field is selected
     */
    void emmettreSelected(){emit jeSuisSelectionne(this);}
  signals:
          void jeSuisSelectionne(Property *);
};

#endif // PROPERTY_H
