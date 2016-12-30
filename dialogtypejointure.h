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
#ifndef DIALOGTYPEJOINTURE_H
#define DIALOGTYPEJOINTURE_H

#include <QDialog>

namespace Ui {
    class DialogTypeJointure;
}
/**
 * @brief The DialogTypeJointure class
 * This dialog permit to choose relation type
 */
class DialogTypeJointure : public QDialog {
    Q_OBJECT
public:
    DialogTypeJointure(QWidget *parent = 0);
    ~DialogTypeJointure();
    Ui::DialogTypeJointure *m_ui;

protected:
    void changeEvent(QEvent *e);

private slots:
    /**
     * @brief on_comboBoxType_activated
     * @param arg1 new relation type
     */
    void on_comboBoxType_activated(const QString &arg1);
    /**
     * @brief on_pushButtonCancel_clicked
     * Nothing to do
     */
    void on_pushButtonCancel_clicked();
    /**
     * @brief on_pushButtonOk_clicked
     * Validation of changes
     */
    void on_pushButtonOk_clicked();
    /**
     * @brief onLineEditNomRelationChanged
     * @param arg1 new name of relation
     * register new name
     */
    void onLineEditNomRelationChanged(QString arg1);
};

#endif // DIALOGTYPEJOINTURE_H
