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
#include "qcustomgraphicsscene.h"
#include <QGraphicsItem>
#include <QDrag>
#include <QDebug>
#include "entite.h"
#include "property.h"
#include "types.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QMimeData>
#include <mainwindow.h>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
class MainWindow;

QCustomGraphicsScene::QCustomGraphicsScene(QWidget * parent):QGraphicsScene(parent)
{
 outil="move";
}
void QCustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug("void QCustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)");
    if (mouseEvent->button() == Qt::LeftButton
        && (itemAt(mouseEvent->scenePos(),QTransform())!=NULL))
    {
        //trouver l'objet à la position:

        QGraphicsItem * elt=itemAt(mouseEvent->scenePos(),QTransform());
        elt->setSelected(!elt->isSelected());
        if(elt!=NULL)
        {
            //si c'est une table
            qDebug()<<"youou"<<elt->data(32);
            bool onACliqueSurUneEntiteOuUnChamp=false;
            if(elt->data(32)=="Table")
            {
                if (!qgraphicsitem_cast<Entite*> (elt ))//le titre dit qu'il est une table
                {
                    //mais la table est le parent de son parent
                    elt=(Entite*)elt->parentItem()->parentItem();
                }
                onACliqueSurUneEntiteOuUnChamp=true;

            }
            else//cela peut être un lien ou un field
            {
                if(elt->data(32)=="Field")
                {
                    ((Property*)elt)->emmettreSelected();
                    elt=(Entite*)(((Property*)elt)->lEntite);
                    onACliqueSurUneEntiteOuUnChamp=true;

                }
            }
            //si une table ou le champ d'une table a été sélectionné dans le graphique on chamge la table sélectionnée de la boite liste
            if(elt!=NULL && onACliqueSurUneEntiteOuUnChamp)
            {
                MainWindow * maman=(MainWindow*)parent();
                maman->ui->listWidgetObjects->setCurrentItem((Entite*) elt);
                maman->on_listWidgetObjects_itemActivated((Entite*)elt);
            }
        }
        if(outil=="drag")
        {
            if(!(elt->data(32).toString()=="Field"))
            {
                QDrag *drag = new QDrag(((QWidget*)this->parent()));
                QMimeData *mimeData = new QMimeData;
                QByteArray qba;
                qba.append(elt->data(32).toString());
                qba.append(";");
                qba.append(elt->data(33).toString());
                qba.append(";");
                qba.append(elt->data(34).toString());
                mimeData->setData("text/"+elt->data(32).toString(),qba);
                drag->setMimeData(mimeData);
                //drag->setPixmap(iconPixmap);
                //Qt::DropAction dropAction =
                drag->exec();

            }//fin du si c'est un champ
        }//fin du outil choisi drag
    }
    else//bouton droit
    {
        qDebug()<<"bouton droit";
        if (mouseEvent->button() == Qt::RightButton)
        {   QGraphicsItem * elementConcerne=NULL;
            //si personne à la position de la souris
            if(itemAt(mouseEvent->scenePos(),QTransform())==NULL)
            {
                //et personne dans le rectangle autour
                if(items(QRectF(mouseEvent->scenePos().x()-1,mouseEvent->scenePos().y()-1,2,2)).count()==0)
                {
                    //construction et appel du menu contextuel de la zone de travail
                    QMenu menuContextuelDeRien(QObject::tr("Workspace Menu"));
                    //ajout du titre
                    QAction* titre=new QAction(menuContextuelDeRien.title(),this);
                    titre->setDisabled(true);
                    menuContextuelDeRien.addAction(titre);
                    //titre->setSeparator(true);
                    titre->setFont(QFont("verdana",9,3,true));
                    //ajout des actions du menu:
                    QAction* printModel=menuContextuelDeRien.addAction(tr("Print"));
                    QAction* exportModel=menuContextuelDeRien.addAction(tr("Export to png"));

                    MainWindow* maman=(MainWindow*)parent();
                    QAction * actionChoisie=menuContextuelDeRien.exec(mouseEvent->screenPos());
                    if(actionChoisie==printModel)
                    {
                        //impression
                        maman->statusBar()->showMessage(tr("Printing document"),2000);
                        //tout déselectionner
                        QPrinter printer(QPrinter::HighResolution);
                        QPrintDialog dialog(&printer, maman);
                        if(dialog.exec())
                        {
                          QPainter painter(&printer);
                          this->render(&painter);
                        }
                        else
                        {
                            maman->statusBar()->showMessage(tr("Print canceled"),2000);
                        }
                    }
                    else if(actionChoisie==exportModel)
                    {
                        //exportation au format png
                        maman->statusBar()->showMessage(tr("Exporting document to png"),2000);
                        QString fichierOuvert=maman->getOpenedFileName().replace(".mea",".png");
                        QString nomFichier=QFileDialog::getSaveFileName(maman,tr("Export mea file"),fichierOuvert,tr("Image Files (*.png)"));
                        //sauver dans une image
                        QFileInfo fi(nomFichier);
                        QImage monImage(this->width(),this->height(),QImage::Format_ARGB32_Premultiplied);
                        QPainter monPainter(&monImage);
                        this->render(&monPainter);
                        bool ouvertureReussie=monImage.save(fi.absoluteFilePath());
                        if(ouvertureReussie)
                        {
                            QString message=tr("File was succesfully exported.");
                            maman->statusBar()->showMessage(message,2000);
                        }
                        else
                        {
                            maman->statusBar()->showMessage(tr("Export failed check your filesystem"),2000);
                        }
                    }
                }
                else//qlq chose ds le rectangle
                {
                    elementConcerne=items(QRectF(mouseEvent->scenePos().x()-1,mouseEvent->scenePos().y()-1,2,2))[0];
                }
            }
            else elementConcerne=itemAt(mouseEvent->scenePos(),QTransform());
            if(elementConcerne!=NULL)
            {
                if(elementConcerne->data(32)=="Table")
                {
                    while(!qgraphicsitem_cast<Entite*> (elementConcerne ))
                    {
                        elementConcerne=elementConcerne->parentItem();
                    }
                     //pb sur les assoc
                    ((Entite*)elementConcerne)->contextMenuEvent(mouseEvent);
                }
                else//cela peut être un lien ou un field
                {
                    if(elementConcerne->data(32)=="Field")
                    {

                        ((Property*)elementConcerne)->emmettreSelected();
                        ((Property*)elementConcerne)->contextMenuEvent(mouseEvent);
                    }
                    else //c'est un champ
                    {
                        if(elementConcerne->data(32)=="Lien")
                        {

                            while(!qgraphicsitem_cast<Lien*> (elementConcerne ))
                            {
                                elementConcerne=elementConcerne->parentItem();
                            }
                            //essais de sélection
                            //((Lien*)elementConcerne)->setSelected(!((Lien*)elementConcerne)->isSelected());
                            qDebug()<<"je le sélectionne";
                            ((Lien*)elementConcerne)->setSelected(false);
                            ((Lien*)elementConcerne)->setSelected(true);
                            ((Lien*)elementConcerne)->update();
                            ((Lien*)elementConcerne)->contextMenuEvent(mouseEvent);
                        }

                    }
                }
            }//fin if elementConcerne!=NULL
        }
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

