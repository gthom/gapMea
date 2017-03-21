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
#include "lien.h"
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QTextDocument>
#include <QPainter>
#include <QInputDialog>
#include <QVector>
#include <QGraphicsEllipseItem>
#include <association.h>


Lien::~Lien()
{
    if(!reflexif)
    {
        qDebug()<<"destructeur du lien";
        //je me retire du vecteur de mes deux tables
        int monIndexDansT1=t1->vectLiens.indexOf(this);
        if(monIndexDansT1!=-1) t1->vectLiens.remove(monIndexDansT1,1);
        int monIndexDansT2=t2->vectLiens.indexOf(this);
        if(monIndexDansT2!=-1) t2->vectLiens.remove(monIndexDansT2,1);
        //je me retire du vecteur de la MainWindow
        int monIndexDansLaMW=t1->maman->vectLiens.indexOf(this);
        if(monIndexDansLaMW!=-1) t1->maman->vectLiens.remove(monIndexDansLaMW,1);
    }
    //les pointeurs instanciés par le constructeur sont automatiquement libérés car le parent des différents éléments est "this"
}

Lien::Lien(Entite* pt1,Entite* pt2,QGraphicsItem * parent,QString typ, QString relationName, QString pRole):QGraphicsItemGroup(parent)
{
    qDebug()<<"lien::lien(Entite* pt1,Entite* pt2,QGraphicsItem * parent,QString typ, QString relationName, QString pRole)";
    //initialisation à NULL des pointeurs facultatifs
    reflexif=false;
    lignePointillee=NULL;
    leRond=NULL;
    laFleche=NULL;
    cardinalite2=NULL;
    role=NULL;
    //construction de la ligne pas de parent sinon coordonnées relatives au parent
    line=new QGraphicsLineItem();
    line->setData(32,"Lien");
    //mémorisation de la source et de la cible
    t1=pt2;
    t2=pt1;
    //création de la cardinalité1
    cardinalite1=new QGraphicsSimpleTextItem();
    cardinalite1->setData(32,"Lien");
    cardinalite1->setZValue(129);
    if(!pRole.isEmpty())
    {
        //création du rôle si besoin
        this->texteDuRole=pRole;
        role=new QGraphicsSimpleTextItem(texteDuRole);
        role->setZValue(130);
    }
    //si c'est une cif ou une df ou une entité faible
    if(typ==CIF or typ==DF or typ==LEAKRELATION)
    {
        //il y a une deuxieme cardinalité
        cardinalite2=new QGraphicsSimpleTextItem();
        //ajout de la flêche
        laFleche=new QGraphicsPolygonItem();
        //ajout du rond où est marqué cif ou df
        leRond=new QGraphicsEllipseItem();
        leRond->setData(32,"Lien");//il dit que c'est un lien
        leRond->setBrush(QBrush(QColor("#FFD4A3")));
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
        leTexteDuRond->setDefaultTextColor(Qt::black);
        //les cardinalites
        cardinalite2->setText("0,n");
        //determination de la cardinalité1
        if(typ==CIF)
        {
            cardinalite1->setText("1,1");
        }
        else
        {
            if(typ==DF)
            {
                cardinalite1->setText("0,1");

            }
            else
            {
                if(typ==LEAKRELATION)
                {
                    cardinalite1->setText("(1,1)");
                }
            }
        }//fin determination cardinalité 1
    }//fin de si c'est une df une cif ou une entité faible
    else//c'est soit une patte soit une association
    {
        //si c'est une patte
        if(typ==LEG)
        {
            cardinalite1->setText("0,n");
        }
        else //ce n'est pas une patte
        {
            //si c'est une association
            if(typ==RELATION)
            {
                typ=LEG;
                cardinalite1->setText("0,n");
                if(cardinalite2!=NULL)cardinalite2->setText("");
                //création de l'association
                QStringList listeVide;
                Association* nouvelleAssoc=new Association(t1->maman,relationName,this->boundingRect().x()+this->boundingRect().width()/2,this->boundingRect().y()+this->boundingRect().height()/2,parent,listeVide,true);
                //abcisse et ordonnee
                float abcisse=(t1->x()+t1->boundingRect().width()+t2->x()+t2->boundingRect().width()-nouvelleAssoc->rect().width())/2.0;
                float ordonnee=(t1->y()+t1->boundingRect().height()+t2->y()+t2->boundingRect().height()-nouvelleAssoc->boundingRect().height())/2.0;
                //ajout au vecteur de la mainWindow
                t1->maman->ajouteTable(nouvelleAssoc);
                t1->maman->getScene()->addItem(nouvelleAssoc);
                //créer un autre lien entre l'assoc et t2
                bool ok;
                QString nomDuRole="";
                if(t1==t2)
                {
                  while(!(nomDuRole!="" &&ok))
                  {
                      nomDuRole=QInputDialog::getText(0,QObject::tr("GapMea_ Rôle Input"),
                                                  QObject::tr("Rôle Name:"),
                                                  QLineEdit::Normal,
                                                  "",
                                                  &ok);
                  }
                }
                Lien* nouveauLien=new Lien(nouvelleAssoc,t2,0,LEG,"",nomDuRole);
                //je l'ajoute à la scene
                t1->maman->getScene()->addItem(nouveauLien);
                //on ajoute les éléments du groupe
                nouveauLien->ajouteElementsAuGroupe();
                //faire pointer t2 sur l'association
                t2=nouvelleAssoc;
                t2->setPos(abcisse,ordonnee);
            }//fin du si c'est une association
            else
            {
                qDebug()<<"ERREUR TYPE DE RELATION INCONNU"<<endl;
            }
        }//fin du ce n'est pas une patte
    } //fin du "c'est soit une patte soit une association"
    this->typeDeJointure=typ;
    setData(32,"Lien");
    //en arrière plan
    setZValue(-1000.0);
    //remplir les vecteurs de lien
    //de la mainWindow et du ou des objets associés
    t1->maman->vectLiens.append(this);
    //de la table t1
    t1->vectLiens.append(this);
    //de la table t2 si ce n'est pas la même que t1(reflexive)
    if(t2!=t1) //non reflexive
        t2->vectLiens.append(this);
    else
    {
        //reflexive  (df)
        //???
    }
    QGraphicsItemGroup::setFlags(ItemIsSelectable);
}//fin du constructeur de lien

