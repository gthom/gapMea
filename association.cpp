#include "association.h"
#include <QPainter>
#include <QDebug>

Association::Association(MainWindow* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent,  QStringList listeChamps, bool isAssoc)
 : Entite(mum,nom,x,y, parent,listeChamps,isAssoc)
{
    qDebug()<<"Association::Association(MainWindow* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent, QCustomGraphicsScene * laScene, QStringList listeChamps)";
  QGraphicsRectItem::setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable
    |QGraphicsItem::ItemSendsGeometryChanges
    |QGraphicsItem::ItemClipsChildrenToShape);
  m_radius_x=20;
  m_radius_y=m_radius_x;
  rectTitle=NULL;

}


void Association::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    qDebug()<<"void Association::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)";
    painter->setRenderHint(QPainter::Antialiasing,true);
    if (QGraphicsRectItem::isSelected())
    {
        QPen pen;
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
    }

    //les dimensions
    int hauteur=title->boundingRect().height();
    if(vecteurChamps.size()>0)
        hauteur+=vecteurChamps.size()*vecteurChamps[0]->boundingRect().height();
    else
        hauteur*=2;
    QRectF leRect=rect();
    leRect.setHeight(hauteur);
    setRect(leRect);
    //le contour
    painter->drawRoundedRect(this->rect(),m_radius_x,m_radius_y);
    //essais
    QLinearGradient gradient(rect().topLeft(), rect().bottomRight()); // diagonal gradient from top-left to bottom-right
    gradient.setColorAt(0, QColor("#FFD4A3"));
    gradient.setColorAt(1, Qt::white);
    /* nouvel essais */
    QPainterPath roundRectPath;

    float largeur,left,top;
    largeur=rect().width();
    hauteur=rect().height();
    left=0;
    top=0;
    float rayon=20;

    roundRectPath.moveTo(largeur, top+rayon);
    roundRectPath.arcTo(largeur-2*rayon, top, 2*rayon, 2*rayon, 0.0, 90.0);
    roundRectPath.lineTo(left+rayon, top);
    roundRectPath.arcTo(left, top, 2*rayon, 2*rayon, 90.0, 90.0);
    roundRectPath.lineTo(top, hauteur-rayon);
    roundRectPath.arcTo(left, hauteur-2*rayon, 2*rayon, 2*rayon, 180.0, 90.0);
    roundRectPath.lineTo(largeur-rayon, hauteur);
    roundRectPath.arcTo(largeur-2*rayon, hauteur-2*rayon, 2*rayon, 2*rayon, 270.0, 90.0);
    roundRectPath.closeSubpath();
    //ajout de la ligne
    //la ligne sous le titre

    float y=title->boundingRect().height();
    roundRectPath.moveTo(0,y);
    roundRectPath.lineTo(rect().width(),y);
    //painter->setBrush(gradient);//pas top à l'impression
    painter->setBrush(QColor("#FFD4A3"));
    painter->drawPath(roundRectPath);

}

void Association::setRoundedRect(const QRectF rect, const double radius_x, const double radius_y)
{
    qDebug()<<"void Association::setRoundedRect(const QRectF rect, const double radius_x, const double radius_y)"<<endl;
  this->setRect(rect);
  this->setRadiusX(radius_x);
  this->setRadiusY(radius_y);
}

QVector <Entite*> Association::vectEntitesAssociees()
{
    qDebug()<<"QVector <Entite*> Association::vectEntitesAssociees()"<<endl;
    QVector <Entite*> resultat;
    foreach (Lien* leLien, vectLiens) {
        if(leLien->t2==this && leLien->typeDeJointure==LEG)
        {
            resultat.append(leLien->t1);
        }
    }
    return resultat;
}
QVector < QPair <Entite*,QString> > Association::vectEntitesRolesAssociees()
{
    qDebug()<<"QVector <Entite*> Association::vectEntitesAssociees()"<<endl;
    QVector < QPair <Entite*,QString> > resultat;
    foreach (Lien* leLien, vectLiens) {
        if(leLien->t2==this && leLien->typeDeJointure==LEG)
        {
            resultat.append(QPair<Entite*,QString>(leLien->t1,leLien->texteDuRole ) );
        }
    }
    return resultat;
}
