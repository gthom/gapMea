#include "xmeareader.h"
#include "lien.h"
#include "lienreflexif.h"
#include <QDebug>

XMeaReader::XMeaReader(MainWindow * maman)
{
    mum=maman;
    //mum->getScene()->clear();
}

bool XMeaReader::readFile(QIODevice *device)
{
    qDebug()<<"bool XMeaReader::readFile(QIODevice *device)";
    setDevice(device);

    if (readNextStartElement()) {
        if (name() == "xmea" && attributes().value("version") == "1.0")
        {
            //efacer tout
            mum->effaceTout();
            readMea();
        }
        else
            raiseError(QObject::tr("The file is not an XMEA version 1.0 file."));
    }

    return !error();

}

void XMeaReader::readMea()
{
    qDebug()<<"void XMeaReader::readMea()";
    Q_ASSERT(isStartElement() && name() == "xmea");

        readNextStartElement();

        if (name() == "entities")
            readEntites();
        readNextStartElement();
        if (name() == "links")
        readLiens();
        //centrer sur les elements

}
void XMeaReader::readField(Entite* lEntite)
{
    qDebug()<<"void XMeaReader::readField(Entite* lEntite)";
    Q_ASSERT(isStartElement() && name() == "property");
    QString nom=attributes().value("fieldname").toString();
    QString type=attributes().value("fieldtype").toString();
    QString taille=attributes().value("fieldsize").toString();
    QString role=attributes().value("fieldrole").toString();
    //creation du champ
    //Property* laPropriete=new Property(mum,true,mum->getScene(),nom,type,role,taille,lEntite);
    //ajout dans les propriétés de l'entité
    mum->tableAjouterChamp(lEntite,nom,type,role,taille);
    skipCurrentElement();
}

void XMeaReader::readFields(Entite* lEntite)
{
    qDebug()<<"void XMeaReader::readFields(Entite* lEntite)";
    Q_ASSERT(isStartElement() && name() == "fields");
    //les champs
    while (readNextStartElement())
    {
        if (name() == "property")
            readField(lEntite);
        else
            return;
    }//fin du while
}

void XMeaReader::readEntite()
{
   qDebug()<<"void XMeaReader::readEntite()";
    Q_ASSERT(isStartElement() && name() == "entity");
    QString nom=attributes().value("name").toString();
    QString left=attributes().value("left").toString();
    QString top=attributes().value("top").toString();
    QString type=attributes().value("type").toString();
    QStringList listeDesChamps;
    bool isAssoc=type==RELATION;
    //creation de l'entite
    if(!isAssoc)
    {
        Entite * lEntite=new Entite(mum,nom,left.toFloat(),top.toFloat(),0,listeDesChamps,isAssoc);
        //peut-être ajout au vecteur de la maman
        mum->ajouteTable(lEntite);
        lEntite->setPos(left.toFloat(),top.toFloat());
        mum->getScene()->addItem(lEntite);
        lEntite->redraw();

        //les champs
        while (readNextStartElement())
        {
            if (name() == "fields")
                readFields(lEntite);
            else
                return;
        }//fin du while

    }
    else
    {
        Association* lEntite=new Association(mum,nom,left.toFloat(),top.toFloat(),0,listeDesChamps,isAssoc);
        //peut-être ajout au vecteur de la maman
        mum->ajouteTable(lEntite);
        lEntite->setPos(left.toFloat(),top.toFloat());
        mum->getScene()->addItem(lEntite);
        lEntite->redraw();

        //les champs
        while (readNextStartElement())
        {
            if (name() == "fields")
                readFields(lEntite);
            else
                return;
        }//fin du while

    }
}

void XMeaReader::readLien()
{
  qDebug()<<"void XMeaReader::readLien()";
  Q_ASSERT(isStartElement() && name() == "link");
  QString nomt1=attributes().value("t1").toString();
  QString nomt2=attributes().value("t2").toString();
  QString nomType=attributes().value("type").toString();
  QString role=attributes().value("role").toString();//vide si l'attribut n'existe pas

  //creation du lien on va chercher les deux entités
  Entite* t1=mum->getEntiteByName(nomt1);
  Entite* t2=mum->getEntiteByName(nomt2);
  //création du lien la chaine vide est normale
  Lien * nouveauLien;
  LienReflexif * nLienReflex;
  if(t1!=t2)
  {
     nouveauLien= new Lien(t2,t1,0,nomType,"",role);
     //on l'ajoute à la scene
     mum->getScene()->addItem(nouveauLien);
     //on ajoute les éléments du groupe
     nouveauLien->ajouteElementsAuGroupe();
  }
  else
  {
     nLienReflex= new LienReflexif(t2,t1,0,nomType,"",role);
     //on l'ajoute à la scene
     mum->getScene()->addItem(nLienReflex);
     //on ajoute les éléments du groupe
     nLienReflex->LienReflexif::ajouteElementsAuGroupe();
  }

  //on passe au suivant
  skipCurrentElement();
}

void XMeaReader::readEntites()
{
    qDebug()<<"void XMeaReader::readEntites()";
    Q_ASSERT(isStartElement() && name() == "entities");

        while (readNextStartElement())
        {
            if (name() == "entity")
                readEntite();
            else
                //skipCurrentElement();
                return;
        }//fin du while
}

void XMeaReader::readLiens()
{
    qDebug()<<"void XMeaReader::readLiens()";
    Q_ASSERT(isStartElement() && name() == "links");

        while (readNextStartElement())
        {
            if (name() == "link")
                readLien();
            else
                return;
        }//fin du while
}

XMeaReader::~XMeaReader()
{

}

