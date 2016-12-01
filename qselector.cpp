#include "qselector.h"
#include <QDebug>
#include <QCheckBox>
#include <QComboBox>
#include <QModelIndexList>


QSelector::QSelector(QWidget* parent): QTableWidget(parent)
{

}
void QSelector::dragEnterEvent(QDragEnterEvent *event)
 {
    qDebug("void QSelector::dragEnterEvent(QDragEnterEvent *event)");
    qDebug()<<event->mimeData()->text();
     if (event->mimeData()->hasFormat("text/plain"))
         event->accept();
     else
         event->ignore();
 }

 void QSelector::dragMoveEvent(QDragMoveEvent *event)
 {
     if (event->mimeData()->hasFormat("text/plain")) {
         event->setDropAction(Qt::MoveAction);
         event->accept();
     } else
         event->ignore();
 }

 void QSelector::dropEvent(QDropEvent *event)
 {
     if (event->mimeData()->hasFormat("text/plain")) {
         QString data=event->mimeData()->text();
         QStringList typeEtNom=data.split(';');
         //si une colonne est sélectionnée remplacement sinon ajout
         int noColonne;
         if(!this->selectedItems().empty())
         {
             noColonne=this->column(this->selectedItems()[0])+1;
         }
         else
         {
         //ajout de la colonne
         this->setColumnCount(this->columnCount()+1);
         noColonne=this->columnCount();

       }
         QString intitule=typeEtNom[1];
         if(typeEtNom[0]=="Table")
         {
             //affichage du nom de la table
             this->setItem(1,noColonne-1,new QTableWidgetItem(intitule));
             intitule="*";
         }
         else
         {
             if(!(intitule==""))
             {
             //table et nom de champ sont séparés par un .
             QStringList qsl=intitule.split('.');
             this->setItem(1,noColonne-1,new QTableWidgetItem(qsl[0]));
             intitule=qsl[1];
            }
             else
             {
                 //ajout d'un champ hors table
             }
         }
          QTableWidgetItem *newItem = new QTableWidgetItem(intitule);
          //fieldname
           setItem( 0,noColonne-1, newItem);
           //affiché ou non
           setCellWidget(2,noColonne-1,new QCheckBox("display",this));
           //tri
           QComboBox* comboSort=new QComboBox(this);
           comboSort->addItem("");
           comboSort->addItem("asc");
           comboSort->addItem("desc");
           setCellWidget(4,noColonne-1,comboSort);
           //fonctions de groupe
           QComboBox* comboCalc=new QComboBox(this);
           comboCalc->addItem("");
           comboCalc->addItem("SUM");
           comboCalc->addItem("MIN");
           comboCalc->addItem("MAX");
           comboCalc->addItem("AVG");
           setCellWidget(6,noColonne-1,comboCalc);
         event->setDropAction(Qt::MoveAction);
         event->accept();
     } else
         event->ignore();
 }
