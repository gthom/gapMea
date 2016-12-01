/********************************************************************************
** Form generated from reading UI file 'dialogaboutme.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGABOUTME_H
#define UI_DIALOGABOUTME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogAboutMe
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QTextBrowser *textBrowser;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QTextBrowser *textBrowser_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogAboutMe)
    {
        if (DialogAboutMe->objectName().isEmpty())
            DialogAboutMe->setObjectName(QStringLiteral("DialogAboutMe"));
        DialogAboutMe->resize(654, 299);
        verticalLayout = new QVBoxLayout(DialogAboutMe);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(DialogAboutMe);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textBrowser = new QTextBrowser(tab);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setOpenExternalLinks(true);

        horizontalLayout->addWidget(textBrowser);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
#ifndef QT_NO_STATUSTIP
        label_2->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        label_2->setWhatsThis(QStringLiteral(""));
#endif // QT_NO_WHATSTHIS

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
#ifndef QT_NO_WHATSTHIS
        label_3->setWhatsThis(QStringLiteral(""));
#endif // QT_NO_WHATSTHIS

        verticalLayout_2->addWidget(label_3);

        textBrowser_2 = new QTextBrowser(tab_2);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setOpenExternalLinks(true);

        verticalLayout_2->addWidget(textBrowser_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QStringLiteral(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        label->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        label->setWhatsThis(QStringLiteral(""));
#endif // QT_NO_WHATSTHIS

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(DialogAboutMe);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogAboutMe);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogAboutMe, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogAboutMe, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogAboutMe);
    } // setupUi

    void retranslateUi(QDialog *DialogAboutMe)
    {
        DialogAboutMe->setWindowTitle(QApplication::translate("DialogAboutMe", "About Me", 0));
        textBrowser->setHtml(QApplication::translate("DialogAboutMe", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">GapMea is an open source project. The members of the GThom'sSoftware team invest their free time in this project. Even small donations like 10 Euros show us that somebody likes the work we do. The donations motivate all team members to continue investing time in this project.There are several levels of sponsorship. For details see the become a Sponsor page.</p>\n"
"<p style=\" margin-top:14px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a name=\"idm140278778939456\"></a><span style=\" font-size:large; font-we"
                        "ight:600;\">S</span><span style=\" font-size:large; font-weight:600;\">outenez le logiciel libre</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Ce logiciel  est sous licence GPL. Merci de  participer financi\303\250rement au projet.<a href=\"http://PayPal.Me/GThomSoftware/10\"><span style=\" text-decoration: underline; color:#0000ff;\">Donate via Paypal</span></a>.				</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Copyright (C) Gilles Thomassin 2015-2016      This program is free software: you can redistribute it and/or modify    it under the terms of the GNU General Public License as published by    the Free Software Foundation, either version 3 of the License, or any later version.    This program is distributed in the hope that it will be useful,    but WITHOUT ANY WARRANTY; without even the implied warranty of    MERCHANTABILITY or FIT"
                        "NESS FOR A PARTICULAR PURPOSE.  See the    GNU General Public License for more details.   </p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("DialogAboutMe", "Licence", 0));
        label_2->setText(QApplication::translate("DialogAboutMe", "Author: Gilles Thomassin", 0));
        label_3->setText(QApplication::translate("DialogAboutMe", "Mail: gthomassingap@gmail.com", 0));
        textBrowser_2->setHtml(QApplication::translate("DialogAboutMe", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">L'auteur est <span style=\" font-weight:600;\">professeur d'informatique</span> depuis 1991 en Section de Technicien Sup\303\251rieur &quot;Services Informatiques aux Organisations&quot;.</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Cette section post-bac plus commun\303\251ment nomm\303\251e BTS SIO <a href=\"http://www.btsinfogap.org\"><span style=\" text-decoration: underline; color:#0000ff;\"> www.btsinfogap.org</span></a> a \303\251t\303\251 cr\303\251\303\251e en 1984 "
                        " au sein du<a href=\"https://www.atrium-paca.fr/web/lgt-dominique-villars-050101/lycee-villars?\"><span style=\" text-decoration: underline; color:#0000ff;\"> Lyc\303\251e Dominique Villars</span></a>. </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Elle permet de former en deux ans de vrais professionnels de l'informatique sp\303\251cialis\303\251s soit en d\303\251veloppement soit en r\303\251seau.</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">L'auteur enseigne:<br />Les syst\303\250mes d'exploitation libres, l'administration syst\303\250me, la gestion de parc et d'incidents, la supervision des r\303\251seaux , la conception des r\303\251seaux et la configuration des routeurs et switchs et points d'acc\303\250s WIFI, la virtualisation et les syst\303\250mes \303\240 tol\303\251rance de panne.</p>\n"
"<p style=\" margin-top:12px; margin-bottom"
                        ":12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Mais aussi: l'analyse des donn\303\251es, le d\303\251veloppement d'applications Web (PHP,javascript/ajax,Html/css), <br />la programmation objet en c++ ainsi que la programmation \303\251venementielle avec Qt, ainsi que le d\303\251veloppement d'applications android.</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">			Ce logiciel  est sous licence GPL. Pour que ce logiciel perdure et s'am\303\251liore, merci de participer financi\303\250rement au projet.</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://PayPal.Me/GThomSoftware\"><span style=\" text-decoration: underline; color:#0000ff;\">Donate via Paypal</span></a></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">.				</p><"
                        "/body></html>", 0));
        label->setText(QApplication::translate("DialogAboutMe", "Copyright @ Gilles Thomassin 2015", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("DialogAboutMe", "Author", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogAboutMe: public Ui_DialogAboutMe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGABOUTME_H
