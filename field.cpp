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
#include "field.h"
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QTextDocument>

field::field(dialogRelation* mum ,bool isFree,QGraphicsScene* pScene,QString pName,QGraphicsItem* pParent)
    :QGraphicsTextItem(pName,pParent)
{
    qDebug()<<"constructeur de field";
    maman=mum;
    nomInitial=pName;
    //affichage de l'oeil fermé: le champ n'est pas affiché
    affiche=false;
    oeil=new QGraphicsPixmapItem(QPixmap(":/mini-eye.xpm"),this);
    oeil->setPos(-20,5);
    oeil->setVisible(affiche);//false puisque non affiché
    freeField=isFree;
    //affichage du tri
    tri=noSort;//pas de tri sur le champ
    iconSort=new QGraphicsPixmapItem(QPixmap(),this);
    iconSort->setPos(-8,5);
    numeroOrdreDansLeSelect=-1;
    //pas de condition sur le champ pour l'instant genre ='Dupond' ou <123
    cond=NULL;
    setAcceptDrops(true);
    connect(document(),SIGNAL(contentsChanged()),this,SIGNAL(jAiChange()));
    connect(this, SIGNAL(jAiChange()),maman , SLOT(miseAJourResultat()));

}
field::~field()
{
    qDebug()<<"field::~field()";
    if(cond!=NULL)
    {
        delete cond;
        delete trait;
    }
    if(oeil!=NULL) delete oeil;
    if(iconSort !=NULL) delete iconSort;
    //le champ s'enlève du vecteur ou il est stocké
    if(laTable!=NULL)
    {
        laTable->vecteurChamps.remove(laTable->vecteurChamps.indexOf(this),1);
    }
    else
    {//champ en dehors d'une table
        maman->vectChampsLibres.remove(maman->vectChampsLibres.indexOf(this),1);
    }
}
void field::contextMenuEvent(QGraphicsSceneMouseEvent *event)
{
    //ce qui se passe lorsque le menu contextuel du champ est appelé
    qDebug()<<"void field::contextMenuEvent(QGraphicsSceneMouseEvent *event)";
    //création du menu cntextuel du champ
    QMenu menu(QObject::tr("Field Menu"));
    //titre du menu contextuel
    QAction* titre=new QAction(menu.title(),this);
    titre->setDisabled(true);
    menu.addAction(titre);
    titre->setFont(QFont("verdana",9,3,true));
    //si je n'était pas sélectionné, je le deviens
    this->setSelected(!this->isSelected());
    //création des actions du menu
    QAction *removeAction ;
    if(freeField)
        removeAction = menu.addAction(tr("&Remove"));

    QAction *afficherAction = menu.addAction(QIcon(":/mini-eye.xpm"),tr("&Display(on/off)"));
    //affichage conditionnel du menu concernant les conditions
    QAction *addCondAction;
    QAction *removeCondAction;
    if(cond==NULL)
    {
        addCondAction= menu.addAction(QIcon(":/list-add.png"),tr("&Add Condition"));
    }
    else
    {
        removeCondAction= menu.addAction(tr("&removeCondition"));
    }
    //fin affichage du menu concernant les conditions
    QAction *choisirCritereDeTriAction=menu.addAction(QIcon(":/stock_sort-criteria.png"),tr("Sort(asc,desc,off)"));
    //exécution du menu
    QAction* actionChoisie=menu.exec(event->screenPos());
    if(actionChoisie!=NULL)
    {
        //qlq chose a été fait
        if (actionChoisie==afficherAction)
        {
            this->affiche=!this->affiche;
            this->oeil->setVisible(this->affiche);
            if(this->affiche)
            {
                this->numeroOrdreDansLeSelect=maman->maxCleDeLaMap()+1;
            }
            else
            {
                this->numeroOrdreDansLeSelect=-1;
            }
        }
        else
        {
            if(actionChoisie==choisirCritereDeTriAction)
            {
                QMenu menu2;
                QAction * asc=menu2.addAction(QIcon(":/upSort.xpm"),tr("&Asc"));
                QAction * desc=menu2.addAction(QIcon(":/downSort.xpm"),tr("&Desc"));
                QAction * off=menu2.addAction(tr("&Off"));
                QAction* triChoisi=menu2.exec(event->screenPos());
                if(triChoisi==asc)
                {
                    tri=ascSort;
                }
                else
                {
                    if(triChoisi==desc)
                    {
                        tri=descSort;
                    }
                    else
                    {
                        if(triChoisi==off)
                        {
                            tri=noSort;
                        }
                    }
                }
                QString icon;
                switch(tri)
                {
                case noSort:icon="";break;
                case ascSort:icon=":/upSort.xpm";break;
                case descSort:icon=":/downSort.xpm";break;
                }
                this->iconSort->setPixmap(QPixmap(icon));

            }
            else
            {
                if(actionChoisie==addCondAction)
                {
                    //faire une zone de saisie pour l'action
                    //et le trait et l'opérateur
                    //is null is not null
                    //= < > <>
                    ajouteCondition("="+maman->delimiteur+tr("something")+maman->delimiteur);

                }
                else
                {
                    if(actionChoisie==removeCondAction) //suppression d'une condition sur un champ
                    {
                        delete cond;
                        cond=NULL;
                        //effacer le trait aussi
                        delete trait;

                    }
                    else
                    {
                        if(actionChoisie==removeAction)
                        {

                            //si c'est un champ d'une table redimensionnement
                            deleteLater();
                        }
                    }
                }
            }
        }

        emit jAiChange();
    }//fi du si qlq chose a ete fait
}
void field::dropEvent( QGraphicsSceneDragDropEvent* event)
{
    qDebug()<<"void field::dropEvent(QDropEvent *event)";
}
void field::dragEnterEvent( QGraphicsSceneDragDropEvent* event)
{
    qDebug()<<"void field::dragEnterEvent(QDragEnterEvent *event)";
    event->accept();
}
void field::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug()<<"void field::dragMoveEvent(QGraphicsSceneDragDropEvent *event)";
    event->accept();
}
QString field::getTri()
{
    qDebug()<<"QString field::getTri()";
    QString resultat;
            switch(tri)
            {
                case noSort:resultat="";break;
                case ascSort:resultat="ASC";break;
                case descSort:resultat="DESC";break;
            }
            return resultat;
}
void field::ajouteCondition(QString texteCondition)
{
    qDebug()<<"void field::ajouteCondition(QString texteCondition)";
    cond=new QGraphicsTextItem(texteCondition,this);
    QObject::connect(cond->document(),SIGNAL(contentsChanged()),maman, SLOT(miseAJourResultat()));
    cond->setPos(100+this->boundingRect().width(),0);
    cond->setTextInteractionFlags(Qt::TextEditable);
    //et le trait
    trait=new QGraphicsLineItem(this->pos().x()+this->boundingRect().width(),QFontMetrics(cond->font()).height()/2,cond->pos().x(),cond->pos().y()+QFontMetrics(cond->font()).height()/2,this);
    //prise en compte de la modif pour raffraîchir le résultat de la requête
    emit jAiChange();
}
void field::modifieCondition(QString texteDeLaCondition)
{
    qDebug()<<"void field::modifieCondition(QString texteDeLaCondition)";
    cond->document()->setPlainText(texteDeLaCondition);
    //prise en compte de la modif pour raffraîchir le résultat de la requête
    emit jAiChange();
}
QString field::getNomComplet()
{
    qDebug()<<"QString field::getNomComplet()";
        if(laTable==NULL || freeField) return(document()->toPlainText());
        else
        {
            return(laTable->getNomEntite()+"."+document()->toPlainText());
        }
};//renvoie le nom sans ambigüité
