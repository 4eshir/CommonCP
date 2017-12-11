#include "basewindow.h"
#include "Demo.h"
#include "ui_basewindow.h"
#include "theory.h"
#include "test.h"
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

void BaseWindow::actionStartTest()
{
    Test *window = new Test();
    this->close();
    window->show();
}

void BaseWindow::actionShowHelp()
{

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
    //----------------РџСѓРЅРєС‚ РјРµРЅСЋ РўР•РЎРўРР РћР’РђРќРР•----------------------------//
    mnTest = new QMenu("Тест"); // СЃРѕР·РґР°РµРј РјРµРЅСЋ РўРµСЃС‚РёСЂРѕРІР°РЅРёРµ
    startTest = new QAction("Начать тестирование", this);
    connect(startTest, SIGNAL(triggered()), this, SLOT(actionStartTest()));
    mnTest->addAction(startTest);
    //-------------------------------------------------------------------//
    //------------------РџСѓРЅРєС‚ РјРµРЅСЋ РЎРџР РђР’РљРђ-------------------------------//
    mnHelp = new QMenu("Справка"); // СЃРѕР·РґР°РµРј РјРµРЅСЋ РЎРїСЂР°РІРєР°
    showHelp = new QAction("Показать справку", this);
    connect(showHelp, SIGNAL(triggered()), this, SLOT(actionShowHelp()));
    mnHelp->addAction(showHelp);
    //-------------------------------------------------------------------//
    menuBar()->addMenu(mnTheory); // Р”РѕР±Р°РІР»СЏРµРј РїСѓРЅРєС‚С‹ РјРµРЅСЋ РІ menuBar, С‚.Рµ. С‚Рµ, РєРѕС‚РѕСЂС‹Рµ Р±СѓРґСѓС‚ РѕС‚РѕР±СЂР°Р¶Р°С‚СЊСЃСЏ РІ РіР». РѕРєРЅРµ
    menuBar()->addMenu(mnDemo);
    menuBar()->addMenu(mnTest);
    menuBar()->addMenu(mnHelp);

}
