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
#include "entite.h"
#include <QFontMetrics>
#include <QAction>
#include <QGraphicsWidget>
#include<QGraphicsSceneContextMenuEvent>
#include <QGraphicsItem>
#include <QMenu>
#include <QDebug>
#include "field.h"
#include <QInputDialog>
#include "mainwindow.h"
#include "lien.h"
#include "association.h"
#include "lienreflexif.h"
#include <QMessageBox>


//short declarations
class Property;
class Lien;
class Association;

Entite::~Entite()
{
    qDebug()<<"Entite::~Entite()";
    if(this->rectTitle!=NULL)
    {
        delete this->rectTitle;
        rectTitle=NULL;
    }
    else
    {
        delete this->title;
        this->title=NULL;
    }


    //effacement des liens qui partent ou arrivent à l'objet
    int nbLiens=vectLiens.count();
    for(int noLien=0;noLien<nbLiens;noLien++)
    {
        Lien * leLien=vectLiens[0];
        if(leLien!=NULL)maman->supprimerLien(leLien);
    }

    for(int noChamp=0;noChamp<vecteurChamps.size();noChamp++)
    {
        vecteurChamps.remove(0);
    }

}

void Entite::setNomEntite(QString nouveauNom)
{
    nomEntite=nouveauNom;
    redraw();
}


QVariant Entite::itemChange(GraphicsItemChange change,const QVariant &value)
{
    qDebug()<<"QVariant Entite::itemChange(GraphicsItemChange change,const QVariant &value)"<<endl;
    if (change == ItemPositionHasChanged) {
        foreach (Lien *link, vectLiens)
        {
            if(!link->reflexif) link->calculeCoordonnees();
            else ((LienReflexif*)link)->LienReflexif::calculeCoordonnees();
            link->update();
        }
    }
    return QGraphicsRectItem::itemChange(change, value);
}
void Entite::redraw()
{
    qDebug()<<"void Entite::redraw()"<<endl;
    //calcul de la largeur et de la hauteur;
    long hauteur=20+QFontMetrics(title->font()).height()*(vecteurChamps.size()+2);
    long largeur=QFontMetrics(title->font()).width(nomTableTronque())+20;
    for(int noChamp=0;noChamp<vecteurChamps.count();noChamp++)
    {
        long largeurDuChamp=QFontMetrics(title->font()).width(vecteurChamps[noChamp]->getNomComplet())+20;
        if (largeurDuChamp>largeur) largeur=largeurDuChamp;
    }

    setTextColor(config->entityColor().text());
    setBrush(config->entityColor().background());
    //le titre
    if(!association)
    {
        rectTitle->setRect(0,0,largeur,QFontMetrics(title->font()).height()+10);
        rectTitle->setBrush(config->entityColor().titleBackground());
        rectTitle->setPos(0,0);
    }
    //le texte du titre
    title->setPos(0,0);//par rapport à son parent
    title->setTextWidth(boundingRect().width());
    title->setHtml("<center>"+nomTableTronque()+"</center>");

    //les champs
    int ordonnee=0;
    if(!association)ordonnee=rectTitle->rect().height();
    else ordonnee=title->boundingRect().height();
    for(int noChamp=0;noChamp<vecteurChamps.count();noChamp++)
    {
        vecteurChamps[noChamp]->setPos(10,ordonnee);
        QString texte;
        if(noChamp==0 && !association)
        {
            texte="<b><u>"+vecteurChamps[noChamp]->getNomComplet()+"</u></b>";
        }
        else texte=vecteurChamps[noChamp]->getNomComplet();

            vecteurChamps[noChamp]->setHtml(texte);
        ordonnee+=vecteurChamps[noChamp]->boundingRect().height();
    }
    //dimensions de l'objet:
    //le gros rectangle jaune de l'entité
    setRect(0,0,largeur,ordonnee+15);
    //mise à jour des liens
    foreach (Lien* leLien, vectLiens) {
       if(!leLien->reflexif)
       leLien->calculeCoordonnees();
       else
           ((LienReflexif*)leLien)->LienReflexif::calculeCoordonnees();
       leLien->update();
    }


}
int Entite::noLien(Entite* lAutre, Lien* unLien)
{
    qDebug()<<"int Entite::noLien(Entite* lAutre, Lien* unLien)";
    int resultat=0;
    foreach (Lien* leLien, vectLiens)
    {
        if((leLien->t1==this && leLien->t2==lAutre) ||(leLien->t2==this && leLien->t1==lAutre)){
            resultat++;
            if(leLien==unLien)
                return resultat;
        }
    }
    return resultat;
}
int Entite::nbLien(Entite* lAutre)
{
    qDebug()<<"int Entite::nbLien(Entite* lAutre)"<<endl;
    int resultat=0;
    foreach (Lien* leLien, vectLiens)
    {
        if((leLien->t1==this && leLien->t2==lAutre) ||(leLien->t2==this && leLien->t1==lAutre)){
            resultat++;
        }
    }
    return resultat;
}
Entite::Entite(MainWindow* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent,QStringList listeDesChamps,bool isAssoc)
        :QGraphicsRectItem(x,y,200,200,parent), QListWidgetItem(nom)

