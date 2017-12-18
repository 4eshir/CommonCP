#ifndef TEST_H
#define TEST_H

#include "basewindow.h"
#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QStringList>
#include <QLabel>

namespace Ui {
class Test;
}

class Test : public BaseWindow
{
    Q_OBJECT
    QListWidget *allTopics;     // поле содержащее все темы
    QListWidget *usedTopics;     // поле содержащее темы используемые в тестировании
    QLineEdit *simple;            // количество вопросов простой сложности
    QLineEdit *basic;             // количество вопросов базовой сложности
    QLineEdit *high;             // количество вопросов высокой сложности
    QLineEdit *elaboration;     // для ввода времени или количества не правильных ответов
    QComboBox *endOfTest;     // способ окончания тестирования
    QLabel *notification;       // для вывода предупреждений

public:
    explicit Test(QWidget *parent = 0);
    Test(bool c);
    ~Test();

private slots:
    void Start();       // создание формы окна с виджетами
    void Go_On();       // переход к тестированию
    void Add();         // добавление темы тестирования в используемые
    void Remove();      // уборка темы тестирования из используемых
    void Record();      // запись настроек в файл
    void ChekColor();   // подсвечивание текста в полях
    QStringList listFilesInDir(QString path);

private:
    bool choose = true;
};

#endif // TEST_H
