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
#include "customgraphicsview.h"
#include <QGraphicsItem>
#include <QMimeData>
#include <QDrag>
#include <QDebug>
#include <QTextDocument>
#include <QStandardItemModel>
#include <QDropEvent>
#include "entite.h"





void customGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug("void :customGraphicsView:dragEnterEvent(QDragEnterEvent *event)");
    if(event->source()) //source interne à l'application
    {
        if(event->source()->objectName()=="listWidgetTables")
        {
            event->accept();
        }
        else
        {

            qDebug()<<"mime"<<event->mimeData()->text();
            qDebug()<<"position"<<event->pos();
            QPointF lePointMapp=this->mapToScene(event->pos());
            QPoint  lePointMappe=lePointMapp.toPoint();
            qDebug()<<"Voici le point mappé:"<<lePointMappe;
            //jointures acceptées entre deux tables
            qDebug()<<"this.item at event->pos():"<<this->itemAt(lePointMappe)->data(32).toString();
            qDebug()<<"scene.item at event->pos():"<<this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString();

            if (this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Table")
            {
                event->accept();
                qDebug("drag accepté");
                //setCursor(QCursor(Qt::PointingHandCursor));
            }
            else
            {
                //si c'est un champ et que l'origine est une valeur de la grille des résultats alors on l'accepte
                if(this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Field")
                {
                    qDebug()<<"dragEnterEvent c'est un champ";
                    event->accept();
                    //setCursor(QCursor(Qt::PointingHandCursor));
                }
                else
                {
                    QGraphicsView::dragEnterEvent(event);
                    qDebug()<<this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString();

                }
            }
        }//fin du sinon
    }//fin du si source interne à l'applic
    else
    {
        event->ignore();
    }
}
void customGraphicsView::dragMoveEvent(QDragMoveEvent *event)
 {
    qDebug()<<"customGraphicsView::dragMoveEvent(QDragMoveEvent *event)";
    if(event->source()->objectName()=="listWidgetTables")
    {
        event->accept();
    }
    else
    {

        QPointF lePointMapp=this->mapToScene(event->pos());
        QPoint  lePointMappe=lePointMapp.toPoint();
        if (this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Table")
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            //setCursor(QCursor(Qt::PointingHandCursor));
        }
        else
        {
            if(this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Field")
            {
                qDebug()<<"c'est un champ";
                event->setDropAction(Qt::MoveAction);
                event->accept();
                //setCursor(QCursor(Qt::PointingHandCursor));
            }
            else
            {
                qDebug()<<"glourps";
                event->ignore();
            }
        }
    }
 }

void customGraphicsView::dropEvent(QDropEvent *event)
{  qDebug()<<"void customGraphicsView::dropEvent(QDropEvent *event)"<<endl;
   QPointF lePointMapp=this->mapToScene(event->pos());
   QPoint  lePointMappe=lePointMapp.toPoint();
    if(event->source()->objectName()=="listWidgetTables")
    {
        //ajout  des tables sélectionnées
        emit ilYADesTablesAAjouter(lePointMappe);
    }
    else
    {
        qDebug()<<"customGraphicsView::dropEvent(QDropEvent *event)";
        //si une table est à l'origine du dragndrop
        if(event->mimeData()->hasFormat("text/Table"))
        {
            qDebug()<<"il a le format text/Table";
            //si la destination est une table
            if (this->scene()->itemAt(lePointMappe,QTransform())->data(32).toString()=="Table")
            {
                Entite* table1=(Entite*)this->scene()->itemAt(lePointMappe,QTransform())->data(34).toLongLong();
                qDebug()<<"table1:"<<table1;
                QByteArray qba=event->mimeData()->data("text/Table");
                QString data(qba);
                QStringList typeEtNomEtAdresse=data.split(';');
                Entite * table2=(Entite*) typeEtNomEtAdresse[2].toLongLong();//recup de l'adresse de la table2
                qDebug()<<"table2:"<<table2;
                //création du lien entre les deux tables
                //trouver les deux tables:
                if(table1!=table2)
                    emit jointureRequise(table1,table2);
                else
                {
                    qDebug()<<"jointure réflexive interdite créez un alias";
                    //jointure reflexive
                    //verifier qu'il n'y a pas deja plus de 2 liens entre table1 et table1
                    if(table1->nbLien(table1)<=2)
                    emit jointureRequise(table1,table1);
                    //else avertir

                }

            }
            else
            {

                event->ignore();
            }
        }
        else //l'emmetteur du drag n'est ni une table ni une query
        {
                event->ignore();
        }
    }
}
void customGraphicsView::zoomIn()
{
    scale(1.2, 1.2);
}
void customGraphicsView::zoomOut()
{ scale(1 / 1.2, 1 / 1.2);
}
