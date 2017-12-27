/********************************************************************************
** Form generated from reading UI file 'basewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEWINDOW_H
#define UI_BASEWINDOW_H

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

class Ui_BaseWindow
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BaseWindow)
    {
        if (BaseWindow->objectName().isEmpty())
            BaseWindow->setObjectName(QStringLiteral("BaseWindow"));
        BaseWindow->resize(400, 300);
        centralWidget = new QWidget(BaseWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BaseWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BaseWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 26));
        BaseWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BaseWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BaseWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BaseWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BaseWindow->setStatusBar(statusBar);

        retranslateUi(BaseWindow);

        QMetaObject::connectSlotsByName(BaseWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BaseWindow)
    {
        BaseWindow->setWindowTitle(QApplication::translate("BaseWindow", "BaseWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class BaseWindow: public Ui_BaseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWINDOW_H
