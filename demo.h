#ifndef DEMO_H
#define DEMO_H

#include "basewindow.h"
#include <QPushButton>
#include <QLabel>
#include "task1view.h"
#include "task2view.h"
#include "task3view.h"

class Demo : public BaseWindow
{
    Q_OBJECT
public:
    enum buttonCount {value = 3,}; //Число кнопок с примерами
    enum startSizes {width = 800, height = 600}; //Размеры главного окна
    explicit Demo(QWidget *parent = 0);
    ~Demo();
private slots:
    void action_Task1ButtonClicked();
    void action_Task2ButtonClicked();
    void action_Task3ButtonClicked();
private:
    QLabel* label;
    QPushButton* buttonTask1;
    QPushButton* buttonTask2;
    QPushButton* buttonTask3;
};

#endif // DEMO_H
