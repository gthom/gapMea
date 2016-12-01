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
