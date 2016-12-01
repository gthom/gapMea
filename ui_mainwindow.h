/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "customgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_quitter;
    QAction *action_Add_Entity;
    QAction *action_Object_list;
    QAction *action_Properties;
    QAction *actionMove;
    QAction *actionLink;
    QAction *actionSave;
    QAction *action_Open;
    QAction *action_sql;
    QAction *actionZoom;
    QAction *actionZoom_2;
    QAction *actionZoom_Best;
    QAction *action_About;
    QAction *actionAbout_Qt;
    QAction *actionNew_Document;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    customGraphicsView *graphicsView;
    QTextEdit *textEditSql;
    QMenuBar *menuBar;
    QMenu *menu_fichier;
    QMenu *menuWindows;
    QMenu *menu_Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidgetObjects;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidgetObjects;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditObjectName;
    QPushButton *pushButtonAddObject;
    QDockWidget *dockWidgetProperties;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxProperties;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *tableWidgetProperties;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonAddProperty;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBoxEditNewProperty;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *lineEditPropertyName;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditPropertyRole;
    QComboBox *comboBoxPropertyType;
    QLabel *label_5;
    QLineEdit *lineEditTaille;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonModifyProperty;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1007, 717);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/icone"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_quitter = new QAction(MainWindow);
        action_quitter->setObjectName(QStringLiteral("action_quitter"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/quit"), QSize(), QIcon::Normal, QIcon::Off);
        action_quitter->setIcon(icon1);
        action_Add_Entity = new QAction(MainWindow);
        action_Add_Entity->setObjectName(QStringLiteral("action_Add_Entity"));
        action_Add_Entity->setCheckable(true);
        action_Object_list = new QAction(MainWindow);
        action_Object_list->setObjectName(QStringLiteral("action_Object_list"));
        action_Object_list->setCheckable(true);
        action_Object_list->setChecked(true);
        action_Properties = new QAction(MainWindow);
        action_Properties->setObjectName(QStringLiteral("action_Properties"));
        action_Properties->setCheckable(true);
        action_Properties->setChecked(true);
        actionMove = new QAction(MainWindow);
        actionMove->setObjectName(QStringLiteral("actionMove"));
        actionMove->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/move"), QSize(), QIcon::Normal, QIcon::Off);
        actionMove->setIcon(icon2);
        actionLink = new QAction(MainWindow);
        actionLink->setObjectName(QStringLiteral("actionLink"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/relier"), QSize(), QIcon::Normal, QIcon::Off);
        actionLink->setIcon(icon3);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/save"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/open"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open->setIcon(icon5);
        action_sql = new QAction(MainWindow);
        action_sql->setObjectName(QStringLiteral("action_sql"));
        action_sql->setCheckable(true);
        actionZoom = new QAction(MainWindow);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/zoomPlus"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom->setIcon(icon6);
        actionZoom_2 = new QAction(MainWindow);
        actionZoom_2->setObjectName(QStringLiteral("actionZoom_2"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/zoomMoins"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_2->setIcon(icon7);
        actionZoom_Best = new QAction(MainWindow);
        actionZoom_Best->setObjectName(QStringLiteral("actionZoom_Best"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/zoomBestFit"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Best->setIcon(icon8);
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QStringLiteral("action_About"));
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        actionNew_Document = new QAction(MainWindow);
        actionNew_Document->setObjectName(QStringLiteral("actionNew_Document"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/fileNew"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Document->setIcon(icon9);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        graphicsView = new customGraphicsView(splitter);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        splitter->addWidget(graphicsView);
        textEditSql = new QTextEdit(splitter);
        textEditSql->setObjectName(QStringLiteral("textEditSql"));
        splitter->addWidget(textEditSql);

        verticalLayout_4->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1007, 17));
        menu_fichier = new QMenu(menuBar);
        menu_fichier->setObjectName(QStringLiteral("menu_fichier"));
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QStringLiteral("menuWindows"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QStringLiteral("menu_Help"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidgetObjects = new QDockWidget(MainWindow);
        dockWidgetObjects->setObjectName(QStringLiteral("dockWidgetObjects"));
        dockWidgetObjects->setWindowIcon(icon);
        dockWidgetObjects->setFloating(true);
        dockWidgetObjects->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_5 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listWidgetObjects = new QListWidget(groupBox);
        listWidgetObjects->setObjectName(QStringLiteral("listWidgetObjects"));

        verticalLayout_2->addWidget(listWidgetObjects);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEditObjectName = new QLineEdit(groupBox);
        lineEditObjectName->setObjectName(QStringLiteral("lineEditObjectName"));
        lineEditObjectName->setMaxLength(25);

        horizontalLayout->addWidget(lineEditObjectName);

        pushButtonAddObject = new QPushButton(groupBox);
        pushButtonAddObject->setObjectName(QStringLiteral("pushButtonAddObject"));
        pushButtonAddObject->setEnabled(false);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/add"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddObject->setIcon(icon10);
        pushButtonAddObject->setDefault(true);

        horizontalLayout->addWidget(pushButtonAddObject);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_5->addWidget(groupBox);

        dockWidgetObjects->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetObjects);
        dockWidgetProperties = new QDockWidget(MainWindow);
        dockWidgetProperties->setObjectName(QStringLiteral("dockWidgetProperties"));
        dockWidgetProperties->setWindowIcon(icon);
        dockWidgetProperties->setFloating(true);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBoxProperties = new QGroupBox(dockWidgetContents_2);
        groupBoxProperties->setObjectName(QStringLiteral("groupBoxProperties"));
        horizontalLayout_4 = new QHBoxLayout(groupBoxProperties);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        tableWidgetProperties = new QTableWidget(groupBoxProperties);
        if (tableWidgetProperties->columnCount() < 4)
            tableWidgetProperties->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetProperties->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetProperties->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetProperties->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetProperties->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetProperties->setObjectName(QStringLiteral("tableWidgetProperties"));
        tableWidgetProperties->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetProperties->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout_4->addWidget(tableWidgetProperties);


        verticalLayout_3->addWidget(groupBoxProperties);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButtonAddProperty = new QPushButton(dockWidgetContents_2);
        pushButtonAddProperty->setObjectName(QStringLiteral("pushButtonAddProperty"));
        pushButtonAddProperty->setEnabled(false);
        pushButtonAddProperty->setIcon(icon10);

        horizontalLayout_3->addWidget(pushButtonAddProperty);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_3);

        groupBoxEditNewProperty = new QGroupBox(dockWidgetContents_2);
        groupBoxEditNewProperty->setObjectName(QStringLiteral("groupBoxEditNewProperty"));
        verticalLayout = new QVBoxLayout(groupBoxEditNewProperty);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(groupBoxEditNewProperty);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        lineEditPropertyName = new QLineEdit(groupBoxEditNewProperty);
        lineEditPropertyName->setObjectName(QStringLiteral("lineEditPropertyName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditPropertyName);

        label_3 = new QLabel(groupBoxEditNewProperty);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(groupBoxEditNewProperty);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        lineEditPropertyRole = new QLineEdit(groupBoxEditNewProperty);
        lineEditPropertyRole->setObjectName(QStringLiteral("lineEditPropertyRole"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditPropertyRole);

        comboBoxPropertyType = new QComboBox(groupBoxEditNewProperty);
        comboBoxPropertyType->insertItems(0, QStringList()
         << QStringLiteral("FLOAT")
         << QStringLiteral("INTEGER")
         << QStringLiteral("NUMERIC")
         << QStringLiteral("BOOL")
         << QStringLiteral("VARCHAR")
         << QStringLiteral("BIT")
         << QStringLiteral("DATE")
         << QStringLiteral("TIME")
         << QStringLiteral("DATETIME")
         << QStringLiteral("SET")
         << QStringLiteral("ENUM")
         << QStringLiteral("BLOB")
        );
        comboBoxPropertyType->setObjectName(QStringLiteral("comboBoxPropertyType"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBoxPropertyType);

        label_5 = new QLabel(groupBoxEditNewProperty);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        lineEditTaille = new QLineEdit(groupBoxEditNewProperty);
        lineEditTaille->setObjectName(QStringLiteral("lineEditTaille"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditTaille);


        verticalLayout->addLayout(formLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonModifyProperty = new QPushButton(groupBoxEditNewProperty);
        pushButtonModifyProperty->setObjectName(QStringLiteral("pushButtonModifyProperty"));
        pushButtonModifyProperty->setEnabled(false);

        horizontalLayout_2->addWidget(pushButtonModifyProperty);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(groupBoxEditNewProperty);

        dockWidgetProperties->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetProperties);

        menuBar->addAction(menu_fichier->menuAction());
        menuBar->addAction(menuWindows->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_fichier->addAction(actionNew_Document);
        menu_fichier->addAction(action_Open);
        menu_fichier->addAction(actionSave);
        menu_fichier->addAction(action_quitter);
        menuWindows->addAction(action_Object_list);
        menuWindows->addAction(action_Properties);
        menuWindows->addAction(action_sql);
        menuWindows->addAction(actionZoom);
        menuWindows->addAction(actionZoom_2);
        menuWindows->addAction(actionZoom_Best);
        menu_Help->addAction(action_About);
        menu_Help->addAction(actionAbout_Qt);
        mainToolBar->addAction(action_Open);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionMove);
        mainToolBar->addAction(actionLink);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_sql);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionZoom_Best);
        mainToolBar->addAction(actionZoom);
        mainToolBar->addAction(actionZoom_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "gapMEA", 0));
        action_quitter->setText(QApplication::translate("MainWindow", "&Quit", 0));
        action_Add_Entity->setText(QApplication::translate("MainWindow", "&add Entity", 0));
#ifndef QT_NO_TOOLTIP
        action_Add_Entity->setToolTip(QApplication::translate("MainWindow", "add a new object", 0));
#endif // QT_NO_TOOLTIP
        action_Object_list->setText(QApplication::translate("MainWindow", "&Object list", 0));
#ifndef QT_NO_TOOLTIP
        action_Object_list->setToolTip(QApplication::translate("MainWindow", "Show Object List", 0));
#endif // QT_NO_TOOLTIP
        action_Properties->setText(QApplication::translate("MainWindow", "&Properties", 0));
#ifndef QT_NO_TOOLTIP
        action_Properties->setToolTip(QApplication::translate("MainWindow", "Show Object's Properties", 0));
#endif // QT_NO_TOOLTIP
        actionMove->setText(QApplication::translate("MainWindow", "move", 0));
#ifndef QT_NO_TOOLTIP
        actionMove->setToolTip(QApplication::translate("MainWindow", "use this tool to move and select Objects", 0));
#endif // QT_NO_TOOLTIP
        actionLink->setText(QApplication::translate("MainWindow", "link", 0));
#ifndef QT_NO_TOOLTIP
        actionLink->setToolTip(QApplication::translate("MainWindow", "use this tool to link objects", 0));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("MainWindow", "&Save", 0));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "Save actual work", 0));
#endif // QT_NO_TOOLTIP
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0));
#ifndef QT_NO_TOOLTIP
        action_Open->setToolTip(QApplication::translate("MainWindow", "Open a  file", 0));
#endif // QT_NO_TOOLTIP
        action_sql->setText(QApplication::translate("MainWindow", "&sql", 0));
#ifndef QT_NO_TOOLTIP
        action_sql->setToolTip(QApplication::translate("MainWindow", "generate sql code", 0));
#endif // QT_NO_TOOLTIP
        actionZoom->setText(QApplication::translate("MainWindow", "zoom+", 0));
        actionZoom_2->setText(QApplication::translate("MainWindow", "zoom-", 0));
        actionZoom_Best->setText(QApplication::translate("MainWindow", "zoom to fit", 0));
#ifndef QT_NO_TOOLTIP
        actionZoom_Best->setToolTip(QApplication::translate("MainWindow", "Adapt display to content", 0));
#endif // QT_NO_TOOLTIP
        action_About->setText(QApplication::translate("MainWindow", "&About", 0));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About &Qt", 0));
        actionNew_Document->setText(QApplication::translate("MainWindow", "New Document", 0));
#ifndef QT_NO_STATUSTIP
        actionNew_Document->setStatusTip(QApplication::translate("MainWindow", "to create a new document", 0));
#endif // QT_NO_STATUSTIP
        textEditSql->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\" bgcolor=\"#131513\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#8ca68c;\">gtgtgg</span></p></body></html>", 0));
        menu_fichier->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuWindows->setTitle(QApplication::translate("MainWindow", "&Windows", 0));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0));
