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
#include "lienreflexif.h"
#include <QDebug>
#include <QInputDialog>

LienReflexif::LienReflexif(Entite *qg1, Entite *qg2, QGraphicsItem *parent, QString typ, QString relationName, QString pRole):Lien(qg1,qg2,parent,typ,relationName,pRole)
{
    qDebug()<<"LienReflexif::LienReflexif(Entite* pt1,Entite* pt2,QGraphicsItem * parent,QString typ, QString relationName, QString pRole)";
    //initialisation à NULL des pointeurs facultatifs
    reflexif=true;
    lignePointillee=NULL;
    leRond=NULL;
    laFleche=NULL;
    cardinalite2=NULL;
    role=NULL;
    //construction de la ligne pas de parent sinon coordonnées relatives au parent
    line=new QGraphicsLineItem();
    line->setData(32,"Lien");
    firstLine=new QGraphicsLineItem();
    firstLine->setData(32,"Lien");
    lignePointillee=new QGraphicsLineItem();
    lignePointillee->setData(32,"Lien");
    //le lien  n'est pas sélectionnable et il n'est pas déplaçable
    //this->setFlags(QGraphicsItemGroup::ItemIsSelectable);
    //mémorisation de la source et de la cible
    t1=qg1;
    t2=qg2;

    //création de la cardinalité1
    cardinalite1=new QGraphicsSimpleTextItem();
    cardinalite1->setData(32,"Lien");
    cardinalite1->setZValue(129);
    //le rôle
    if(!pRole.isEmpty())
    {
        //création du rôle si besoin
        this->texteDuRole=pRole;
        role=new QGraphicsSimpleTextItem(texteDuRole);
        role->setZValue(130);
    }
    else //création du rôle
    {
        bool ok;
        QString text = QInputDialog::getText(0, QObject::tr("Edit Rôle"),
                                             QObject::tr("Rôle:"), QLineEdit::Normal,
                                             this->texteDuRole, &ok);
        if (ok && !text.isEmpty()&& text!=texteDuRole)//il a changé le rôle
        {
            this->texteDuRole=text;
            if(role==NULL)
            {
                role=new QGraphicsSimpleTextItem(text,this);

            }
            role->setText(text);
        }
    }
    //ce ne peut être qu'une DF
    if(typ==DF)
    {
        //il y a une deuxieme cardianlité
        cardinalite2=new QGraphicsSimpleTextItem();
        //ajout de la flêche
        laFleche=new QGraphicsPolygonItem();
        //ajout du rond où est marqué cif ou df
        leRond=new QGraphicsEllipseItem();
        leRond->setData(32,"Lien");//il dit que c'est un lien
        leRond->setBrush(QBrush(QColor(config->getReflectiveLinkBackgroundColor())));
        //le texte (CIF ou DF)
        leTexteDuRond=new QGraphicsTextItem(leRond);
        //determination diametre du rond
        int diametre=QFontMetrics(leTexteDuRond->font()).width(" CIF ");
        QPoint position=boundingRect().center().toPoint();
        position.setX(position.x()-diametre/2);
        leRond->setRect(position.x(),position.y(),diametre,diametre);
        leTexteDuRond->setData(32,"Lien");//il dit que c'est un lien
        leTexteDuRond->setHtml(typ.toUpper().left(3));
        //position du texte
        QPoint positionTexte=boundingRect().center().toPoint();
        positionTexte.setX(positionTexte.x()-QFontMetrics(leTexteDuRond->font()).width(" CIF ")/2);
        leTexteDuRond->setPos(positionTexte);
        leTexteDuRond->setDefaultTextColor(config->getReflectiveLinkTextColor());
        //les cardinalites
        cardinalite2->setText("0,n");
        //determination de la cardinalité1
       cardinalite1->setText("0,1");
    }//fin de si c'est une df une cif ou une entité faible
    else//c'est soit une patte soit une association
    {
        qDebug()<<"ERREUR reflexive non DF"<<endl;

    }
}
void LienReflexif::calculeCoordonnees()
{
    qDebug()<<"void LienReflexif::calculeCoordonnes()";
    int diametreRond=leRond->boundingRect().height();
    //décaler si plus d'un lien entre les deux mêmes objets
    int noLien=t1->noLien(t1,this);
    //obtenir le nb de lien
    //int nbLiensEntreT1EtT2=t1->nbLien(t1);
    int nbLiensEntreT1EtT2=4;
    int ordonnee=diametreRond*(nbLiensEntreT1EtT2-(noLien/2));

    qDebug()<<"no du lien:"<<noLien<<endl;

    //répartir en fonction du nb de lien
    //calculs dans t1
    int abcisseDuCentreDansT1=t1->boundingRect().width()/2;
    int decalageX=diametreRond;
    decalageX*=(noLien/2)+1;
    QPointF positionDuRond;
    positionDuRond=t1->pos()+QPointF(abcisseDuCentreDansT1,-ordonnee);
    leRond->setPos(positionDuRond);
    QPointF depart=t1->pos()+QPointF(decalageX,0);
    QPointF destination=depart+QPointF(0,-ordonnee+0.5*diametreRond);
    //elle est bonne
    QLineF lfirstLine(depart,destination);
    firstLine->setLine(lfirstLine);
    //j'inverse la ligne
    lfirstLine=QLineF(destination,depart);
    //trouve la perpendiculaire
    QLineF vector=lfirstLine.normalVector();
    //calcul de la longueur de la perpendiculaire
    vector.setLength(t1->rect().width()-2*decalageX);
    //elle est bonne
    lignePointillee->setLine(vector);
    //pour que le trait soit derrière le disque
    lignePointillee->setZValue(-254);
    //inversion du vecteur
    vector=QLineF(vector.p2(),vector.p1());
    QLineF retour=vector.normalVector();
    retour.setLength(ordonnee-0.5*diametreRond);
    QPointF intersectPointT2=retour.p2();
    //retour.intersect(QLineF(t1->rect().topLeft(),t1->rect().topRight()),&intersectPointT2);
    //dessin de la ligne
    line->setLine(QLineF(retour.p1(),intersectPointT2));
    //position de la fleche
    QPointF presquAuBout=line->line().pointAt(0.90);
    QLineF maLigne(presquAuBout,intersectPointT2);
    QLineF normalVector=maLigne.normalVector();
    QPointF bout1=normalVector.pointAt(1);
    QLineF normalVector2=QLineF(intersectPointT2,bout1).normalVector();
    QPointF bout2=normalVector2.pointAt(1);
    QVector<QPointF> vectP;
    vectP<<intersectPointT2<<bout1<<bout2;
    laFleche->setPolygon(QPolygonF(vectP));
    //positionnement des cardinalités et des rôles
    cardinalite2->setPos(retour.p2()+QPointF(0,-ordonnee));
    cardinalite1->setPos(depart+QPointF(0,-ordonnee));
    //positionnement des roles
    if(role!=NULL)
    {
        role->setPos(depart);
        role->setRotation(-1+firstLine->line().angle());
    }
    qDebug()<<"FIN calcul coordonnees"<<endl;

}

