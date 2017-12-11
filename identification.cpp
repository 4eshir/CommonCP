#include "basewindow.h"
#include "identification.h"
#include "questions.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QPalette>

Identification::Identification(QWidget *parent) :
    BaseWindow(parent)
{
    resize(1024, 768);      // стартовые размеры окна
    Start();
}

Identification::~Identification()
{
    delete ui;
}

void Identification::Start()
{
    // функция добавляет виджеты на экран
    QWidget *mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    QVBoxLayout *basis = new QVBoxLayout(this);     // основной листовый слой

    QLabel *info = new QLabel ("<font size = 7><center>Перед началом тестирования необходимо ввести данные</font>", this);
    info->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // ниже поля для ввода ФИ и группы
    surname = new QLineEdit(this);
    surname->setPlaceholderText(QApplication::translate("Form", "Введите Фамилию", 0));
    surname->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    name = new QLineEdit(this);
    name->setPlaceholderText(QApplication::translate("Form", "Введите Имя", 0));
    name->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    group = new QLineEdit(this);
    group->setPlaceholderText(QApplication::translate("Form", "Введите группу", 0));
    group->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // добавление кнопки для сохранения идентификационных данных
    QPushButton *go = new QPushButton("Начать", this);
    go->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(go, SIGNAL(clicked()), this, SLOT(Go()));

    // добавление виджетов на лист, для отображения
    basis->addWidget(info);
    basis->addWidget(surname);
    basis->addWidget(name);
    basis->addWidget(group);
    basis->addWidget(go);
    mainWidget->setLayout(basis);
}

void Identification::Go()
{
    // если поля для ввода не пустые
    if (surname->text() != "" && name->text() != "" && group->text() != "")
    {
        QFile result("result.txt");
        result.open(QIODevice::Append);     // открываем на дозапись
        // возвращает системные данные даты и времени
        QDateTime *my_date = new QDateTime(QDateTime::currentDateTime());
        QTextStream writen(&result);
        writen << "\r\n \r\n" << my_date->toString("dd/MM/yy HH:mm") << "\r\n";      // записываем время
        // записываем ФИ и группу
        writen << " " + surname->text() + " " + name->text() + " " + group->text() + "\r\n";
        result.close();

        // после записи данных переходим к тестированию
        Questions *window = new Questions();
        window->show();
        this->close();
    }

    if (surname->text() == "")
    {
        // при отутствии символов внутренни текст с просьбой ввести фамилию становится красным
        QPalette red = surname->palette();
        red.setColor(QPalette::Text, Qt::red);
        surname->setPalette(red);
    }

    if (name->text() == "")
    {
        // при отутствии символов внутренни текст с просьбой ввести имя становится красным
        QPalette red = name->palette();
        red.setColor(QPalette::Text, Qt::red);
        name->setPalette(red);
    }

    if (group->text() == "")
    {
        // при отутствии символов внутренни текст с просьбой ввести группу становится красным
        QPalette red = group->palette();
        red.setColor(QPalette::Text, Qt::red);
        group->setPalette(red);
    }
}
