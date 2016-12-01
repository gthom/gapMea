#include "property.h"
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QTextDocument>
#include "ui_mainwindow.h"

Property::Property(MainWindow* mum,QString pName,QString pType, QString pRole,QString pTaille,QGraphicsItem* pParent)
    :QGraphicsTextItem(pName,pParent),nom(pName), sonType(pType), role(pRole), taille(pTaille)
{
    qDebug()<<"constructeur de Property";
    maman=mum;
    lEntite=(Entite*)pParent;
    setAcceptDrops(true);
    //setFlag(QGraphicsItem::ItemIsSelectable,true);
    connect(this,SIGNAL(jeSuisSelectionne(Property*)),maman,SLOT(selectionne(Property*)));

}
Property::~Property()
{


}
void Property::contextMenuEvent(QGraphicsSceneMouseEvent *event)
{
    //ce qui se passe lorsque le menu contextuel du champ est appelé
    qDebug()<<"void Property::contextMenuEvent(QGraphicsSceneMouseEvent *event)";
    //sélection de l'objet
    setSelected(true);
    maman->selectionne(lEntite);
    //création du menu cntextuel du champ
    QMenu menu(QObject::tr("Property's Menu"));
    //titre du menu contextuel
    QAction* titre=new QAction(menu.title(),this);
    titre->setDisabled(true);
    menu.addAction(titre);
    titre->setFont(QFont("verdana",9,3,true));
    //si je n'était pas sélectionné, je le deviens
    this->setSelected(!this->isSelected());
    //création des actions du menu
    QAction *removeAction ;
    removeAction = menu.addAction(tr("&Remove"));
    //non ajoutée au menu contextuel
    QAction *editAction = menu.addAction(QIcon(":/mini-eye.xpm"),tr("&Edit"));
    //exécution du menu
    QAction* actionChoisie=menu.exec(event->screenPos());
    if(actionChoisie!=NULL)
    {
        if(actionChoisie==removeAction)
        {
            //supression de la propriété
            maman->ui->tableWidgetProperties->removeRow(maman->ui->tableWidgetProperties->currentRow());
            //enlever la propriété du vecteur de l'entité
            lEntite->vecteurChamps.remove(lEntite->vecteurChamps.indexOf(this));
            //et destructeur de l'instance
            deleteLater();

        }
        //qlq chose a été fait
        else
        {
            if(actionChoisie==editAction)
            {
                maman->editProperty(this);
            }
        }

    }//fi du si qlq chose a ete fait
}
void Property::dropEvent( QGraphicsSceneDragDropEvent* event)
{
    qDebug()<<"void Property::dropEvent(QDropEvent *event)";
    event->accept();
}
void Property::dragEnterEvent( QGraphicsSceneDragDropEvent* event)
{
    qDebug()<<"void Property::dragEnterEvent(QDragEnterEvent *event)";
    event->accept();
}
void Property::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug()<<"void Property::dragMoveEvent(QGraphicsSceneDragDropEvent *event)";
    event->accept();
}

QString Property::toSql()
{
    //les couleurs
    QString coulMotReserve="#ad2bee";
    QString coulTypeChamp="#87711d";
    QString coulNomTable="#29a329";
    QString coulNomChamp="#39b339";
    QString coulTailleChamp="#97812d";
    QString resultat;
    resultat="<font color=\""+coulNomChamp+"\">`"+this->nom+"`</font> <font color=\""+coulTypeChamp+"\">"+this->sonType+"</font>";
    if(!taille.isEmpty())
    {
        resultat+="(<font color=\""+coulTailleChamp+"\">"+taille+"</font>)";
    }
    return(resultat);
}

