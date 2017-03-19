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
#ifndef ENTITE_H
#define ENTITE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QListWidgetItem>
#include "types.h"
#include "lien.h"
#include "property.h"
#include "mainwindow.h"

//short declarations
class MainWindow;
class Property;
class Lien;
/**
 * @brief The Entite class
 * Entity is an object we have to deal with
 */
class Entite : public QGraphicsRectItem ,public QListWidgetItem
{
public:

    enum { Type = TABLE};

    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    /**
     * @brief Entite
     * @param mum
     * @param nom
     * @param x
     * @param y
     * @param parent
     * @param laScene
     * @param listeDesChamps
     * @param isAssoc
     * the constructor
     */
    Entite(MainWindow* mum, QString nom, qreal x, qreal y, QGraphicsItem* parent, QStringList listeDesChamps, bool isAssoc);
    ~Entite();
    /**
     * @brief rectTitle
     * rectangle wich contains title
     */
    QGraphicsRectItem* rectTitle;
    /**
     * @brief title
     */
    QGraphicsTextItem* title;//le titre
    /**
     * @brief nomEntite
     * name of entity
     */
    QString nomEntite;//nom de la table
    /**
     * @brief getNomEntite
     * @return
     * accessor for name
     */
    QString getNomEntite(){return nomEntite;}
    /**
     * @brief setNomEntite
     * @param nouveauNom
     * change le titre de l'entité
     */
    void setNomEntite(QString nouveauNom);
    /**
     * @brief vectLiens
     * this vector contains adresses of the links concerning entity
     */
    QVector<Lien*> vectLiens;//les liens qui la touchent.
    /**
     * @brief vecteurChamps
     * container for entity's fields
     */
    QVector<Property *> vecteurChamps;//ses champs
    /**
     * @brief contextMenuEvent
     * @param event
     * Display context Menu
     */
    void contextMenuEvent(QGraphicsSceneMouseEvent *event);//demande de menu contextuel
    /**
     * @brief maman
     * the main window
     */
    MainWindow* maman;// lien vers la maman
    /**
     * @brief polygon
     * @return rectangle wich limits entity
     */
    QPolygonF polygon(){return QPolygonF(this->boundingRect());}
    /**
     * @brief nomTableTronque
     * @return the 10 left characters + "..."
     */
    QString nomTableTronque(){return (nomEntite.length()>13)?nomEntite.left(10)+"...":nomEntite;}
    /**
     * @brief getPrimaryKey
     * @return primary key of entity as QString
     */
    QString getPrimaryKey();
    /**
     * @brief redraw
     *
     */
    void redraw();
    //assoc ou pas
    bool association;
    /**
     * @brief renvoieEntiteMeres
     * @return entities from which actual is issued
     */
    QVector<Entite*> renvoieEntiteMeres();
    /**
     * @brief isEntiteFaible
     * @return true if leak entity as hotel's room
     */
    bool isEntiteFaible();
    /**
     * @brief toSql
     * @param withoutFK
     * @return "create table ..."
     */
    QString toSql(bool withoutFK=false);
    /**
     * @brief renvoieClefsEtrangeres
     * @param constraintInsideTable if true references follow each field
     * @return foreign keys
     */
    QStringList renvoieClefsEtrangeres(bool constraintInsideTable=true);
    /**
     * @brief getPrimaryKeyAsFields
     * @return a string containing primary key
     */
    QString getPrimaryKeyAsFields();
    /**
     * @brief renvoieChampsEtrangers
     * @return all foreign fields
     */
    QStringList renvoieChampsEtrangers();
    /**
     * @brief getkeyAsForeignKey
     * @param role sometimes used to distinguish serveral links
     * @return
     */
    QString getkeyAsForeignKey(QString role);

    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    /**
     * @brief canBeWriten
     * @param vectEntitesGeneres
     * @return true if all needed entities are already created false in other case
     */
    bool canBeWriten(QVector<Entite *> vectEntitesGeneres);
    /**
     * @brief noLien
     * @param lAutre
     * @param leLien
     * @return 1 for first link  or 2 for second or 3 ...
     */
    int noLien(Entite* lAutre, Lien *leLien);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
public slots:
    /**
     * @brief nbLien
     * @param lAutre
     * @return how many links between me and the other one
     */
    int nbLien(Entite *lAutre);
};

#endif // ENTITE_H
