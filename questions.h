#ifndef QUESTIONS_H
#define QUESTIONS_H
#include <QTextBrowser>

#include "basewindow.h"
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QVector>
#include <QString>
#include <QPushButton>

namespace Ui {
class Questions;
}

class Questions : public BaseWindow
{
    Q_OBJECT
    QTextBrowser *text;     // поле содержаещее задание и варианты ответа
    QLabel *info;           // содержит номер вопроса
    QLineEdit *answer;      // поле для ввода ответа


public:
    explicit Questions(QWidget *parent = 0);
    ~Questions();

private slots:
    void Start();       // создание стартового окна с виджетами
    void Read();        // считывание файла с настройками
    void Filling(QString name, QVector < QVector <QString> > &matrix, int &separator1, int &separator2);    // считывание из файла
    void Sample(QVector < QVector <QString> > matrix, int from, int befor, int value);        // генерация теста
    void Create(QVector<QString> topics, int simple, int basic, int hight);      // создание тестириования
    void Back();        // переход к предыдущему заданию или выход из теста
    void Go_On();       // переход к следующему заданию или завершения теста
    void Output();      // вывод задания на экран
    void Result(bool go_out);      // вывод результата тестирования
    void Result();
    void Intermediate();            // подсчёт промежуточного результата
    void Chek();        // быстрая проверка на правильность ответа
    void Totals();                  // глобальный подсчёт резульатов (с баллами)
    void ChekForCompletion();          // проверка на завершение
    bool Substring(int value, int number);

private:
    QPushButton *back;
};

#endif // QUESTIONS_H