{
qDebug()<<"constructeur de table";
maman=mum;
association=isAssoc;
    nomEntite=nom;
    //le titre
    if(!association)
    {
        rectTitle=new QGraphicsRectItem(this);
        title=new QGraphicsTextItem(rectTitle);
    }
    else
    {
        title=new QGraphicsTextItem(this);
    }
    //police du titre
    title->setFont(QFont("verdana",10,QFont::Bold,false));
    //déterminons la largeur de la table ainsi que sa hauteur:
    long hauteur=20;//marge haut + basse
    hauteur+=QFontMetrics(title->font()).height();
    int marge=20;
    long largeurMaxi=QFontMetrics(title->font()).width(nomTableTronque()+marge);
    for(int noChamp=0;noChamp<listeDesChamps.count();noChamp++)
    {
        long largeurDuChamp=QFontMetrics(title->font()).width(listeDesChamps[noChamp]+nomEntite);
        hauteur+=QFontMetrics(title->font()).height();
        if (largeurDuChamp>largeurMaxi) largeurMaxi=largeurDuChamp;
    }

    //construction du QGraphicsRectItem
    setRect(x,y,largeurMaxi+10,200);

    //création du titre
    setBrush(config->entityColor().titleBackground());
    setTextColor(config->entityColor().text());
    title->setPos(0,0);//par rapport à son parent
    title->setTextWidth(boundingRect().width());
    title->setHtml("<center>"+nomTableTronque()+"</center>");

    //stockage de quelques infos
    //c'est une table
    title->setData(32,"Table");
    title->setData(34,qVariantFromValue((qlonglong)this));
    //on stocke son nom
    title->setData(33,nomEntite);
    QGraphicsItem::setData(32,"Table");
    QGraphicsItem::setData(33,nomEntite);
    QGraphicsItem::setData(34,qVariantFromValue((qlonglong)this));
    long ordonne=title->boundingRect().height();

    this->setRect(0,0,largeurMaxi+10,ordonne+10);
    //création des champs dans la table
    for(int noChamp=0;noChamp<listeDesChamps.count();noChamp++)
    {
        QString tipe="VARCHAR";
        QString taille="25";
        QString role="";
        if(noChamp==0)
        {
            tipe="INTEGER";
            taille="";
            role="Identifiant de "+nomEntite;
        }


        vecteurChamps.push_back(new Property(maman,listeDesChamps[noChamp]+nomEntite,tipe,role,taille,this));
        vecteurChamps[noChamp]->setPos(10,ordonne);
        //sa table c'est moi
        vecteurChamps[noChamp]->lEntite=this;
        //vecteurChamps[noChamp]->setFlag(QGraphicsItem::ItemIsSelectable,true);
        vecteurChamps[noChamp]->setData(32,"Field");
        vecteurChamps[noChamp]->setData(33,nom+"."+listeDesChamps[noChamp]);
        ordonne+=vecteurChamps[noChamp]->boundingRect().height();

    }
    setRect(0,0,largeurMaxi+20,ordonne+10);
    setAcceptDrops(false);
    QGraphicsRectItem::setFlags(ItemSendsGeometryChanges|ItemIsSelectable|ItemIsMovable);
}



 void Entite::contextMenuEvent(QGraphicsSceneMouseEvent *event)
 {
     //ce qui se passe lorsque le menu contextuel de la table est appelé
     qDebug()<<"void Entite::contextMenuEvent(QGraphicsSceneMouseEvent *event)";
     QMenu menu(QObject::tr("Object Menu"));
     //ajout du titre

     QAction* titre=new QAction(menu.title(),this->maman);
    titre->setDisabled(true);
    menu.addAction(titre);

    titre->setFont(QFont("verdana",9,3,true));


     //si je n'était pas sélectionnée, je le deviens
     QGraphicsItem::setSelected(true);
     //selection de l'objet
     maman->selectionne(this);
     //création des actions du menu
     QAction *removeAction = menu.addAction(QObject::tr("&Remove Object"));
     QAction *addPropertyAction = menu.addAction(QObject::tr("&Add property"));
     QAction *renameAction=menu.addAction(QObject::tr("re&Name Object"));
     //exécution du menu
     QAction * actionChoisie=menu.exec(event->screenPos());
     if(actionChoisie==removeAction)
     {
         maman->tableSupprimer(this);
     }
     else
     {
         if(actionChoisie==addPropertyAction)
         {
             maman->tableAjouterChamp(this);
         }
         else
         {
             if(actionChoisie==renameAction)
             {
                 maman->renameEntity(this);
             }
         }
     }

 }


