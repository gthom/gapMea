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
#ifndef DIALOGSORTORDER_H
#define DIALOGSORTORDER_H

#include <QDialog>

namespace Ui {
    class dialogSortOrder;
}

class dialogSortOrder : public QDialog {
    Q_OBJECT
public:
    dialogSortOrder(QWidget *parent = 0);
    ~dialogSortOrder();
    Ui::dialogSortOrder *m_ui;

protected:
    void changeEvent(QEvent *e);



private slots:
    void on_listWidgetChamps_currentRowChanged(int currentRow);
    void on_toolButtonDown_clicked();
    void on_toolButtonUp_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonOk_clicked();
};

#endif // DIALOGSORTORDER_H
