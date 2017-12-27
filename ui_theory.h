/********************************************************************************
** Form generated from reading UI file 'theory.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THEORY_H
#define UI_THEORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Theory
{
public:
    QWidget *centralWidget;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Theory)
    {
        if (Theory->objectName().isEmpty())
            Theory->setObjectName(QStringLiteral("Theory"));
        Theory->resize(400, 300);
        centralWidget = new QWidget(Theory);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(60, 10, 256, 192));
        Theory->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Theory);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 26));
        Theory->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Theory);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Theory->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Theory);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Theory->setStatusBar(statusBar);

        retranslateUi(Theory);

        QMetaObject::connectSlotsByName(Theory);
    } // setupUi

    void retranslateUi(QMainWindow *Theory)
    {
        Theory->setWindowTitle(QApplication::translate("Theory", "Theory", 0));
    } // retranslateUi

};

namespace Ui {
    class Theory: public Ui_Theory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THEORY_H
