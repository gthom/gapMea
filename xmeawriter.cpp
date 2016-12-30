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
#include "xmeawriter.h"
#include <QDebug>

XMeaWriter::XMeaWriter(MainWindow* maman)
{
  mum=maman;
}

XMeaWriter::~XMeaWriter()
{

}

bool XMeaWriter::writeFile(QIODevice *device)
{
    qDebug()<<"bool XMeaWriter::writeFile(QIODevice *device)";
    setDevice(device);
    writeStartDocument();
    writeDTD("<!DOCTYPE xmea PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://gthom.btsinfogap.org/gapMea/dtd/mea.dtd\">");
    writeStartElement("xmea");
    writeAttribute("version", "1.0");
    //creation des entites
    writeEntites();
    //creation des liens
    writeLiens();
    //fin du doc
    writeEndDocument();
    return true;
}

void XMeaWriter::writeEntite(Entite * lEntite)
{
    qDebug()<<"void XMeaWriter::writeEntite(Entite * lEntite)"<<endl;
    writeStartElement("entity");
    writeAttribute("name",lEntite->nomEntite);
    writeAttribute("left",QString::number(lEntite->x()));
    writeAttribute("top",QString::number(lEntite->y()));
    QString type;
    if(lEntite->association)
    {
        type=RELATION;
    }
    else type=ENTITY;
    writeAttribute("type",type);
    //les champs
    writeStartElement("fields");
    //boucle sur les champs
    foreach (Property* laPropriete, lEntite->vecteurChamps) {
        writeStartElement("property");
        writeAttribute("fieldname",laPropriete->nom);
        writeAttribute("fieldtype",laPropriete->sonType);
        writeAttribute("fieldsize",laPropriete->taille);
        writeAttribute("fieldrole",laPropriete->role);
        //fin de la propriété
        writeEndElement();
    }
    writeEndElement();
    //fin des champs
    //fin de l'entité
    writeEndElement();
}
void XMeaWriter::writeEntites()
{
    qDebug()<<"void XMeaWriter::writeEntites()"<<endl;
    writeStartElement("entities");
    QVector<Entite*> vectE=mum->vectTable;
    foreach(Entite* lEntite,vectE)
    {
        writeEntite(lEntite);
    }
    writeEndElement();
}
void XMeaWriter::writeLien(Lien * leLien)
{
    qDebug()<<"void XMeaWriter::writeLien(Lien * leLien)"<<endl;
    writeStartElement("link");
    writeAttribute("t1",leLien->t1->nomEntite);
    writeAttribute("t2",leLien->t2->nomEntite);
    writeAttribute("type",leLien->typeDeJointure);
    writeAttribute("card1",leLien->cardinalite1->text());
    if(leLien->cardinalite2!=NULL)
    {
      writeAttribute("card2",leLien->cardinalite2->text());
    }
    if(leLien->role!=NULL)
    {
        writeAttribute("role",leLien->role->text());
    }//bug corrigé remplace leLien->role->text() car il y a des liens sans role
    //on termine le lien
    writeEndElement();
}
void XMeaWriter::writeLiens()
{
    qDebug()<<"void XMeaWriter::writeLiens()"<<endl;
    writeStartElement("links");
    QVector<Lien*> vectL=mum->vectLiens;
    foreach(Lien* leLien,vectL)
    {
        writeLien(leLien);
    }
    writeEndElement();
}