#ifndef QT_NO_TOOLTIP
        mainToolBar->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        dockWidgetObjects->setWindowTitle(QApplication::translate("MainWindow", "Object List", 0));
#ifndef QT_NO_TOOLTIP
        groupBox->setToolTip(QApplication::translate("MainWindow", "Use this first to create your objects", 0));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("MainWindow", "Object list", 0));
        label->setText(QApplication::translate("MainWindow", "Name:", 0));
        pushButtonAddObject->setText(QApplication::translate("MainWindow", "&Add", 0));
#ifndef QT_NO_TOOLTIP
        dockWidgetProperties->setToolTip(QApplication::translate("MainWindow", "You will see here selected Object's properties", 0));
#endif // QT_NO_TOOLTIP
        dockWidgetProperties->setWindowTitle(QApplication::translate("MainWindow", "Object Properties", 0));
        groupBoxProperties->setTitle(QApplication::translate("MainWindow", "Properties", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetProperties->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetProperties->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Type", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetProperties->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Size", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetProperties->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "R\303\264le", 0));
        pushButtonAddProperty->setText(QApplication::translate("MainWindow", "&Add Property", 0));
        groupBoxEditNewProperty->setTitle(QApplication::translate("MainWindow", "Edit Property", 0));
        label_2->setText(QApplication::translate("MainWindow", "Name:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Type:", 0));
        label_4->setText(QApplication::translate("MainWindow", "R\303\264le:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Size:", 0));
        pushButtonModifyProperty->setText(QApplication::translate("MainWindow", "&Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
