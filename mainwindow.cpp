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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsTextItem>
#include <QWidget>
#include <QDebug>
#include "entite.h"
#include "property.h"
#include <QString>
#include <QMessageBox>
#include "dialogtypejointure.h"
#include "ui_dialogtypejointure.h"
#include <QDir>
#include <QFileDialog>
#include <QDesktopServices>
#include <QFontDatabase>
#include "xmeawriter.h"
#include "xmeareader.h"
#include "dialogaboutme.h"
#include "lienreflexif.h"
#include <QInputDialog>
/**
 * @brief MainWindow::MainWindow
 * @param parent
 * le constructeur
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFontDatabase::addApplicationFont(":/fonts/verdana.ttf");
    QFontDatabase::addApplicationFont(":/fonts/DejaVuSerif.ttf");  
    setFont(QFont("Sans Serif",9));
    setDockNestingEnabled(true);
    maScene=new QCustomGraphicsScene(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setScene(maScene);
    prochainX=30;
    //agrandissement de la dernière colonne de tableWidgetProperties
    ui->tableWidgetProperties->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidgetProperties->horizontalHeader()->setStretchLastSection(true);
    //placement des dockwidgets
    ui->dockWidgetProperties->setFloating(false);
    ui->dockWidgetObjects->setFloating(false);
    //on donne le focus au lineEdit
    ui->lineEditObjectName->setFocus();
    ui->textEditSql->setVisible(false);

    QPalette palette;
    QColor couleurFond(Qt::lightGray);
    QColor couleurTexte(Qt::black);

    palette.setColor(QPalette::Base,couleurFond);
    palette.setColor(QPalette::Text,couleurTexte);
    ui->textEditSql->setPalette(palette);
    //connexion des signaux aux slots
     connect (ui->graphicsView,SIGNAL(jointureRequise(Entite*,Entite*)),this,SLOT(jointure(Entite*,Entite*)));
     connect(ui->pushButtonModifyProperty,SIGNAL(clicked()),this,SLOT(on_pushButtonModifyProperty_clicked()));
     connect(ui->lineEditPropertyName,SIGNAL(textChanged(QString)),this,SLOT(activeDesactiveBoutonApply()));
     connect(ui->lineEditPropertyRole,SIGNAL(textChanged(QString)),this,SLOT(activeDesactiveBoutonApply()));
     connect(ui->lineEditTaille,SIGNAL(textChanged(QString)),this,SLOT(activeDesactiveBoutonApply()));
      connect(ui->comboBoxPropertyType,SIGNAL(currentTextChanged(QString)),this,SLOT(activeDesactiveBoutonApply()));
      connect(ui->comboBoxPropertyType,SIGNAL(currentTextChanged(QString)),this,SLOT(activeDesactiveInputTaille()));
     setFileName(tr("New_Model.mea"));
     setSaved(true);
     ui->statusBar->showMessage(tr("Welcome in database design World"));
}
void MainWindow::effaceTout()
{
    qDebug()<<"void MainWindow::effaceTout()";
    //effacement des entités
     foreach (Entite* lEntite, vectTable)
     {
         //supression sans demander confirmation
         tableSupprimer(lEntite,false);
     }
     //raz de la tableWidget des propriétés
     if(ui->tableWidgetProperties->rowCount()>0) ui->tableWidgetProperties->setRowCount(0);
     //raz du formulaire de modif des propriétés
     maScene->clear();
     maScene->views()[0]->repaint();
}

MainWindow::~MainWindow()
{  
   //effacement des entités
   effaceTout();
   delete ui;
}

void MainWindow::on_action_quitter_triggered()
{
    close();
}
/**
 * @brief MainWindow::closeEvent
 * @param event
 * surcharge du closeEvent pour ne fermer que lorsque l'utilisateur confirme vouloir quitter l'application
 */
