#ifndef QSELECTOR_H
#define QSELECTOR_H

#include <QTableWidget>
#include <QDragEnterEvent>

class QSelector : public QTableWidget
{
public:
    QSelector(QWidget* parent=0);
 void dragEnterEvent(QDragEnterEvent *event);
 void dragMoveEvent(QDragMoveEvent *event);
 void dropEvent(QDropEvent *event);

};

#endif // QSELECTOR_H