void LienReflexif::ajouteElementsAuGroupe()
{
    LienReflexif::calculeCoordonnees();
    //la ligne
    addToGroup(line);
    //la première cardianlité
    addToGroup(cardinalite1);
    //le rôle s'il y en a
    if(role!=NULL)addToGroup(role);
    //la cardinalité2 si ce n'est pas une patte
    if(cardinalite2!=NULL)addToGroup(cardinalite2);
    //la fleche si besoin
    if(laFleche!=NULL)addToGroup(laFleche);
    //le rond central si besoin
    if(leRond!=NULL)addToGroup(leRond);
    //la ligne pointillée si pseudo-entité
    if(lignePointillee!=NULL)addToGroup(lignePointillee);
    addToGroup(firstLine);
}

LienReflexif::~LienReflexif()
{
    qDebug()<<"destructeur du lien Reflexif";
    //je me retire du vecteur de mes deux tables
    if(t1!=NULL)
    {
        int monIndexDansT1=t1->vectLiens.indexOf(this);
        if(monIndexDansT1!=-1) t1->vectLiens.remove(monIndexDansT1,1);

        //je me retire du vecteur de la MainWindow
        if(t1->maman!=NULL)
        {
            int monIndexDansLaMW=t1->maman->vectLiens.indexOf(this);
            if(monIndexDansLaMW!=-1) t1->maman->vectLiens.remove(monIndexDansLaMW,1);
        }
    }
    //les pointeurs instanciés par le constructeur sont automatiquement libérés car le parent des différents éléments est "this"
}

void LienReflexif::refreshColors()
{
    Lien::refreshColors();
    if (leTexteDuRond)
        leTexteDuRond->setDefaultTextColor(config->getLinkTextColor());
    if (leRond)
        leRond->setBrush(QBrush(config->getLinkBackgroundColor()));
}
