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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "qcustomgraphicsscene.h"
#include "customgraphicsview.h"
#include <QWidget>
#include "entite.h"
#include "lien.h"
#include <QFileInfo>
class Entite;
class Lien;
class Property;


namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class
 * main code of application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    /**
     * @brief maScene
     * the scene where objects are drawed
     */
    QCustomGraphicsScene * maScene;
    /**
     * @brief saved
     * true if no modification has been done false in other case
     */
    bool saved;
    /**
     * @brief fileName
     * name of opened file
     */
    QString openedFileName;

protected:
    /**
     * @brief closeEvent
     * @param event
     * surcharge du closeEvent pour proposer de sauver si besoin
     * needed to ask user to save his work whenever necessary
     */
    void closeEvent(QCloseEvent *event);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString getOpenedFileName(){return openedFileName;}
    /**
     * @brief vectLiens
     * all links
     */
    QVector <Lien*> vectLiens;
    /**
     * @brief vectTable
     *all entities and relations
     */
    QVector <Entite *> vectTable;
    /**
     * @brief prochainX
     * when adding entity it will be drawn there left distance from beginning
     */
    int prochainX;   
    /**
     * @brief getScene
     * @return
     * accessor for scene
     */
    QCustomGraphicsScene* getScene(){return maScene;}
    Ui::MainWindow *ui;
    /**
     * @brief effaceTout
     * remove all from vectors and scene
     */
    void effaceTout();
    void renameEntity(Entite *lEntite);
public slots:
    /**
     * @brief tableSupprimer
     * @param laTableASupprimer
     * @param demanderConfirmation
     * to delete an object from scene
     */
    void tableSupprimer(Entite * laTableASupprimer,bool demanderConfirmation=true);
    /**
     * @brief on_listWidgetObjects_itemActivated
     * @param item
     *when an object is selected in the list
     */
    void on_listWidgetObjects_itemActivated(QListWidgetItem *item);
    /**
     * @brief jointure
     * jointure demandée entre deux tables de la scene
     */
    void jointure(Entite*,Entite*);
    /**
     * @brief getEntiteByName
     * @param nom
     * @return Entity whose name is nom
     */
    Entite* getEntiteByName(QString nom);
    /**
     * @brief supprimerLien
     * @param leLien
     * remove a link
     */
    void supprimerLien(Lien * leLien);
    /**
     * @brief ajouteTable
     * @param t
     *add object to scene
     */
    void ajouteTable(Entite* t);
    /**
     * @brief tableAjouterChamp
     * @param lEntite
     * @param nomDuChamp
     * @param typeDuChamp
     * @param roleDuChamp
     * @param tailleDuChamp
     *add field to object
     */
    void tableAjouterChamp(Entite * lEntite,QString nomDuChamp="property name",QString typeDuChamp="Son type", QString roleDuChamp="Son rôle dans l'objet",QString tailleDuChamp="");
    /**
     * @brief setFileName
     * @param fn
     * accessor for filename (opened file)
     */
    void setFileName(QFileInfo fn);
    /**
     * @brief editProperty
     * @param laPropriete
     *to modify field name or field type
     */
    void editProperty(Property *laPropriete);
    /**
     * @brief selectionne
     * @param lEntite
     * used to programatically select an entity
     */
    void selectionne(Entite *lEntite);
    /**
     * @brief selectionne
     * used to programatically select a field
     */
    void selectionne(Property*);
    /**
     * @brief on_pushButtonModifyProperty_clicked
     * whenever modify property is called
     */
    void on_pushButtonModifyProperty_clicked();
    /**
     * @brief activeDesactiveBoutonApply
     * enable or disable apply button regarding ok application state
     */
    void activeDesactiveBoutonApply();
    /**
     * @brief activeDesactiveInputTaille
     * Somme fields need size as varchar
     */
    void activeDesactiveInputTaille();
private slots:
    /**
     * @brief on_action_quitter_triggered
     * when user wants to Quit
     */
    void on_action_quitter_triggered();
    /**
     * @brief on_action_Add_Entity_triggered
     * user wants to add entity
     */
    void on_action_Add_Entity_triggered();

    void on_pushButtonAddObject_clicked();

    void on_action_Object_list_triggered(bool checked);

    void on_pushButtonAddProperty_clicked();

    void on_tableWidgetProperties_cellChanged(int row, int column);

    void on_lineEditObjectName_textChanged(const QString &arg1);
    /**
     * @brief on_actionLink_triggered
     * link tool is choosen
     */
    void on_actionLink_triggered();
    /**
     * @brief on_actionMove_triggered
     * Move tool is choosen
     */
    void on_actionMove_triggered();
    /**
     * @brief on_actionSave_triggered
     * user wants to save his work
     */
    void on_actionSave_triggered();
    /**
     * @brief on_action_Open_triggered
     * User wants to open a file
     */
    void on_action_Open_triggered();
    /**
     * @brief on_actionZoom_Best_triggered
     * user wants to see all schema
     */
    void on_actionZoom_Best_triggered();
    /**
     * @brief on_actionZoom_2_triggered
     *  zoom out
     */
    void on_actionZoom_2_triggered();
    /**
     * @brief on_actionZoom_triggered
     *zoom in
     */
    void on_actionZoom_triggered();
    /**
     * @brief on_action_sql_triggered
     * @param checked if true sql code is shown else it is hidden
     * user wants to generate and see sql code
     */
    void on_action_sql_triggered(bool checked);
    /**
     * @brief on_actionAbout_Qt_triggered
     *shows Qt about dialog
     */
    void on_actionAbout_Qt_triggered();
    /**
     * @brief on_action_About_triggered
     *shows gapmea about dialog
     */
    void on_action_About_triggered();
    void on_action_Properties_triggered(bool checked);
    /**
     * @brief setSaved
     * write accessor for saved property
     */
    void setSaved(bool);
    /**
     * @brief on_tableWidgetProperties_itemSelectionChanged
     * User select or unseelect a field
     */
    void on_tableWidgetProperties_itemSelectionChanged();
    /**
     * @brief on_actionNew_Document_triggered
     * User wants to begin a new schema.
     */
    void on_actionNew_Document_triggered();
    /**
     * @brief on_listWidgetObjects_itemSelectionChanged
     * Another entity is selected in the list
     */
    void on_listWidgetObjects_itemSelectionChanged();
    void on_lineEditPropertyName_textChanged(const QString &arg1);

    void on_actionSaveAs_triggered();
    void on_pushButtonDeleteProperty_clicked();
    void on_action_Export_triggered();
    void on_action_Imprimer_triggered();
    void on_dockWidgetObjects_visibilityChanged(bool visible);
    void on_dockWidgetProperties_visibilityChanged(bool visible);
};

#endif // MAINWINDOW_H
