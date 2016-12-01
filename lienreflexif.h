#ifndef LIENREFLEXIF_H
#define LIENREFLEXIF_H

#include <QObject>
#include "lien.h"
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "entite.h"
#include <QColor>
#include "types.h"
class LienReflexif : public Lien
{
public:
    LienReflexif(Entite* qg1,Entite* qg2,QGraphicsItem* parent, QString typ="Natural",QString relationName="",QString pRole="");
    ~LienReflexif();
    void calculeCoordonnees();
    QGraphicsLineItem  * firstLine;
    void ajouteElementsAuGroupe();
    //bool reflexif;
};

#endif // LIENREFLEXIF_H
