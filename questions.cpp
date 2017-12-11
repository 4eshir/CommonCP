#include "basewindow.h"
#include "questions.h"
#include "test.h"
#include "identification.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextBrowser>
#include <QLineEdit>
#include <QFile>
#include <QTimer>
#include <QVector>
#include <QString>
#include <QTime>
#include <QTextStream>
#include <QDebug>

Questions::Questions(QWidget *parent) :
    BaseWindow(parent)
{
    resize(1024, 768);      // стартовые размеры окна
    Start();
}

Questions::~Questions()
{
}
                                // если all = true, то значит прекращаем тест когда все ответы правильные
bool all = true;                // если error = true, то прекращаем тестирование по достижению некоторого количества ошибок
bool error = false;             // если и all и error = true, то прекращаем тестирование в соответствии с 0 < D < 1
                                // если и all и error = false, то тестирование прекращается по истечению времени

void Questions::Start()
{
    // функция добавляет виджеты на экран
    QWidget *mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    // листы для горизонтального и вертикального расположения виджетов
    QVBoxLayout *base = new QVBoxLayout(this);
    QHBoxLayout *buttons = new QHBoxLayout();

    // лейбл для отображения номера задания
    info = new QLabel ("<center>№ вопроса из n вопросов", this);
    info->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // текстовый браузер для отображения задания и вариантов ответов
    text = new QTextBrowser();
    text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // поле для ввода ответа
    answer = new QLineEdit(this);
    answer->setPlaceholderText(QApplication::translate("Form", "Введите свой ответ", 0));
    answer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // ниже две кнопки для перехода по заданиям
    back = new QPushButton("Назад", this);
    back->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(back, SIGNAL(clicked()), this, SLOT(Back()));

    QPushButton *next = new QPushButton("Вперёд", this);
    next->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(next, SIGNAL(clicked()), this, SLOT(Go_On()));

    // добавление виджетов в горизонтальном положении
    buttons->addWidget(back, 1, Qt::AlignLeft);
    buttons->addWidget(next, 0, Qt::AlignRight);

    // добавление виджетов в вертикальном положении
    base->addWidget(info, 1);
    base->addStretch(1);
    base->addWidget(text, 6);
    base->addStretch(1);
    base->addWidget(answer, 1);
    base->addStretch(1);
    base->addLayout(buttons, 1);
    mainWidget->setLayout(base);

    Read();         // считем и создадим тест
    Output();       // выведем первое задание
}

int Number = 0, Quantity;                               // Number для обозначния номера задания, Quantity для обозначения всего количества заданий
bool training = true;                                   // для обозначения типа тестирования, и знания нужен ли нам словарь
QVector < QVector <QString> > task;                    // тут мы хроним весь наш тест (от темы, до ответов)
QVector <QString> reply;                   // для хранения ответов пользователя
QVector <bool> action;                                  // для быстрого подсчёта (необходимо для прекращения теста при all, error, portion
int fail = 0;                                               // для хранения количества неправильных ответов

void Questions::Read()
{
    // функция чтения настроечного файла

    // открываем файл с настройками
    QFile file ("training settings.txt");
    file.open(QIODevice::ReadOnly);
    if (!file.exists())     // если нет учебного файла, то используем контрольный тест
    {
        file.close();
        file.setFileName("control settings.txt");
        training = false;           // отмечаем что это контрольный тест и мы не можем использовать словарь
        file.open(QIODevice::ReadOnly);
    }

    // считываем всё нужное и запоминаем
    QString temp;
    QVector <QString> topics;
    int simple = -1, basic = -1, hight = -1;
    while (!file.atEnd())
    {
        temp = file.readLine();             // считываем строку
        temp = temp.simplified();       // стёрли символ переноса строки
        if (temp[0] == '#')                 // записываем темы в вектор строк
        {
            temp.remove(0, 1);
            topics.push_back(temp);
        }
        else if (temp[0] == '?')           // распределяем вопросы
        {
            temp.remove(0, 1);
            if (simple < 0)
                simple = temp.toInt();
            else if (basic < 0)
                basic = temp.toInt();
            else
                hight = temp.toInt();
        }
        else if (temp[0] == '!')            // записываем способ окончания тестирования
        {
            temp.remove(0, 1);
            if (temp == "time" || temp == "error")
            {
                all = false;
            }
            if (temp == "portion" || temp == "error")
            {
                error = true;
            }
        }
        else if (temp[0] == '*')           // считывание дополнительного поле для прекращения тестирование
        {
            temp.remove(0, 1);
            if (!all && !error)
            {
                // запускаем таймер на тестирование
                QTimer::singleShot(temp.toInt() * 60 * 1000, this, SLOT(Result()));
            }
            if (!all && error)
            {
                fail = temp.toInt();
            }
        }
    }
    file.close();
    Quantity = simple + basic + hight;
    Create(topics, simple, basic, hight);
}