QVector<Entite*> Entite::renvoieEntiteMeres()
{
    qDebug()<<"QVector<Entite*> Entite::renvoieEntiteMeres()"<<endl;
    QVector<Entite*> resultat;
    foreach (Lien* leLien, vectLiens)
    {
        if (LEAKRELATION==leLien->typeDeJointure)
        {
            if(leLien->t1==this)
            {
                resultat.push_back(leLien->t2);
            }
        }
    }
    return resultat;
}
QStringList Entite::renvoieChampsEtrangers()
{
    qDebug()<<"QStringList Entite::renvoieChampsEtrangers()"<<endl;
    QStringList resultat;

    foreach (Lien* leLien, vectLiens)
    {
        if (CIF==leLien->typeDeJointure or DF==leLien->typeDeJointure or LEAKRELATION==leLien->typeDeJointure)
        {
            if(leLien->t1==this)
            {
                if(leLien->role!=NULL)
                {
                    //resultat<<leLien->texteDuRole;
                    QStringList ajout=leLien->t2->getPrimaryKeyAsFields().split(" ");
                    ajout[0]=leLien->texteDuRole;
                    resultat<<ajout.join(" ");
                }
                else
                {
                    QString chEtrangers=leLien->t2->getPrimaryKeyAsFields();
                    resultat<<chEtrangers;
                }
                if (DF==leLien->typeDeJointure)//enlever les not null
                {
                    resultat.replaceInStrings("not null","",Qt::CaseInsensitive);
                }
            }
        }
        if (LEG==leLien->typeDeJointure)
        {
            if(leLien->t2==this)
            {   if(leLien->role!=NULL)
                {
                    QString ch=leLien->t1->getPrimaryKeyAsFields();
                    QStringList sl=ch.split(' ');
                    sl[0]=leLien->texteDuRole;
                    resultat<<sl.join(" ");
                }

                else
                    resultat<<leLien->t1->getPrimaryKeyAsFields();//+chObligatoire;
            }
        }
    }
    return resultat;
}
QStringList Entite::renvoieClefsEtrangeres(bool constraintInsideTable)
{
    qDebug()<<"QStringList Entite::renvoieClefsEtrangeres(bool constraintInsideTable)"<<endl;
    QStringList resultat;
    QString debut="";
    if(!constraintInsideTable)debut="ALTER TABLE "+nomEntite+" ADD ";
    QString fin="";
    if(!constraintInsideTable)fin=";";

    foreach (Lien* leLien, vectLiens)
    {
        if (CIF==leLien->typeDeJointure or DF==leLien->typeDeJointure or LEAKRELATION==leLien->typeDeJointure)
        {
            if(leLien->t1==this)
            {
                resultat<<debut+leLien->t2->getkeyAsForeignKey(leLien->texteDuRole)+fin;
            }
        }
        if (LEG==leLien->typeDeJointure)
        {
            if(leLien->t2==this)
            {
                resultat<<debut+leLien->t1->getkeyAsForeignKey(leLien->texteDuRole)+fin;
            }
        }
    }
    return resultat;
}
bool Entite::canBeWriten(QVector <Entite*>vectEntitesGeneres)
{
    qDebug()<<"bool Entite::canBeWriten(QVector <Entite*>vectEntitesGeneres)"<<endl;
    bool resultat=true;
    foreach (Lien* leLien, vectLiens)
    {
        if (CIF==leLien->typeDeJointure or DF==leLien->typeDeJointure or LEAKRELATION==leLien->typeDeJointure)
        {
            if(leLien->t1==this)
            {
                resultat=resultat && (vectEntitesGeneres.contains(leLien->t2)||leLien->t1==leLien->t2);
            }
        }
        if (LEG==leLien->typeDeJointure)
        {
            if(leLien->t2==this)
            {
                //resultat<<leLien->t1->getkeyAsForeignKey();
                resultat=resultat && vectEntitesGeneres.contains(leLien->t1);
            }
        }
    }
    return resultat;
}

