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
#ifndef ASSOCIATION_H
#define ASSOCIATION_H
#include "entite.h"
/**
 * @brief The Association class
 * Association inherit Entite
 * Association is a relation between at least two entities
 */
class Association : public Entite
{
private:
    /**
     *The rounded rect corner x radius
     */
    double m_radius_x;
    /**
     *The rounded rect corner y radius
     */
    double m_radius_y;
public:
    /**
     * @brief Association
     * @param mum the mainwindow
     * @param nom name of the association it can be a verb but it's better if it's a name
     * @param x  position x of the left up corner
     * @param y  position y of the upper left  corner
     * @param parent
     * @param laScene QScene
     * @param listeChamps a list of the fields the relation contains
     * @param isAssoc true it can be an assoc or leak entity as a room for an hotel
     * This is the only constructor.
     */
    Association(MainWindow* mum, QString nom, qreal x, qreal y, QGraphicsItem* parent, QStringList listeChamps, bool isAssoc);
    /**
   * @brief paint association
   * @param painter
   * @param option
   * @param widget
   * Paints the association on the scene
   */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ///Get the rounded rect corner x radius
    double getRadiusX() const { return m_radius_x; }

    ///Get the rounded rect corner y radius
    double getRadiusY() const { return m_radius_y; }

    ///Set the rounded rect corner x radius
    void setRadiusX(const double radius_x) { m_radius_x = radius_x; }

    ///Set the rounded rect corner y radius
    void setRadiusY(const double radius_y) { m_radius_y = radius_y; }

    ///Set the rounded rect
    void setRoundedRect(const QRectF rect, const double radius_x, const double radius_y);
    /**
     * @brief vectEntitesAssociees
     * @return a vector with adresses of all linked entities
     */
    QVector <Entite*> vectEntitesAssociees();
    QVector<QPair<Entite *, QString> > vectEntitesRolesAssociees();
};
#endif // ASSOCIATION_H
