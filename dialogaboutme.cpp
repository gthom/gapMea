#include "dialogaboutme.h"
#include "ui_dialogaboutme.h"

DialogAboutMe::DialogAboutMe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAboutMe)
{
    ui->setupUi(this);
}

DialogAboutMe::~DialogAboutMe()
{
    delete ui;
}
