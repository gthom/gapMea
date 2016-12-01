/********************************************************************************
** Form generated from reading UI file 'dialogtypejointure.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGTYPEJOINTURE_H
#define UI_DIALOGTYPEJOINTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogTypeJointure
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBoxType;
    QHBoxLayout *horizontalLayout;
    QLabel *labelRelationName;
    QLineEdit *lineEditRelationName;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *DialogTypeJointure)
    {
        if (DialogTypeJointure->objectName().isEmpty())
            DialogTypeJointure->setObjectName(QStringLiteral("DialogTypeJointure"));
        DialogTypeJointure->setWindowModality(Qt::ApplicationModal);
        DialogTypeJointure->resize(227, 97);
        QIcon icon;
        icon.addFile(QStringLiteral(":/gapQBE.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogTypeJointure->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DialogTypeJointure);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(DialogTypeJointure);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        comboBoxType = new QComboBox(DialogTypeJointure);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/cif"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxType->addItem(icon1, QString());
        comboBoxType->addItem(QString());
        comboBoxType->addItem(QString());
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/leakRelation.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxType->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/association"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxType->addItem(icon3, QString());
        comboBoxType->setObjectName(QStringLiteral("comboBoxType"));

        horizontalLayout_2->addWidget(comboBoxType);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelRelationName = new QLabel(DialogTypeJointure);
        labelRelationName->setObjectName(QStringLiteral("labelRelationName"));

        horizontalLayout->addWidget(labelRelationName);

        lineEditRelationName = new QLineEdit(DialogTypeJointure);
        lineEditRelationName->setObjectName(QStringLiteral("lineEditRelationName"));

        horizontalLayout->addWidget(lineEditRelationName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonOk = new QPushButton(DialogTypeJointure);
        pushButtonOk->setObjectName(QStringLiteral("pushButtonOk"));

        horizontalLayout_3->addWidget(pushButtonOk);

        pushButtonCancel = new QPushButton(DialogTypeJointure);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));

        horizontalLayout_3->addWidget(pushButtonCancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(DialogTypeJointure);

        QMetaObject::connectSlotsByName(DialogTypeJointure);
    } // setupUi

    void retranslateUi(QDialog *DialogTypeJointure)
    {
        DialogTypeJointure->setWindowTitle(QApplication::translate("DialogTypeJointure", "Relation Type", 0));
        label->setText(QApplication::translate("DialogTypeJointure", "Please choose a type:", 0));
        comboBoxType->setItemText(0, QApplication::translate("DialogTypeJointure", "Cif", 0));
        comboBoxType->setItemText(1, QApplication::translate("DialogTypeJointure", "Df", 0));
        comboBoxType->setItemText(2, QApplication::translate("DialogTypeJointure", "Leg", 0));
        comboBoxType->setItemText(3, QApplication::translate("DialogTypeJointure", "Leak Relation", 0));
        comboBoxType->setItemText(4, QApplication::translate("DialogTypeJointure", "Relation", 0));

        labelRelationName->setText(QApplication::translate("DialogTypeJointure", "Relation Name:", 0));
        pushButtonOk->setText(QApplication::translate("DialogTypeJointure", "&Ok", 0));
        pushButtonCancel->setText(QApplication::translate("DialogTypeJointure", "&Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogTypeJointure: public Ui_DialogTypeJointure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTYPEJOINTURE_H
