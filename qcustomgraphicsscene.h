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
#ifndef QCUSTOMGRAPHICSSCENE_H
#define QCUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDragEnterEvent>
/**
 * @brief The QCustomGraphicsScene class
 * This class is designed to deal with mouse events
 */
class QCustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QCustomGraphicsScene(QWidget *);
    /**
     * @brief mousePressEvent
     * @param mouseEvent
     * some usefull code
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    //on peut lier ou déplacer outil est l'outil choisi
    /**
     * @brief outil
     * User Tool  it can be move or link
     */
    QString outil;
};

#endif // QCUSTOMGRAPHICSSCENE_H
