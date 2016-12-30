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
#include "dialogsortorder.h"
#include "ui_dialogsortorder.h"

dialogSortOrder::dialogSortOrder(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::dialogSortOrder)
{
    m_ui->setupUi(this);

}

dialogSortOrder::~dialogSortOrder()
{
    delete m_ui;
}

void dialogSortOrder::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void dialogSortOrder::on_pushButtonOk_clicked()
{
    accept();
}



void dialogSortOrder::on_pushButtonCancel_clicked()
{
    reject();
}

void dialogSortOrder::on_toolButtonUp_clicked()
{
    if(!m_ui->listWidgetChamps->selectedItems().isEmpty())
    {
        //monter l'elt selectionne d'une case vers le haut
        int numero=m_ui->listWidgetChamps->currentRow();
        QListWidgetItem* elt=m_ui->listWidgetChamps->takeItem(numero);


            m_ui->listWidgetChamps->insertItem(numero-1,elt);
            m_ui->listWidgetChamps->setCurrentRow(numero-1);


    }
}

void dialogSortOrder::on_toolButtonDown_clicked()
{
    if(!m_ui->listWidgetChamps->selectedItems().isEmpty())
    {
        //descendre l'elt selectionne d'une case vers le bas
        int numero=m_ui->listWidgetChamps->currentRow();
        QListWidgetItem* elt=m_ui->listWidgetChamps->takeItem(numero);

            m_ui->listWidgetChamps->insertItem(numero+1,elt);
            m_ui->listWidgetChamps->setCurrentRow(numero+1);


    }
}

void dialogSortOrder::on_listWidgetChamps_currentRowChanged(int currentRow)
{
    m_ui->toolButtonDown->setEnabled(currentRow<m_ui->listWidgetChamps->count()-1);
    m_ui->toolButtonUp->setEnabled(currentRow>0);
}
