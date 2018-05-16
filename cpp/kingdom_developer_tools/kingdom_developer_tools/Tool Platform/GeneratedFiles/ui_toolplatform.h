/********************************************************************************
** Form generated from reading UI file 'toolplatform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLPLATFORM_H
#define UI_TOOLPLATFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolPlatformClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ToolPlatformClass)
    {
        if (ToolPlatformClass->objectName().isEmpty())
            ToolPlatformClass->setObjectName(QStringLiteral("ToolPlatformClass"));
        ToolPlatformClass->resize(600, 400);
        menuBar = new QMenuBar(ToolPlatformClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ToolPlatformClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ToolPlatformClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ToolPlatformClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ToolPlatformClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ToolPlatformClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ToolPlatformClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ToolPlatformClass->setStatusBar(statusBar);

        retranslateUi(ToolPlatformClass);

        QMetaObject::connectSlotsByName(ToolPlatformClass);
    } // setupUi

    void retranslateUi(QMainWindow *ToolPlatformClass)
    {
        ToolPlatformClass->setWindowTitle(QApplication::translate("ToolPlatformClass", "ToolPlatform", 0));
    } // retranslateUi

};

namespace Ui {
    class ToolPlatformClass: public Ui_ToolPlatformClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLPLATFORM_H
