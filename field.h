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
#include "dialogrelation.h"

class Entite;
class dialogRelation;
class Property :   public QGraphicsTextItem
{
    Q_OBJECT
private:
    dialogRelation * maman;

public:
    enum { Type = FIELD};
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    //constructeur
    Property(dialogRelation* mum ,bool,QGraphicsScene* pScene,QString pName="'something'",QGraphicsItem* pParent=0);
    //destructeur
    ~Property();
    //affiche: true si le champ est à afficher
    bool affiche;
    //graphisme, visuel
    QGraphicsPixmapItem * oeil;
    QGraphicsPixmapItem * iconSort;
    QGraphicsTextItem * cond;//condition: exemple ='Dupond'
    QGraphicsLineItem * trait;//trait entre le champ et la condition
    //son nom
    QString nomInitial;
    //son alias
    QString alias;
    //en dehors des tables
    bool freeField;
    Entite * laTable;//table dans laquelle il est NULL si pas de table
    enum typeDeTri{noSort,ascSort,descSort} tri;
    //son numéro dans le tri
    int  numeroDansLeTri;
    //son numéro dans le select
    int numeroOrdreDansLeSelect;


    //quelques méthodes
    //menu contextuel
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);
    QString getNomComplet();

    QString getTri();//renvoie le numéro d'ordre dans le tri
    void dropEvent( QGraphicsSceneDragDropEvent* event);
    void dragEnterEvent( QGraphicsSceneDragDropEvent* event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void ajouteCondition(QString texteCondition);
    void modifieCondition(QString);
  signals:
          void jAiChange();
};

#endif // FIELD_H
