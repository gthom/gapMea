#include "query.h"

query::query(dialogRelation* mum,QString nom,qreal x,qreal y, QGraphicsItem* parent, QCustomGraphicsScene * laScene, QStringList listeDesChamps,QString requete,QString pAlias)
        :table(mum,nom,x,y,parent,laScene,listeDesChamps)

{
    sql=requete;
    alias=pAlias;
}
