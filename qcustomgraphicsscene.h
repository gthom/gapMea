#ifndef QCUSTOMGRAPHICSSCENE_H
#define QCUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDragEnterEvent>
/**
 * @brief The QCustomGraphicsScene class
 * This class is designed to deal with mouse events
 */
class QCustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QCustomGraphicsScene(QWidget *);
    /**
     * @brief mousePressEvent
     * @param mouseEvent
     * some usefull code
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    //on peut lier ou déplacer outil est l'outil choisi
    /**
     * @brief outil
     * User Tool  it can be move or link
     */
    QString outil;
};

#endif // QCUSTOMGRAPHICSSCENE_H
