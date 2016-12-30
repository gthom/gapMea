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