void MainWindow::closeEvent(QCloseEvent* event)
{
    if(saved && QMessageBox::question(this,this->windowTitle(),tr("Do you really want to quit gapMea?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        event->accept();
    else
    {
        if (!saved && QMessageBox::question(this,this->windowTitle(),tr("Your work is not saved, Are you sure ?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        event->accept();
        else
        event->ignore();
    }
}

void MainWindow::on_action_Add_Entity_triggered()
{
    qDebug()<<"void MainWindow::on_action_Add_Entity_triggered()";
    QStringList listeDesChamps;
    listeDesChamps<<"numero"<<"libelle";
    QString nomTable=ui->lineEditObjectName->text();
    Entite* tableAjoutee=new Entite(this,nomTable,0,0,0,listeDesChamps,false);
    tableAjoutee->setPos(QPoint (prochainX,30));
    ajouteTable(tableAjoutee);
   maScene->addItem(tableAjoutee);
   //j'efface la zone de saisie
   ui->lineEditObjectName->clear();
   tableAjoutee->redraw();
   setSaved(false);
}
void MainWindow::ajouteTable(Entite * lEntite)
{
    qDebug()<<"void MainWindow::ajouteTable(Entite * lEntite)"<<endl;
    vectTable.append(lEntite);
    ui->listWidgetObjects->addItem(lEntite);
    prochainX=lEntite->pos().x()+lEntite->boundingRect().width()+10;
    lEntite->setFlag(QGraphicsItem::ItemIsSelectable);
    lEntite->setFlag(QGraphicsItem::ItemIsMovable);
    setSaved(false);
}

void MainWindow::tableAjouterChamp(Entite * lEntite,QString nomDuChamp,QString typeDuChamp, QString roleDuChamp,QString tailleDuChamp)
{
    //but:Ajouter une propriété à l'entité
   qDebug()<<"void MainWindow::tableAjouterChamp()";

    Property* nouveauChamp=new Property(this,nomDuChamp,typeDuChamp,roleDuChamp,tailleDuChamp,lEntite);
    //les données du champ
    nouveauChamp->setData(32,"Field");
    nouveauChamp->setData(33,lEntite->nomEntite+"."+nomDuChamp);
    //ajout du nouveau champ au vecteur des champs de l'entité
    lEntite->vecteurChamps.append(nouveauChamp);
    lEntite->redraw();
    setSaved(false);
    //selection dans la liste des objets pour mettre à jour les propriétés de celui-ci
    on_listWidgetObjects_itemActivated(lEntite);
}

void MainWindow::setFileName(QString fn)
{
    fileName=fn;
    setWindowTitle("GapMea "+fileName);
}
void MainWindow::selectionne(Entite* lEntite)
{
    qDebug()<<"void MainWindow::selectionne(Entite* lEntite)"<<endl;
    //selection dans la liste des objets
    ui->listWidgetObjects->setCurrentItem(lEntite);
    //on fait comme si l'utilisateur l'avait sélectionné à la main dans la liste
    on_listWidgetObjects_itemActivated(lEntite);
}

void MainWindow::selectionne(Property * laPropriete)
{
    qDebug("void MainWindow::selectionne(Property * laPropriete)");
    selectionne(laPropriete->lEntite);
    ui->tableWidgetProperties->selectRow(laPropriete->lEntite->vecteurChamps.indexOf(laPropriete));
    //desactivation du bouton modifier
    ui->pushButtonModifyProperty->setEnabled(false);
}

void MainWindow::editProperty(Property* laPropriete)
{
   ui->lineEditPropertyName->setText(laPropriete->nom);
   ui->lineEditPropertyRole->setText(laPropriete->role);
   ui->lineEditTaille->setText(laPropriete->taille);
   ui->comboBoxPropertyType->setCurrentText(laPropriete->sonType);
   ui->lineEditPropertyName->setFocus();
}

void MainWindow::on_pushButtonAddObject_clicked()
{
    //ajout de l'objet à la liste
    QString leNom=ui->lineEditObjectName->text();
    //s'il n'est pas vide et qu'il n'existe pas déjà
    if(leNom!="" && !ui->listWidgetObjects->findItems(leNom,Qt::MatchExactly).count()>0 )
    {
        on_action_Add_Entity_triggered();
        setSaved(false);
    }
    else
    {
        statusBar()->showMessage(tr("Sorry but Object already exists"),2000);
    }
}
/**
 * @brief MainWindow::on_action_Object_list_triggered
 * @param checked
 * appui sur le bouton voir la liste des objets
 * cache ou montre le dockwidget liste des objets
 */
void MainWindow::on_action_Object_list_triggered(bool checked)
{
    if(checked)
    {
        ui->dockWidgetObjects->show();
    }
    else
    {
        ui->dockWidgetObjects->hide();
    }
}

/**
 * @brief MainWindow::on_listWidgetObjects_itemActivated
 * @param item
 * Sélection d'un objet dans la liste
 * On affiche ses propriétés dans la tableWidget
 */
void MainWindow::on_listWidgetObjects_itemActivated(QListWidgetItem *item)
{
    Entite* lEntite=(Entite*)item;
    //affichage du nom de l'entité dans le titre de la groupBoxProperties
    ui->groupBoxProperties->setTitle(lEntite->nomEntite+'-'+tr("Properties"));
    //recup et affichage des propriétés de l'entité
    QVector<Property*>vectChamps=lEntite->vecteurChamps;
    ui->tableWidgetProperties->setRowCount(vectChamps.size());
    //affichage dans la table des champs de l'entité
    for(int no=0;no<vectChamps.size();no++)
    {
        ui->tableWidgetProperties->setItem(no,0,new QTableWidgetItem(vectChamps[no]->getNomComplet()));
        ui->tableWidgetProperties->setItem(no,1,new QTableWidgetItem(vectChamps[no]->sonType));
        ui->tableWidgetProperties->setItem(no,2,new QTableWidgetItem(vectChamps[no]->taille));
        ui->tableWidgetProperties->setItem(no,3,new QTableWidgetItem(vectChamps[no]->role));
    }
    //met à jour la zone de modif des propriétés
    on_tableWidgetProperties_itemSelectionChanged();
    //essais de selection dans la view
    ((QGraphicsItem*)lEntite)->setSelected(true);
}
void MainWindow::on_pushButtonModifyProperty_clicked()
{
    //click sur apply
    int index=ui->tableWidgetProperties->currentRow();
    if(index!=-1)
    {
         Property* laPropriete=((Entite*)ui->listWidgetObjects->currentItem())->vecteurChamps[index];
         //on récupère les informations saisies
         laPropriete->nom=ui->lineEditPropertyName->text();
         laPropriete->sonType=ui->comboBoxPropertyType->currentText();
         laPropriete->role=ui->lineEditPropertyRole->text();
         laPropriete->taille=ui->lineEditTaille->text();
         //on fait comme si on avait cliqué sur l'entité de façon à  actualiser l'affichage
         on_listWidgetObjects_itemActivated(laPropriete->lEntite);
         //on redessine l'entité
         laPropriete->lEntite->redraw();
         //désactivation du bouton modifier
         ui->pushButtonModifyProperty->setEnabled(false);
         setSaved(false);
    }
    else
    {
        statusBar()->showMessage(tr("Please select an object first"),2000);
    }
}

void MainWindow::on_pushButtonAddProperty_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonAddProperty_clicked()"<<endl;
    //ajout de propriété à l'entité en cours d'édition
    //s'il y a une entité sélectionnée
    if(ui->listWidgetObjects->selectedItems().count()==1)
    {
         Entite* lEntite=(Entite*)(ui->listWidgetObjects->selectedItems()).at(0);
         //on récupère les informations saisies
         QString nomDuChamp=ui->lineEditPropertyName->text();
         QString typeDuChamp=ui->comboBoxPropertyType->currentText();
         QString roleDuChamp=ui->lineEditPropertyRole->text();
         QString tailleDuChamp=ui->lineEditTaille->text();
         tableAjouterChamp(lEntite,nomDuChamp,typeDuChamp,roleDuChamp,tailleDuChamp);
         //ajout dans la grille
         int nbChamp=lEntite->vecteurChamps.size();
         ui->tableWidgetProperties->setRowCount(nbChamp);
         ui->tableWidgetProperties->setItem(nbChamp-1,0,new QTableWidgetItem(nomDuChamp));
          ui->tableWidgetProperties->setItem(nbChamp-1,1,new QTableWidgetItem(typeDuChamp));
           ui->tableWidgetProperties->setItem(nbChamp-1,2,new QTableWidgetItem(tailleDuChamp));
           ui->tableWidgetProperties->setItem(nbChamp-1,3,new QTableWidgetItem(roleDuChamp));
           //puis on efface les zones de saisie
           ui->lineEditPropertyName->clear();
           ui->lineEditPropertyRole->clear();
           //ui->comboBoxPropertyType->clear();
           //desactivation du bouton ajouter

           setSaved(false);
    }
    else
    {
        statusBar()->showMessage(tr("Please select an object first"),2000);
    }
}

void MainWindow::on_tableWidgetProperties_cellChanged(int row, int column)
{
    qDebug()<<"void MainWindow::on_tableWidgetProperties_cellChanged(int row, int column)";
    //modification du nom du type ou du role du champ
    if(ui->listWidgetObjects->selectedItems().count()==1)
    {
        Entite* lEntite=(Entite*)(ui->listWidgetObjects->selectedItems()).at(0);
        Property * laPropriete=lEntite->vecteurChamps.at(row);
        QString nouvelleValeur=ui->tableWidgetProperties->item(row,column)->text();

        switch(column)
        {
          case 0:

             laPropriete->nom=nouvelleValeur;
             break;
        case 1:
            laPropriete->sonType=nouvelleValeur;
            break;
        case 2:
            laPropriete->taille=nouvelleValeur;
            break;
        case 3:
            laPropriete->role=nouvelleValeur;
            break;
        }
        lEntite->redraw();
        setSaved(false);
    }
    else statusBar()->showMessage(tr("Select an object first"),2000);
}
void MainWindow::tableSupprimer(Entite* laTableASupprimer,bool demanderConfirmation)
{
    qDebug()<<"void MainWindow::tableSupprimer(Entite* laTableASupprimer)";
    if(demanderConfirmation && QMessageBox::question(this,this->windowTitle(),tr("Do you confirm deleting Object:")+laTableASupprimer->nomEntite,QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        int no=vectTable.indexOf(laTableASupprimer);
        vectTable.remove(no,1);
        //enlever de la liste
        ui->listWidgetObjects->takeItem(no);
        //enlever de la scene
        ui->graphicsView->scene()->removeItem(laTableASupprimer);
        delete laTableASupprimer;

        setSaved(false);
    }
    else//soit sans confirm soit il a confirmé la supression
    {
        //si c'est une supression sans confirmation
        if(!demanderConfirmation)
        {
            int no=vectTable.indexOf(laTableASupprimer);
            vectTable.remove(no,1);
            //enlever de la liste
            ui->listWidgetObjects->takeItem(no);
            //enlever de la scene
            ui->graphicsView->scene()->removeItem(laTableASupprimer);
            delete laTableASupprimer;
            setSaved(false);
        }
    }
}

void MainWindow::on_lineEditObjectName_textChanged(const QString &arg1)
{
    //activation/desactivation du bouton add
    QString nettoyee=arg1;
    nettoyee.remove('`');//supression des caractères dangereux
    nettoyee.remove(' ');//supression des espaces
    if(arg1.contains('`')||arg1.contains(' ')) ui->lineEditObjectName->setText(nettoyee);
    ui->pushButtonAddObject->setEnabled(!nettoyee.isEmpty());
}

void MainWindow::on_actionMove_triggered()
{
    qDebug()<<"void dialogRelation::on_toolButtonMove_clicked()";
    //Choix de l'outil move
    maScene->outil="move";
    ui->graphicsView->setCursor(QCursor(Qt::ArrowCursor));
    ui->actionLink->setEnabled(true);
    ui->actionMove->setEnabled(false);
}

void MainWindow::on_actionLink_triggered()
{
    qDebug()<<"void dialogRelation::on_toolButtonJoin_clicked()";
    //choix de l'outil drag
    maScene->outil="drag";
    ui->graphicsView->setCursor(QCursor(Qt::PointingHandCursor));
    ui->actionLink->setEnabled(false);
    ui->actionMove->setEnabled(true);
}
void MainWindow::jointure(Entite* t1,Entite* t2)
{
    qDebug()<<"void MainWindow::jointure(Entite* t1,Entite* t2)";
    //j'affiche une boite de dialogue pour saisir le type de jointure
    DialogTypeJointure dtj;
    //si t1=t2 df ou assoc enlever la CIF la patte et l'entité faible
    if(t1==t2)
    {
        dtj.m_ui->comboBoxType->removeItem(0);//cif
        dtj.m_ui->comboBoxType->removeItem(1);//leg
        dtj.m_ui->comboBoxType->removeItem(1);//leak relation
    }
    //puis je trouve les deux tables dans le vecteur et ajoute le lien dans la table des liens
    if(dtj.exec())
    {
        QString typ=dtj.m_ui->comboBoxType->currentText();
        //reprise de l'anglais au moins pour les pattes
        if(typ==QObject::tr(LEG)) typ=LEG;
        if(typ==QObject::tr(LEAKRELATION)) typ=LEAKRELATION;
        if(typ==QObject::tr(RELATION)) typ=RELATION;
        QString relationName=dtj.m_ui->lineEditRelationName->text();
        if(t1!=t2 || typ==RELATION)
        {         
            Lien * nouveauLien=new Lien(t1,t2,0,typ,relationName);
            maScene->addItem(nouveauLien);
            //on ajoute les éléments du groupe
            nouveauLien->ajouteElementsAuGroupe();
        }
        else//t1=t2 et df reflexive
        {
            //reflexive donc attention a ne pas ajouter deux fois le lien
            //demander le role
            QString leRole="";
            LienReflexif * nouveauLien=new LienReflexif(t1,t2,0,typ,relationName,leRole);
            maScene->addItem(nouveauLien);
            //on ajoute les éléments du groupe
            nouveauLien->LienReflexif::ajouteElementsAuGroupe();
        }
        //on a modifié le modèle
        setSaved(false);
    }
}


void MainWindow::supprimerLien(Lien * leLien)
{
    qDebug()<<"void MainWindow::supprimerLien(lien * leLien)";
    if(leLien==NULL) return;
    //effacement du lien dans le vecteur central de la mainWindow:
    int index=vectLiens.indexOf(leLien);
    if(index!=-1)
    {
      leLien->t1->vectLiens.remove(leLien->t1->vectLiens.indexOf(leLien));
      //version qt supérieure: leLien->t1->vectLiens.removeOne(leLien);
      if(leLien->t1 != leLien->t2) leLien->t2->vectLiens.remove(leLien->t2->vectLiens.indexOf(leLien));
    }
    index=vectLiens.indexOf(leLien);
    if(index!=-1) vectLiens.remove(index);
    if(leLien!=NULL) delete leLien;
    leLien=NULL;
    //on a modifié le modèle
    setSaved(false);
}

void MainWindow::on_actionSave_triggered()
{
    QString fichierOuvert=fileName;
    QString nomFichier=QFileDialog::getSaveFileName(this,tr("Save xmea file"),fichierOuvert,tr("MEA Files (*.mea *.xml)"));
    //sauver dans un fichier xml
    QFile monFichierXMea(nomFichier);
    QFileInfo fi(nomFichier);
    bool ouvertureReussie=monFichierXMea.open(QIODevice::WriteOnly);
    if(ouvertureReussie)
    {
        XMeaWriter* monWriter=new XMeaWriter(this);
        QString message=tr("Error occured saving file");
        if(monWriter->writeFile(&monFichierXMea))
        {
            message=tr("File was succesfully saved.");
            setSaved(true);
            setFileName(fi.fileName());
        }
        statusBar()->showMessage(message,2000);
        delete monWriter;
    }
    else
    {
        statusBar()->showMessage(tr("Saving is aborted"),2000);
    }
}

void MainWindow::on_action_Open_triggered()
{
    //ouverture d'un fichier xml

         QString fileName =
                 QFileDialog::getOpenFileName(this, tr("Open MEA File"),
                                              QDir::currentPath(),
                                         tr("MEA Files (*.mea *.xml)"));
         QFileInfo fi(fileName) ;
         if (fileName.isEmpty())
             return;

         QFile file(fileName);
         if (!file.open(QFile::ReadOnly | QFile::Text)) {
             QMessageBox::warning(this, "GAP MEA",
                                  tr("Cannot read file %1:\n%2.")
                                  .arg(fileName)
                                  .arg(file.errorString()));
             return;
         }
         XMeaReader* monMeaReader=new XMeaReader(this);
         if (monMeaReader->readFile(&file))
         {
             statusBar()->showMessage(tr("File loaded"), 2000);
             setSaved(true);
             setFileName(fi.fileName());
             //vider le sql
             ui->textEditSql->clear();
             //effacement de la zone du sql
             ui->textEditSql->setVisible(false);
             ui->action_sql->setChecked(false);
             //centrer sur les éléments de la scene
             ui->graphicsView->centerOn(ui->graphicsView->scene()->itemsBoundingRect().center());
             ui->graphicsView->ensureVisible(ui->graphicsView->scene()->itemsBoundingRect());
             ui->lineEditPropertyName->clear();
             ui->lineEditPropertyRole->clear();
             ui->lineEditTaille->clear();
         }
         else
             statusBar()->showMessage(tr("Error reading File"), 2000);
         delete monMeaReader;//liberation
}

void MainWindow::on_actionZoom_Best_triggered()
{
  ui->graphicsView->fitInView(ui->graphicsView->scene()->itemsBoundingRect(),Qt::KeepAspectRatio);
}


void MainWindow::on_actionZoom_2_triggered()
{
    ui->graphicsView->zoomOut();
}

void MainWindow::on_actionZoom_triggered()
{
     ui->graphicsView->zoomIn();
}

void MainWindow::on_action_sql_triggered(bool checked)
{
    QVector <Entite*> entitesAProbleme;
    ui->textEditSql->setVisible(checked);
    ui->action_sql->setChecked(checked);
    if(checked)
    {
        ui->textEditSql->clear();
        QVector<Entite*>entitesGeneres;
        int nbDEntites=vectTable.count();
        int nbEGDsLeTour=180;
        while(!(entitesGeneres.count()==nbDEntites || nbEGDsLeTour==0))
        {
            nbEGDsLeTour=0;
            foreach(Entite* lEntite ,vectTable)
            {
                if(lEntite->canBeWriten(entitesGeneres))
                {
                    if(!entitesGeneres.contains(lEntite))
                    {
                        ui->textEditSql->append(lEntite->toSql());
                        //plus une ligne vide
                        ui->textEditSql->append("");
                        entitesGeneres.append(lEntite);
                        nbEGDsLeTour++;
                    }
                }
            }
        }
        if(!(entitesGeneres.count()==nbDEntites))
        {
            statusBar()->showMessage(tr("Loop was detected please correct problem first"));
            //demander à l'utilisateur s'il veut tout de même créer le modèle
            QMessageBox msg;
            msg.setText(tr("A loop as been detected while trying to generate SQL"));
            msg.setInformativeText(tr("Your model may contain error\r\n You can try to correct problem or to force generation\r\nDo you want to force SQL generation?"));
            msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msg.setDefaultButton(QMessageBox::No);
            int ret=msg.exec();
            if(ret==QMessageBox::Yes)
            {
                //generation des tables(sans fk) puis des alter pour les foreign keys
                foreach(Entite* lEntite ,vectTable)
                {

                    if(!entitesGeneres.contains(lEntite))
                    {
                        entitesAProbleme.push_back(lEntite);
                        ui->textEditSql->append(lEntite->toSql(true));
                        //plus une ligne vide
                        ui->textEditSql->append("");
                        entitesGeneres.append(lEntite);

                    }
                }//fin fdu foreach
                //on reprend les entités à problème
                foreach(Entite* lEntite, entitesAProbleme)
                {
                    QStringList lesClefsEtrangeres=lEntite->renvoieClefsEtrangeres(false);
                    foreach (QString laClef, lesClefsEtrangeres) {
                        ui->textEditSql->append(laClef);
                    }
                }
            }//fin du il veut forcer

        }//fin du il ya eu un pb de generation
        else//c'est ok
        {
            statusBar()->showMessage(tr("SQL was successfully generated."));
        }
        //réglage des proportions du splitter
        ui->splitterMeaSql->setStretchFactor(0,3);
        ui->splitterMeaSql->setStretchFactor(1,0);
    }//fin du if checked
}


Entite *MainWindow::getEntiteByName(QString nom)
{
    qDebug()<<"Entite *MainWindow::getEntiteByName(QString nom)"<<endl;
    int no=0;
    while(!(no==vectTable.size()|| vectTable.at(no)->nomEntite==nom))
    {
        no++;
    }
    if(no!=vectTable.size())
    {
        return vectTable.at(no);
    }
    else
    return NULL;
}



void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action_About_triggered()
{
    DialogAboutMe aboutMe;
    aboutMe.exec();
}



void MainWindow::on_action_Properties_triggered(bool checked)
{
    ui->dockWidgetProperties->setVisible(checked);
}

void MainWindow::setSaved(bool ok)
{
    saved=ok;
    ui->actionSave->setEnabled(!ok);
}

void MainWindow::on_tableWidgetProperties_itemSelectionChanged()
{
    qDebug()<<"void MainWindow::on_tableWidgetProperties_itemSelectionChanged()";
    //si la selection n'est pas vide
    int numeroDeLigne=ui->tableWidgetProperties->currentRow();
    if(numeroDeLigne!=-1)
    {
        if(ui->listWidgetObjects->currentItem()!=NULL)
        {
            editProperty(((Entite*)ui->listWidgetObjects->currentItem())->vecteurChamps[numeroDeLigne]);
        }
    }
}

void MainWindow::on_actionNew_Document_triggered()
{
    //regarder s'il faut sauver
    if (!saved)
    {
        if(QMessageBox::question(this,this->windowTitle(),tr("Your work is not saved, do you want to save it before ?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        {
            on_actionSave_triggered();
        }
    }
    //nouveau document
    effaceTout();
    setFileName(tr("New_Model.mea"));
    setSaved(true);
    //vider le sql
    ui->textEditSql->clear();
    //le rendre invisible
    on_action_sql_triggered(false);
    ui->lineEditPropertyName->clear();
    ui->lineEditPropertyRole->clear();
    ui->lineEditTaille->clear();
}

void MainWindow::activeDesactiveBoutonApply()
{
  qDebug()<<"void MainWindow::activeDesactiveBoutonApply()";
  bool activerApply,activerAdd;
  //comparaison entre ce qu'il y a dans la table et ce qu'il ya dans le formulaire
  int noLigne=ui->tableWidgetProperties->currentRow();
  if(noLigne!=-1)//s'il y a une propriété sélectionnée
  {
      bool nomDif=ui->tableWidgetProperties->item(noLigne,0)->text()!=ui->lineEditPropertyName->text();
      bool typeDif=ui->tableWidgetProperties->item(noLigne,1)->text()!=ui->comboBoxPropertyType->currentText();
      bool tailleDif=ui->tableWidgetProperties->item(noLigne,2)->text()!=ui->lineEditTaille->text();
      bool roleDif=ui->tableWidgetProperties->item(noLigne,3)->text()!=ui->lineEditPropertyRole->text();
      activerApply=(!ui->lineEditPropertyName->text().isEmpty())&&(nomDif||typeDif||tailleDif||roleDif);
  }
  else activerApply=false;//pas de modification de propriété possible
  activerAdd=ui->listWidgetObjects->currentRow()!=-1;
  for(int noL=0;noL<ui->tableWidgetProperties->rowCount();noL++)
  {
      qDebug()<<ui->tableWidgetProperties->item(noL,0)->text();
      if(ui->tableWidgetProperties->item(noL,0)->text()==ui->lineEditPropertyName->text())
      {
          activerAdd=false;
      }
  }

  ui->pushButtonModifyProperty->setEnabled(activerApply);
  ui->pushButtonAddProperty->setEnabled(ui->lineEditPropertyName->text()!=""&& activerAdd);
}
void MainWindow::activeDesactiveInputTaille()
{
    qDebug()<<"void MainWindow::activeDesactiveInputTaille()"<<endl;
    QString typ=ui->comboBoxPropertyType->currentText();
    bool active= typ=="VARCHAR"|| typ=="NUMERIC" ||typ=="SET" || typ== "ENUM";
    ui->lineEditTaille->setEnabled(active);
    if(!(active)) ui->lineEditTaille->setText("");//on vide l'input taille
}

void MainWindow::on_listWidgetObjects_itemSelectionChanged()
{
    ui->pushButtonAddProperty->setEnabled(ui->listWidgetObjects->selectedItems().count()==1);
}

void MainWindow::on_lineEditPropertyName_textChanged(const QString &arg1)
{
    QString nettoyee=arg1;
    nettoyee.replace('`',"");
    nettoyee.replace('<',"");
    nettoyee.replace('>',"");
    nettoyee.replace(' ',"_");
    if(arg1.contains('`')||arg1.contains('<')||arg1.contains('>')||arg1.contains(' '))ui->lineEditPropertyName->setText(nettoyee);
    activeDesactiveBoutonApply();
}
void MainWindow::renameEntity(Entite* lEntite)
{
    if(lEntite!=NULL)
    {
        bool ok;
        QString nouveauNom = QInputDialog::getText(this, tr("Rename Object"),
                                             tr("Object name:"), QLineEdit::Normal,
                                             lEntite->getNomEntite(), &ok);
        if (ok && !nouveauNom.isEmpty()&& !ui->listWidgetObjects->findItems(nouveauNom,Qt::MatchCaseSensitive).count()>0)
        {
            //contrôler la validité du nouveau nom

            QString ancienNom=lEntite->getNomEntite();
            qDebug()<<"entite renommée";
            lEntite->setNomEntite(nouveauNom);
            //rafaraichissement de la liste des entités
            ui->listWidgetObjects->findItems(ancienNom,Qt::MatchCaseSensitive).at(0)->setText(nouveauNom);
        }

        else//affichage d'un message d'erreur
        {
            QString error1=tr("Error object name cannot be empty");
            QString error2=tr("Object with this name already exists");
            QString error=error2;
            if(nouveauNom.isEmpty()) error=error1;
            QMessageBox::warning(this,tr("Rename Object"),error,QMessageBox::Ok,QMessageBox::Ok);
        }

    }
}
