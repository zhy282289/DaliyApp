/********************************************************************************
** Form generated from reading UI file 'daliyapp.ui'
**
** Created: Mon Mar 17 10:52:58 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DALIYAPP_H
#define UI_DALIYAPP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DaliyAppClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DaliyAppClass)
    {
        if (DaliyAppClass->objectName().isEmpty())
            DaliyAppClass->setObjectName(QString::fromUtf8("DaliyAppClass"));
        DaliyAppClass->resize(600, 400);
        menuBar = new QMenuBar(DaliyAppClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        DaliyAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DaliyAppClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DaliyAppClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DaliyAppClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        DaliyAppClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DaliyAppClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DaliyAppClass->setStatusBar(statusBar);

        retranslateUi(DaliyAppClass);

        QMetaObject::connectSlotsByName(DaliyAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *DaliyAppClass)
    {
        DaliyAppClass->setWindowTitle(QApplication::translate("DaliyAppClass", "DaliyApp", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DaliyAppClass: public Ui_DaliyAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DALIYAPP_H