/**
 * @brief Lien::ajouteElementsAuGroupe
 * doit être appelé après la construction du lien
 *
 */
void Lien::ajouteElementsAuGroupe()
{
    qDebug()<<"void Lien::ajouteElementsAuGroupe()";
    //je place bien les composants avant de les ajouter au groupe
    calculeCoordonnees();
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
}

void Lien::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsItemGroup::paint(painter,option,widget);
    if (option->state & QStyle::State_Selected) {
                  QPen outline;
           outline.setColor(Qt::red);
           outline.setWidth(2);
           line->setPen(outline);
       }
       else line->setPen(QPen());
}

void Lien::contextMenuEvent(QGraphicsSceneMouseEvent *event)
{
    //ce qui se passe lorsque le menu contextuel de la table est appelé
     qDebug()<<"void lien::contextMenuEvent(QGraphicsSceneMouseEvent *event)";
     QMenu menu(QObject::tr("Link Menu"));
     //si je n'était pas sélectionnée, je le deviens
     if(!isSelected())
     {
         this->setSelected(true);
         qDebug()<<"je n'étais pas sélectionné je le sélectionne";
     }
     else
     {
         qDebug()<<"je suis déjà sélectionné";
         this->setSelected(false);
         this->setSelected(true);
     }

     //titre du menu
     QAction* titre=new QAction(menu.title(),scene());
    titre->setDisabled(true);
    menu.addAction(titre);
    //titre->setSeparator(true);
    titre->setFont(QFont("verdana",9,3,true));
    //si je n'était pas sélectionnée, je le deviens
    this->setSelected(!this->isSelected());
     //création des actions du menu
     QAction *removeAction = menu.addAction(QObject::tr("&Remove"));

     //s'il y a une condition proposer de l'éditer
     QAction* editRoleAction=menu.addAction(QObject::tr("&Edit Rôle"));

     //exécution du menu et récupération de l'action choisie
     QAction * actionChoisie=menu.exec(event->screenPos());

      //autre choix du menu
         if(actionChoisie==removeAction)
         {
             t1->maman->supprimerLien(this);
         }
         else
         {
             if(actionChoisie==editRoleAction)
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
                         delete cardinalite2;
                         cardinalite2=NULL;
                     }
                     else
                         role->setText(text);
                 }
             }
         }
}
void Lien::calculeCoordonnees()
{
    qDebug()<<"void Lien::calculeCoordonnes()";
    //décaler si plus d'un lien entre les deux mêmes objets
    int noLien=t1->noLien(t2,this);
    int ordonnee=10*noLien;
    //obtenir le nb de lien
    int nbLiensEntreT1EtT2=t1->nbLien(t2);
    //répartir en fonction du nb de lien
    //calculs dans t1
    int ecartEntreDeuxLiensDansT1=(t1->boundingRect().width()-20)/nbLiensEntreT1EtT2;
    //xDuPremier
    int abcisseDuCentreDansT1=t1->boundingRect().width()/2;
    int abcisseDuPremierDanT1=abcisseDuCentreDansT1-(nbLiensEntreT1EtT2-1)/2.0*ecartEntreDeuxLiensDansT1;
    int monAbcisseDansT1=abcisseDuPremierDanT1+(noLien-1)*ecartEntreDeuxLiensDansT1;
    QPointF origine=t1->pos()+QPointF(monAbcisseDansT1,ordonnee);

    //calculs dans t2
    int ecartEntreDeuxLiensDansT2=(t2->boundingRect().width()-20)/nbLiensEntreT1EtT2;
    //xDuPremier
    int abcisseDuCentreDansT2=t2->boundingRect().width()/2;
    int abcisseDuPremierDanT2=abcisseDuCentreDansT2-(nbLiensEntreT1EtT2-1)/2.0*ecartEntreDeuxLiensDansT2;
    int monAbcisseDansT2=abcisseDuPremierDanT2+(noLien-1)*ecartEntreDeuxLiensDansT2;
    QPointF destination=t2->pos()+QPointF(monAbcisseDansT2,ordonnee);
    QLineF centerLine(origine,destination);
    //les polygones des deux objets
    QPolygonF endPolygon = t2->polygon();
    QPolygonF beginPolygon = t1->polygon();

    QPointF p1 = endPolygon.first()+t2->pos() ;
    QPointF p2;
    QPointF intersectPointT2;
    QLineF polyLine;
    //pour les 4 lignes de l'entité de destination

    for (int i = 1; i < endPolygon.count(); ++i)
    {
        p2 = endPolygon.at(i)+t2->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPointT2);
        //s'il y a intersection
        if (intersectType == QLineF::BoundedIntersection)
        {
            break;
        }
        //je passe au suivant
        p1 = p2;
    }
    p1 = beginPolygon.first()+t1->pos() ;

    QPointF intersectPointT1;

    for (int i = 1; i < beginPolygon.count(); ++i)
    {
        p2 = beginPolygon.at(i)+t1->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPointT1);
        if (intersectType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }

    //ici on a le point de départ et d'arrivée
    //qui sont dans intersectPointT1 et intersectPointT2
    if(t1==t2)//si c'est une réflexive
    {
        intersectPointT1=origine;
        //ne pas toucherà intersectPointT2
    }

    if(t1!=t2 && t1->collidesWithItem(t2))
    {
        intersectPointT1=origine;
        intersectPointT2=destination;
        qDebug()<<"DEDANS************"<<endl;
        this->setEnabled(false);
        this->hide();
    }
    else//essais
    {
        if(!this->isEnabled())
        {
            this->setEnabled(true);
            this->show();
        }
        //pour que les pattes ne touchent pas les pseudos entités
        if(t2->association && t1->association)
        {
            QLineF myLine=QLineF(intersectPointT1,intersectPointT2);
            QPointF destination(myLine.pointAt(0.1).x(),myLine.pointAt(0.1).y());
            myLine.setP1(destination);
            intersectPointT1=myLine.p1();
            //dessiner les pointillés
            QLineF perpendiculaire=myLine.normalVector();
            perpendiculaire.setLength(10);
            QPointF deb,fin;
            deb=perpendiculaire.p2();
            fin=perpendiculaire.p1();
            perpendiculaire.setP1(deb);
            perpendiculaire.setP2(fin);
            //je double la longueur
            perpendiculaire.setLength(perpendiculaire.length()*2);
            if(lignePointillee==NULL)
            {
                lignePointillee=new QGraphicsLineItem(this);
                addToGroup(lignePointillee);
            }
            lignePointillee->setLine(perpendiculaire);
        }
        //desssin de la ligne
        line->setLine(QLineF(intersectPointT1,intersectPointT2));
        //placement du rond de la cif ou df ou entité faible
        if(typeDeJointure==CIF || typeDeJointure==DF || typeDeJointure==LEAKRELATION)
        {
            //position de la fleche
            QPointF presquAuBout=line->line().pointAt(0.99);
            QLineF maLigne(presquAuBout,intersectPointT2);
            QLineF normalVector=maLigne.normalVector();
            QPointF bout1=normalVector.pointAt(1);
            QLineF normalVector2=QLineF(intersectPointT2,bout1).normalVector();
            QPointF bout2=normalVector2.pointAt(1);
            QVector<QPointF> vectP;
            vectP<<intersectPointT2<<bout1<<bout2;
            laFleche->setPolygon(QPolygonF(vectP));
            //déplacement du rond
            QPointF position=line->line().pointAt(0.5);
            if(t1==t2) position=line->line().pointAt(0.01);
            int largeur=leRond->rect().width();
            position.setX(position.x()-largeur/2);
            position.setY(position.y()-largeur/2);
            leRond->setRect(position.x(),position.y(),largeur,leRond->rect().height());
            leTexteDuRond->setPos(position);
        }
        int tailleDuRole=0;
        if(role!=NULL)tailleDuRole=role->boundingRect().width();
        //les cardinalités et le rôle
        QPointF posTexte1,posTexte2,posRole;
        if(intersectPointT1.x()<intersectPointT2.x())//t1 a gauche
        {
            posTexte1.setX(intersectPointT1.x());
            if(cardinalite2!=NULL)posTexte2.setX(intersectPointT2.x()-cardinalite2->boundingRect().width());
            //positionnement du role
            float position=(tailleDuRole+10)/line->line().length();
            if(role!=NULL)
            {
                posRole=line->line().pointAt(1-position);
                role->setRotation(-1*line->line().angle());
            }
            if(intersectPointT1.y()<intersectPointT2.y())//t1 est en haut à gauche
            {
                posTexte1.setY(intersectPointT1.y());
                if(cardinalite2!=NULL)posTexte2.setY(intersectPointT2.y()-cardinalite2->boundingRect().height());
                //diminution du y du role
                if(role!=NULL)posRole.setY(posRole.y()-25);
                qDebug("haut/gauche");
            }
            else//t1 est en bas à gauche
            {
                posTexte2.setY(intersectPointT2.y());
                posTexte1.setY(intersectPointT1.y()-cardinalite1->boundingRect().height());
                qDebug("bas gauche");
            }
        }
        else//t1 à droite
        {
            posTexte2.setX(intersectPointT2.x());
            posTexte1.setX(intersectPointT1.x()-cardinalite1->boundingRect().width());
            //positionnement du role
            if(role!=NULL)
            {
                posRole=line->line().pointAt(0.9);
                //rotation
                role->setRotation(180-line->line().angle());
            }
            if(intersectPointT1.y()<intersectPointT2.y())//t1 est en haut droite
            {
                posTexte1.setY(intersectPointT1.y());
                if(cardinalite2!=NULL)posTexte2.setY(intersectPointT2.y()-cardinalite2->boundingRect().height());
                //diminution du x du role
                if(role!=NULL)posRole.setY(posRole.y()-20);
                qDebug()<<"haut droite";
            }
            else//t1 est en bas droite
            {
                posTexte2.setY(intersectPointT2.y());
                posTexte1.setY(intersectPointT1.y()-cardinalite1->boundingRect().height());
                //diminution du x du role
                if(role!=NULL)
                {
                    posRole.setX(posRole.x()+20);
                    posRole.setY(posRole.y()-20);
                }
                qDebug()<<"bas droite";
            }
        }
        cardinalite1->setPos(posTexte1);
        //positionnement  du role
        if(cardinalite2!=NULL)cardinalite2->setPos(posTexte2);
        if(role!=NULL)role->setPos(posRole);
    }//fin du else

    qDebug()<<"FIN calcul coordonnees"<<endl;
}//fin de la méthode calculeCoordonnees

bool Lien::estRelieA(Lien* autreLien)
{
    qDebug()<<"bool Lien::estRelieA(Lien* autreLien)";
    return ((autreLien->t1==t1) or (autreLien->t1==t2) or (autreLien->t2==t1) or (autreLien->t2==t2));
}
