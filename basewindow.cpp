#include "basewindow.h"
#include "Demo.h"
#include "ui_basewindow.h"
#include "theory.h"
#include "test.h"
#include "questions.h"
#include "identification.h"
#include "help.h"
#include <QDebug>

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(1024,768);
    createMenus();
}

BaseWindow::~BaseWindow()
{
    //dtor
}

void BaseWindow::actionShowTheory()
{
    Theory *window = new Theory();
    this->close();
    window->show();
}

void BaseWindow::actionStartDemo()
{
    Demo *window = new Demo();
    this->close();
    window->show();
}

void BaseWindow::actionStartTrainTest()
{
    Test *window = new Test(true);
    this->close();
    window->show();
}

void BaseWindow::actionStartControlTest()
{
    Identification *window = new Identification();
    this->close();
    window->show();
}

void BaseWindow::actionShowHelp()
{
    Help *window = new Help();
    window->show();
}

void BaseWindow::createMenus()
{
    //-------------------Меню ТЕОРИЯ-------------------------------//
    mnTheory = new QMenu("Теория"); // пункт меню
    showTheory = new QAction("Просмотреть теорию", this); //доступное действие
    connect(showTheory, SIGNAL(triggered()), this, SLOT(actionShowTheory()));
    mnTheory->addAction(showTheory); //добавили экшн в меню

    //-------------------------------------------------------------------//
    //----------------Меню ДЕМОНСТРАЦИЯ----------------------------//
    mnDemo = new QMenu("Демонстрация"); // пункт меню
    startDemo = new QAction("Перейти к демонстрации", this);
    connect(startDemo, SIGNAL(triggered()), this, SLOT(actionStartDemo()));
    mnDemo->addAction(startDemo); //добавили экшн в меню
    //-------------------------------------------------------------------//
    //----------------Меню ТЕСТ----------------------------//
    mnTest = new QMenu("Тест"); // пункт меню
    startTrainTest = new QAction("Начать учебное тестирование", this);
    connect(startTrainTest, SIGNAL(triggered()), this, SLOT(actionStartTrainTest()));
    startControlTest = new QAction("Начать контрольное тестирование", this);
    connect(startControlTest, SIGNAL(triggered()), this, SLOT(actionStartControlTest()));
    mnTest->addAction(startTrainTest);
    mnTest->addAction(startControlTest);
    //-------------------------------------------------------------------//
    //------------------Меню СПРАВКА-------------------------------//
    mnHelp = new QMenu("Справка"); // пункт меню
    showHelp = new QAction("Показать справку", this);
    connect(showHelp, SIGNAL(triggered()), this, SLOT(actionShowHelp()));
    mnHelp->addAction(showHelp);
    //-------------------------------------------------------------------//
    menuBar()->addMenu(mnTheory);
    menuBar()->addMenu(mnDemo);
    menuBar()->addMenu(mnTest);
    menuBar()->addMenu(mnHelp);

}