void Questions::Output()
{
    // вывод задания и вариантов ответа, а так же изменение лейбла с номером вопроса
    answer->setVisible(true);
    QString temp = QString::number(Number + 1) + " вопрос из " + QString::number(Quantity);
    info->setText("<center><font size = 5>" + temp + "</font>");
    int limit = task[Number].size();
    if (limit == 3)     // если это задание открытого типа, то важно не вывести ответ
        limit--;
    text->clear();      // стираем старый вопрос
    answer->clear();        // и введённый на него ответ
    text->append("<font size = 4>" + task[Number][0] + "</font>");      // выводим тему задания
    for (int i = 0; i < limit; i++)
    {
        temp = task[Number][i];
        if (i > 0)      // это варианты ответов
        {
            temp.remove(0, 1);              // затираем первый символ, который означет правильный ответ или нет
            text->append("<font size = 4>" + temp + "</font>");
        }
        text->append("\r\n");
    }
}

void Questions::Filling(QString name, QVector < QVector <QString> > &matrix, int &separator1, int &separator2)
{
    // функция считывает все вопросы в файле одной темы
    name = name.simplified();       // удаление разрыва строки (автоматически добавляющегося \r\n)
    QFile question("TestingTopics\\" + name + ".txt");
    question.open(QIODevice::ReadOnly);
    QString temp;                   // для считывания из файла
    QVector <QString> column;

    while (!question.atEnd())            // считываем весь файл и временно сохраняем
    {
        temp = question.readLine();
        if (temp[0] == '#')     // если это текст вопроса запишем удалив символ обозначающий что это текст
        {
            temp.remove(0, 1);
            if (column.size() > 0)
            {
                matrix.push_back(column);        // добавили в матрицу столбец который содержит вопрос и варианты ответа
                column.clear();             // очистили вектор для следующего вопроса
            }
            if (separator1 == -1)           // перед вопросом запишем число равное максимальному количеству баллов которое можно получить за него
                temp.push_front(QString::number(1));
            else if (separator2 == -1)
                temp.push_front(QString::number(3));
            else
                temp.push_front(QString::number(5));
            column.push_back(name);     // добавили тему задания
            column.push_back(temp);     // добавили текст задания
        }
        else if (temp[0] == '+' || temp[0] == '-')      // если это ответ, то запишем как есть, чтобы удобно было проверять
        {
            column.push_back(temp);
        }
        else if (temp[0] == '=')      // это разделительный знак между уровнями задания
        {
            if (separator1 == -1)
            {
                separator1 = matrix.size() + 1;      // разделитель указывает число равное количеству простых вопросов
            }
            else
            {
                separator2 = matrix.size() + 1;      // разделитель указыввает число равное количеству простых и базовых вопросов
            }
        }
    }
    matrix.push_back(column);       // добавили последний считанный вопрос
    question.close();
}

void Questions::Sample(QVector < QVector <QString> > matrix, int from, int befor, int value)
{
    // выбор используемых вопросов для данного тестирования по имеющейся теме
    QTime midnight(0, 0, 0);                        // для рандома
    qsrand(midnight.secsTo(QTime::currentTime()));  // для рандома
    QVector <int> used_question;
    used_question.resize(befor - from);

    // генерируем номер задания без повторов
    for (int i = 0; i < used_question.size(); i++)
    {
        used_question[i] = i;
    }
    for (int i = 0, number; i < used_question.size(); i++)
    {
        number = qrand() % (befor - from);
        std::swap(used_question[i], used_question[number]);
    }

    for (int i = 0; i < value && i < befor; i++)
    {
        task.append(matrix[used_question[i] + from]);            // запишем задание в создаваемый тест
    }
}

