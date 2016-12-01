#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QObject>
#include "entite.h"

/**
 * @brief The customGraphicsView class
 * I had to create my own class to deal with drag and drop
 * I use drag and drop to link objects with other objects
 */
class customGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * @brief customGraphicsView
     * @param parent
     * constructor
     */
    customGraphicsView(QWidget * parent):QGraphicsView(parent){};
    /**
     * @brief dragEnterEvent
     * @param event
     * drag begins
     */
    void dragEnterEvent(QDragEnterEvent *event);
    /**
     * @brief dragMoveEvent
     * @param event
     * drag begun and user move his mouse
     */
    void dragMoveEvent(QDragMoveEvent *event);
    /**
     * @brief dropEvent
     * @param event
     * when a drag begun and user release left mouse button
     */
    void dropEvent(QDropEvent *event);
    /**
     * @brief delimiteur
     * used to separate informations in the mimedata
     */
    QString delimiteur;
//this class emits signals that are plugged into slots
signals:
    /**
     * @brief jointureRequise
     * User wants to link two Objects.
     */
    void jointureRequise(Entite*,Entite*);
    /**
     * @brief ilYADesTablesAAjouter
     */
    void ilYADesTablesAAjouter(QPoint);
    /**
     * @brief supprimerTable
     * @param nomTable Name of the object to remove
     * Users wants to remove the Object whose name is nomTable
     */
    void supprimerTable(QString nomTable);
public slots:
    /**
     * @brief zoomIn
     *Zoom In items are biggest
     */
    void zoomIn();
    /**
     * @brief zoomOut
     * Zoom out items are smaller
     */
    void zoomOut();
};
#endif // CUSTOMGRAPHICSVIEW_H