bool Entite::isEntiteFaible()
{
    return(renvoieEntiteMeres().size()>0);
}

QString Entite::getPrimaryKey()
{
qDebug()<<"QString Entite::getPrimaryKey()"<<endl;
    if(!association)
    {

        if(!isEntiteFaible())//entité
        {
            if (vecteurChamps.length()==0)
                return QObject::tr("&lt;Provide manually&gt;");
            else return '`'+vecteurChamps[0]->nom+'`';
        }
        else //entité faible
        {
            //obtention des tables mères
            QVector<Entite*> entitesMeres=renvoieEntiteMeres();
            QStringList listeDesNoms;
            foreach (Entite* lEntite, entitesMeres)
            {
                listeDesNoms<<lEntite->getPrimaryKey();
            }
            if (vecteurChamps.length()>0)
            listeDesNoms<<vecteurChamps[0]->nom;
            return listeDesNoms.join(',');
        }
    }
    else//association
    {
        //prendre l'ensemble des clefs de chaque patte de l'assoc
        QVector<QPair <Entite*,QString> > vectEnt=((Association*)this)->vectEntitesRolesAssociees();
        QStringList slPK;
        QPair<Entite*,QString> laPaire;
        foreach (laPaire, vectEnt)
        {
            //attention changer le nom par le role s'il y a rôle
            //trouver le lien correspondant
            //s'il a un rôle remplacer identifiant par role
            if(laPaire.second=="")
            {
                slPK<<laPaire.first->getPrimaryKey();
            }
            else
            {
                QString laClef=laPaire.first->getPrimaryKey();
                QStringList sL=laClef.split(" ");
                sL[0]=laPaire.second;//leRole
                slPK<<sL.join(" ");
            }

        }//fin du foreach

        return slPK.join(',');
    }
}