void Questions::Create(QVector<QString> topics, int simple, int basic, int hight)
{
    // функция создания теста

    QVector < QVector <QString> > matrix;        // будем хранить временно весь файл

    int my_simple = (int)(simple / topics.size());           // приблизительное количество простых вопросов которое возьмём из одной темы
    int my_basic = (int)(basic / topics.size());            // приблизительное количество базовых вопросов из одной темы
    int my_hight = (int)(hight / topics.size());        // приблизительное количество сложных вопросов из одной темы

    int separator1 = -1, separator2 = -1;

    for (int i = 0; i < topics.size(); i++)
    {
        Filling(topics[i], matrix, separator1, separator2);
        if (separator2 == -1)
            separator2 = matrix.size();
        // запишем задания разной степени сложности
        Sample(matrix, 0, separator1, my_simple);
        Sample(matrix, separator1, separator2, my_basic);
        Sample(matrix, separator2, matrix.size(), my_hight);

        // очищаем временные элементы
        separator1 = separator2 = -1;
        matrix.clear();

        if (i == topics.size() - 1)     // если это последняя тема из используемых
        {
            my_simple = simple - my_simple * (i - 1);     // количество вопросов равно тому что осталось из имеющегося
            my_basic = basic - my_basic * (i - 1);
            my_hight = hight - my_hight * (i - 1);
        }
    }

    reply.resize(Quantity);     // резервируем область для ответов

    if (all || error)
    {
        action.resize(Quantity);    // резервируем область в булевом массиве для хранения правильности ответа
        for (int i = 0; i < Quantity; i++)
        {
            if ((all && !error) || (error && i % 2 == 0)) action[i] = false;
            if ((error && !all) || (error && all && i % 2 == 1)) action[i] = true;
        }
        if (all && error)   fail = Quantity;
    }
}

void Questions::Back()
{
    // переход к предыдущему вопросу или возможность выхода в главное меню
    Number--;
    if (Number >= 0 && Number < 10000)
    {
        info->setVisible(true);
        Output();
        answer->setText(reply[Number]);     // выводим ответ который пользователь дал на это задание
    }
    if (Number == -1)
    {
        info->setVisible(false);
        text->setText("<center><font size = 5> Если вы действительно хотите выйти из тестирования - нажмите повторно кнопку Назад. </font>");
        text->append("<center><font size = 5> При этом результаты будут аннулированы</font>");
        answer->setVisible(false);
    }
    if (Number == -2)
    {
        // тут можно сделать переход к учебной инфформации или демонстрации
    }
}

void Questions::Go_On()
{
    // переход к следующему вопросу или возможность закончить тестирование
    Number++;
    if (Number == 0)
    {
        info->setVisible(true);
        reply[Number] = answer->text();
        Output();
    }
    else if (Number <= Quantity)
    {
        info->setVisible(true);
        reply[Number - 1] = answer->text();      // запишим ответ на вопрос
        if (all || error)       // промежуточный подсчёт ответов в случае если тест не по времени проходит
        {
            Intermediate();
        }
        if (Number < Quantity)
             Output();      // выведем следующее задание
    }
    if (Number == Quantity)
    {
        info->setVisible(false);
        text->setText("<font size = 5><center> Если вы действительно хотите досрочно закончить тестирование и узнать свои результаты - нажмите кнопку Вперёд</font>");
        answer->setVisible(false);
    }
    if (Number == Quantity + 1)
    {
        Number += 10000;     // добавляем не реальное значение, чтобы заблокировать возможность возврата к заданиям
        Result(true);        // выведем результат
        back->setVisible(false);
    }
    else if (Number > 10000)
    {
         // тут можно сделать переход к учебной инфформации или демонстрации
    }
}

bool Questions::Substring(int value, int number)
{
    QString stroka = reply[number], symbol = QString::number(value);
    for (int i = 0; i < stroka.size(); i++)
    {
        if (stroka[i] == symbol[0])
            return true;
    }
    return false;
}

