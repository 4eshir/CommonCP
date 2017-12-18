#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include "basewindow.h"
#include <QMainWindow>
#include <QLineEdit>

namespace Ui {
class Identification;
}

class Identification : public BaseWindow
{
    Q_OBJECT
    QLineEdit *surname;     // поле для ввода фамилии
    QLineEdit *name;       // поле для ввода имени
    QLineEdit *group;     // поле для ввода группы

public:
    explicit Identification(QWidget *parent = 0);
    ~Identification();

private slots:
    void Start();       // создание формы окна с виджетами
    void Go();          //  переход к тестированию при заполнении всех полей

private:
    Ui::Identification *ui;
};

#endif // IDENTIFICATION_H
