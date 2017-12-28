#include "totals.h"
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Totals::Totals()
{
    points = 0;
    maxpoints = 0;
}

Totals::~Totals()
{

}

void Totals::Total(int quant, bool training, QVector < QVector <QString> > task, QVector <QString> reply)
{
    // глобальный подсчёт резульатов (с баллами)
    QString stroka;
    int correct = 0, wrong = 0, right = 0;  // correct и wrong - правильные и не правильные ответы в ответе, right количество всех правильных
    int temp;

    for (int i = 0; i < quant; i++, wrong = correct = right = 0)      // проверяем всё количество заданий
    {
        for (int k = 2; k < task[i].size(); k++)    // проеверяем все правильные ответы в задании
        {
            stroka = task[i][k];
            if (stroka[0] == '+')
            {
                right++;
                if (Substring(k - 1, i, reply))
                    correct++;
            }
            else if (stroka[0] == '-' && Substring(k - 1, i, reply))
                wrong++;

        }
        // выделим максимальное количество баллов за задание
        stroka = task[i][1];
        stroka.remove(1, stroka.size() - 1);
        temp = stroka.toInt();
        qDebug() << wrong << correct << right << " wrong an ";
        // приплюсуем ко всем остальным
        maxpoints += temp;
        // вычислим сколько начислим за задание исходя из колличества правильных и не правильных
        if (wrong == 0 && correct == right)     // если неправильных нет и все правильные - максимальное количество баллов
            points += temp;
        else if (wrong == 0 && correct < right && correct != 0)     // если неправильных нет и правильных меньше чем нужно
            points += temp * 0.75;
        else if (wrong < correct && correct >= (right / 2))     // если неправильных меньше чем правильных и правильных больше половины
            points += temp * 0.5;
        else if (correct != 0 && wrong <= (right / 2))  // если правильные вообще есть и неправильных меньше или равно половине всех правильных которые возможно
            points += temp * 0.25;
        qDebug() << points << maxpoints;
    }
    Output(training, reply);

}

void Totals::Output(bool training, QVector <QString> reply)
{
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

bool Totals::Substring(int value, int number, QVector <QString> reply)
{
    // поиск подстроки
    QString stroka = reply[number], symbol = QString::number(value);
    qDebug() << stroka << symbol;
    for (int i = 0; i < stroka.size(); i++)
    {
        qDebug() << stroka[i] << symbol;
        if (stroka[i] == symbol[0])
            return true;
    }
    return false;
}
