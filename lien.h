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
#ifndef LIEN_H
#define LIEN_H

#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "entite.h"
#include <QColor>
#include "types.h"

/*Mes constantes*/
#define LEAKRELATION "LeakRelation"
#define ENTITY "Entity"
#define CIF "Cif"
#define RELATION "Relation"
#define DF "Df"
#define LEG "Leg"
//brief declarations
class Entite;
/**
 * @brief The Lien class
 * a link is betwwen to objects
 * it contains a line a role text cardinality ...
 */
class Lien : public QGraphicsItemGroup
{
public:
    enum { Type = LIEN};
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    /**
     * @brief line
     * the line
     */
    QGraphicsLineItem * line;
    /**
     * @brief lignePointillee
     * nécessaire en cas de pseudo-entité (association prise comme entité)
     */
    QGraphicsLineItem * lignePointillee;
    /**
     * @brief t1
     *first linked object table1
     */
    Entite* t1;
    /**
     * @brief t2
     *second linked object table2
     */
    Entite* t2;
    /**
     * @brief cardinalite1
     * example:0,1 or 1,1 or 0,n
     */
    QGraphicsSimpleTextItem * cardinalite1;
    /**
     * @brief cardinalite2
     * example:0,1 or 1,1 or 0,n
     */
    QGraphicsSimpleTextItem * cardinalite2;
    //a utiliser quand il y a plusieurs liens entre deux même objets
    /**
     * @brief role
     * if there are several links between two same objects
     */
    QGraphicsSimpleTextItem* role;
    /**
     * @brief texteDuRole
     *  example: chief
     *   necessary when there are several links between two objects
     */
    QString texteDuRole;//idem ci-dessus
    ~Lien();
    /**
     * @brief Lien
     * @param qg1
     * @param qg2
     * @param parent
     * @param typ
     * @param relationName nom de l'association
     * @param pRole
     *this is constructor
     */
    Lien(Entite* qg1,Entite* qg2,QGraphicsItem* parent, QString typ="Natural",QString relationName="",QString pRole="");//constructeur
    //Cif,patte,...
    /**
     * @brief typeDeJointure
     * cif --1,1--CIF--0,n--> df --0,1--DF--0,n-->or leg -----------
     */
    QString typeDeJointure;
    //pour les cifs et dfs et entités faibles le rond central
    /**
     * @brief leRond
     *Pour les cifs et dfs et entités faibles le rond central
     */
    QGraphicsEllipseItem* leRond;
    /**
     * @brief leTexteDuRond
     * text writen into central disk
     */
    QGraphicsTextItem* leTexteDuRond;
    /**
     * @brief laFleche
     * pour les cifs et df la flêche
     */
    QGraphicsPolygonItem* laFleche;
    //menu contextuel du lien
    /**
     * @brief contextMenuEvent
     * @param event
     * show link context Menu
     */
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);//menu contextuel du lien
    /**
     * @brief estRelieA
     * @param autreLien
     * @return true if there is another link with same source or same destination
     */
    bool estRelieA(Lien* autreLien);
    /**
     * @brief calculeCoordonnes
     * calcule les coordonnées et les met à jour
     */
    void calculeCoordonnees();
    /**
     * @brief ajouteElementsAuGroupe
     * this procedure add different items to the link
     * line, laFleche, leRond etc...
     */
    void ajouteElementsAuGroupe();
    bool reflexif;
    /**
     * @brief shape
     * used for selection and for itemAt
     * @return the smallest polygon wich contains the link
     */
    QPainterPath shape() const;
    /**
     * @brief refreshColors
     * permits to refresh colors
     */
    virtual void refreshColors();
};
#endif // LIEN_H