void Questions::Totals()
{
    // глобальный подсчёт резульатов (с баллами)
    QString stroka;
    float points = 0, maxpoints = 0;
    int correct = 0, wrong = 0, right = 0;  // correct и wrong - правильные и не правильные ответы в ответе, right количество всех правильных
    int temp;
    for (int i = 0; i < Quantity; i++)      // проверяем всё количество заданий
    {
        for (int k = 2; k < task[i].size(); k++)    // проеверяем все правильные ответы в задании
        {
            stroka = task[i][k];
            if (stroka[0] == '+')
            {
                right++;
                if (Substring(k - 1, i))
                    correct++;
            }
            else if (stroka[0] == '-' && Substring(k - 1, i))
                wrong++;
        }
        // выделим максимальное количество баллов за задание
        stroka = task[i][1];
        stroka.remove(1, stroka.size() - 1);
        temp = stroka.toInt();
        // приплюсуем ко всем остальным
        maxpoints += temp;
        // вычислим сколько начислим за задание исходя из колличества правильных и не правильных
        if (wrong == 0 && correct == right)     // если неправильных нет и все правильные - максимальное количество баллов
            points += temp;
        else if (wrong == 0 && correct < right && reply[i] != "")     // если неправильных нет и правильных меньше чем нужно
            points += temp * 0.75;
        else if (wrong < correct && correct >= (right / 2))     // если неправильных меньше чем правильных и правильных больше половины
            points += temp * 0.5;
        else if (correct != 0 && wrong <= (right / 2))  // если правильные вообще есть и неправильных меньше или равно половине всех правильных которые возможно
            points += temp * 0.25;
        wrong = correct = right = 0;        // очищаем переменные для проверки следующего вопроса-ответа
    }

    text->setText("<font size = 5><center>Ваш результат " + QString::number(points) + " баллов из " + QString::number(maxpoints) + " возможных</font>");
    if (points >= maxpoints * 0.8)
        text->append("<font size = 5><center>Отлично! Так держать)</font>");
    else if (points >= maxpoints * 0.7)
        text->append("<font size = 5><center>Вы хорошо знаете материал!</font>");
    else if (points >= maxpoints * 0.6)
        text->append("<font size = 5><center>Удовлетворительно!</font>");
    else
        text->append("<font size = 5><center>Неудовлетворительно! Вам стоит перечитать всю учебную информацию</font>");
}

void Questions::Result()
{
    // функция перенаправляет окончание теста по времени в вычисление результата
    Result(false);
    answer->setVisible(false);
    Number += 10000;
}

void Questions::Result(bool go_out)
{
    // функция проверяющая результат тестирования

    // код ниже изменяет лейбл сообщая о пречине завершения теста
    info->setVisible(true);
    if (!all && !error && !go_out)
    {
        info->setText("<center><font size = 6>Время вышло</font>");
    }
    else if (all && !go_out && !error)
    {
        info->setText("<center><font size = 6>Вы ответили на все вопросы правильно!</font>");
    }
    else if (error && !go_out && !all)
    {
        info->setText("<center><font size = 6>Превышенно количество ошибок!</font>");
    }
    else if (error && all && !go_out)
    {
        info->setText("<center><font size = 6>Доля неверных ответов превзошла допустимое значение!</font>");
    }
    else
    {
        info->setText("<center><font size = 6>Вы закончили тест досрочно</font>");
    }
    Totals();
    if (!training)      // если тест контрольный, то необходимо записать ответы пользователя
    {
        QFile result("result.txt");
        result.open(QIODevice::Append);     // открываем на дозапись
        QTextStream writen(&result);
        for (int i = 0; i < reply.size(); i ++)     // запишем все ответы
        {
            writen << reply[i] << "\r\n";
        }
        result.close();
    }
    else        // удаляем файл с настройками учебного тестирования
    {
        QFile file ("training settings.txt");
        file.remove();
    }
}

void Questions::Chek()
{
    // проверка на правильность ответа
    QString question;
    int wrong = 0;
    for (int k = 2; k < task[Number - 1].size(); k++)    // проеверяем все правильные ответы в задании
    {
        question = task[Number - 1][k];
        if (question[0] == '-' && Substring(k - 1, Number - 1))
            wrong++;
    }
    if (wrong == 0 && reply[Number - 1] != "")
        action[Number - 1] = true;
    else
        action[Number - 1] = false;
}

void Questions::ChekForCompletion()
{
    // проверка на завершение тестирования
    int errors = 0;
    for (int i = 0; i < action.size(); i++)
    {
        if (action[i] == false)
            errors++;
    }

    if ((errors >= fail && error) || (errors == 0 && all))
    {
        // завершим тестирование без вопроса о желании пользователя выйти
        Number+=10000;
        answer->setVisible(false);
        Result(false);
    }
}

void Questions::Intermediate()
{
    // подсчёт промежуточного результата
    Chek();     // подсчитаем сколько не правильных ответов
    ChekForCompletion();        // если их дорстаточно для выхода - вывод результаторв и завершение тестирования
}