QString Entite::getPrimaryKeyAsFields()
{
    qDebug()<<"QString Entite::getPrimaryKeyAsFields()"<<endl;
    QString chObligatoire=" NOT NULL";
    if(!association)
    {
        if(!isEntiteFaible())//je suis une entité
        {
            if(vecteurChamps.size()==0)//ça peut arriver
                return QObject::tr("&lt;Provide manually&gt;");
            else
            {
                QString laChaine="`"+this->vecteurChamps[0]->nom+"` "+this->vecteurChamps[0]->sonType;
                QString taille=this->vecteurChamps[0]->taille;
                if(!taille.isEmpty()) laChaine+="("+taille+")";
                return(laChaine+chObligatoire);
            }
        }
        else//c'est une entite faible
        {
            //obtention des tables mères
            QVector<Entite*> entitesMeres=renvoieEntiteMeres();
            QStringList listeDesNoms;
            foreach (Entite* lEntite, entitesMeres)
            {
                QString laChaine=lEntite->getPrimaryKeyAsFields();
                listeDesNoms<<laChaine;
            }
            QString resultat=listeDesNoms.join(',')+",`"+vecteurChamps[0]->nom+"` "+this->vecteurChamps[0]->sonType;
            QString taille=this->vecteurChamps[0]->taille;
            if(!taille.isEmpty()) resultat+="("+taille+")";
            return resultat+chObligatoire;
        }
    }
    else//c'est une association
    {
        //prendre l'ensemble des clefs de chaque patte de l'assoc
        QVector< QPair <Entite*,QString> > vectEnt=((Association*)this)->vectEntitesRolesAssociees();
        QStringList slPK;
        QPair<Entite*,QString> laPaire;
        foreach (laPaire, vectEnt)
        {
            //attention changer le nom par le role s'il y a rôle
            //trouver le lien correspondant
            //s'il a un rôle remplacer identifiant par role
            if(laPaire.second=="")
            {
                slPK<<laPaire.first->getPrimaryKeyAsFields();
            }
            else
            {
                QString laClef=laPaire.first->getPrimaryKeyAsFields();
                QStringList sL=laClef.split(" ");
                sL[0]=laPaire.second;//leRole
                slPK<<sL.join(" ");
            }

        }//fin du foreach
        return slPK.join(',');
    }
}
QString Entite::getkeyAsForeignKey(QString role)
{
    qDebug()<<"QString Entite::getkeyAsForeignKey(QString role)"<<endl;
    QString motReserve=config->getSqlGenEntityReservedColor().name();
    QString laChaine="<font color=\""+motReserve+"\"> foreign key </font> (";
    if(role.isEmpty())
    {
        laChaine+=getPrimaryKey();
    }
    else
    {
        laChaine+=role;
    }
    laChaine+=+") <font color=\""+motReserve+"\">references</font> "+this->nomEntite+"("+getPrimaryKey()+")";
    return(laChaine);
}
QString Entite::toSql(bool withoutFK)
{
    qDebug()<<"QString Entite::toSql()";
    QStringList defs;
    QString resultat;
    //le début de  la requête
    QString motReserve=config->getSqlGenEntityReservedColor().name();
    QString nomTable=config->getSqlGenEntityNameColor().name();
    //contient la listeDesChamps pour assurer l'unicité
    QStringList defChampSansHtml;

    resultat="<font color=\""+motReserve+"\">CREATE TABLE</font> <font color=\""+nomTable+"\">`"+getNomEntite()+"`</font>(";
    //demander à chaque champ de l'entité de s'écrire ici

    foreach (Property* leChamp, vecteurChamps)
    {
        if(!defChampSansHtml.contains(leChamp->nom))
        {
          defs<<leChamp->toSql();
          defChampSansHtml<<leChamp->nom;
        }
        else
        {
            QMessageBox::warning(0,"GapMea",QObject::tr("The field: ")+leChamp->nom+QObject::tr(" is twice in ")+getNomEntite()+QObject::tr("\r\n Please remove one."),QMessageBox::Ok,QMessageBox::Ok);
            return QObject::tr("Sorry but object ")+getNomEntite()+QObject::tr(" cannot be generated");
        }
    }//fin du foreach

    //les champs étrangers
    QStringList champsEtrangers=renvoieChampsEtrangers();
    for(int noChampEtranger=0;noChampEtranger<champsEtrangers.count();noChampEtranger++)
    {
        qDebug()<<"Recherche de";
        qDebug()<<champsEtrangers.at(noChampEtranger).split(" NOT NULL")[0].split(" ")[0].replace("`","");
        qDebug()<<"dans:";
        qDebug()<<defChampSansHtml;

        if(defChampSansHtml.contains(champsEtrangers.at(noChampEtranger).split(" NOT NULL")[0].split(" ")[0].replace("`","")))
        {
            QMessageBox::warning(0,"GapMea",QObject::tr("You should not have the field: ")+champsEtrangers.at(noChampEtranger).split(" ")[0]+QObject::tr(" in ")+getNomEntite(),QMessageBox::Ok,QMessageBox::Ok);
            return QObject::tr("<font color=\"red\">Error in object  <b>")+getNomEntite()+QObject::tr("</b>\r\n</font> You should remove foreign property from this object.");
        }
        else
        {
            defs.append(champsEtrangers.at(noChampEtranger));
        }
    }


    //les clés étrangères

    if(!withoutFK) defs.append(renvoieClefsEtrangeres());

    //la clef primaire
    defs.append("<font color=\""+motReserve+"\"><b>primary key</b></font>(<u>"+getPrimaryKey()+"</u>)");
    //ajout des définitions
    resultat+=defs.join(',');
    //la toute fin de la requête
    resultat+=");";
    return resultat;
}
