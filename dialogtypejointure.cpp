#include "dialogtypejointure.h"
#include "ui_dialogtypejointure.h"
#include <QDebug>
#include <QDesktopServices>
#define RELATION "Relation"

DialogTypeJointure::DialogTypeJointure(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogTypeJointure)
{
    m_ui->setupUi(this);
    m_ui->labelRelationName->setVisible(false);
    m_ui->lineEditRelationName->setVisible(false);
}

DialogTypeJointure::~DialogTypeJointure()
{
    delete m_ui;
}

void DialogTypeJointure::changeEvent(QEvent *e)
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
void DialogTypeJointure::onLineEditNomRelationChanged(QString arg1)
{
    m_ui->pushButtonOk->setEnabled(!arg1.isEmpty());
}

void DialogTypeJointure::on_comboBoxType_activated(const QString &arg1)
{
    qDebug()<<"void DialogTypeJointure::on_comboBoxType_activated(const QString &arg1)";

    bool isRelation=arg1==tr(RELATION);
    if(isRelation)
    {
        connect(m_ui->lineEditRelationName,SIGNAL(textChanged(QString)),this,SLOT(onLineEditNomRelationChanged(QString)));
        m_ui->pushButtonOk->setEnabled(false);
        //je donne le focus à la lineEdit
        m_ui->lineEditRelationName->setFocus();
    }
    else//ce n'est pas une relation
    {
        disconnect(m_ui->lineEditRelationName,SIGNAL(textChanged(QString)),this,SLOT(onLineEditNomRelationChanged(QString)));
        //on active le bouton ok
        m_ui->pushButtonOk->setEnabled(true);
    }
    m_ui->labelRelationName->setVisible(isRelation);
    m_ui->lineEditRelationName->setVisible(isRelation);
}

void DialogTypeJointure::on_pushButtonCancel_clicked()
{
    reject();
}

void DialogTypeJointure::on_pushButtonOk_clicked()
{
    accept();
}
