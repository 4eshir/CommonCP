#include "basewindow.h"
#include "test.h"
#include "questions.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QFile>
#include <QListWidget>
#include <QDir>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

Test::Test(QWidget *parent) :
    BaseWindow(parent)
{

}

Test::Test(bool c)
{
    resize(1024, 768);      // стартовые размеры окна
    Start();
    choose = c;
}

Test::~Test()
{
}

QStringList Test::listFilesInDir(QString path)
{
    // создание списка имеющихся тем в файле
    QStringList nameList;
    QDir dir(path);
    QString tempName;
    bool ok = dir.exists();
    if (ok)
    {
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Name);
        QFileInfoList list = dir.entryInfoList();
        // пока не закончились файлы считываем название и доавляем в список
        for (size_t i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            tempName = fileInfo.fileName();
            tempName.remove(tempName.size() - 4, tempName.size());
            nameList.append(tempName);
        }
    }
    return nameList;
}

void Test::Start()
{
    // функция добавляет виджеты на экран
    QWidget *mainWidget = new QWidget();

    // слои для горизонтального и вертикального расположения виджетов
    QVBoxLayout *warp = new QVBoxLayout(this);              // общий
    QHBoxLayout *labels = new QHBoxLayout();                // для обозначения лист виджетов
    QHBoxLayout *addition = new QHBoxLayout();              // для лист виджетов
    QHBoxLayout *addition_widget = new QHBoxLayout();       // для двух слоёв ниже
    QVBoxLayout *question = new QVBoxLayout();              // для количества вопросов
    QVBoxLayout *end_test = new QVBoxLayout();              // для способа окончания теста
    QVBoxLayout *list_button = new QVBoxLayout();           // для кнопок межде лист виджетами

    // лейбл для обозначения действия выполняемого в данном окне
    QLabel *choice = new QLabel ("<font size = 5><center> Настройки обучающего режима тестирования </font>", this);
    choice->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QLabel *available = new QLabel ("<font size = 4><center>Доступные темы</font>", this);
    available->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QLabel *necessary = new QLabel ("<font size = 4><center>Используемые для учебного тестирования</font>", this);
    necessary->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    notification = new QLabel();
    notification->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // первый лист виджет содержит все имеющиеся темы, второй - те которые будут использоваться в тестировании
    allTopics = new QListWidget();
    allTopics->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    allTopics->addItems(listFilesInDir("TestingTopics"));
    usedTopics = new QListWidget();
    usedTopics->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // кнопка для добавления темы в тестирование
    QPushButton *add = new QPushButton("->", this);
    add->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(add, SIGNAL(clicked()), this, SLOT(Add()));

    // кнопка для удаления темы из тестирования
    QPushButton *remove = new QPushButton("<-", this);
    remove->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(remove, SIGNAL(clicked()), this, SLOT(Remove()));

    // поля для ввода количества вопросов в каждом из 3 уровней сложности
    simple = new QLineEdit(this);
    simple->setPlaceholderText(QApplication::translate("Form", "Количество простых вопросов", 0));
    simple->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    basic = new QLineEdit(this);
    basic->setPlaceholderText(QApplication::translate("Form", "Количество базовых вопросов", 0));
    basic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    high = new QLineEdit(this);
    high->setPlaceholderText(QApplication::translate("Form", "Количество сложных вопросов", 0));
    high->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // виджеты для выбора способа окончания тестирования
    QLabel *end = new QLabel ("Выберите способ завершения тестирования", this);
    end->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    elaboration = new QLineEdit(this);
    elaboration->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    elaboration->setVisible(false);

    endOfTest = new QComboBox();
    endOfTest->addItem("На все вопросы дан ответ");
    endOfTest->addItem("Закончилось время тестирования");
    endOfTest->addItem("Сделано k ошибок в ответах");
    endOfTest->addItem("Доля неверных ответов превзошла 0 < D < 1");

    // кнопка для перехода к началу тестирвоания
    QPushButton *next = new QPushButton("Вперёд", this);
    next->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(next, SIGNAL(clicked()), this, SLOT(Go_On()));

    // добавления виджетов на cлои для их отображения
    labels->addWidget(available, 4);
    labels->addStretch(1);
    labels->addWidget(necessary, 4);

    list_button->addStretch(2);
    list_button->addWidget(add, 1);
    list_button->addWidget(remove, 1);
    list_button->addStretch(2);

    addition->addWidget(allTopics, 4);
    addition->addLayout(list_button, 1);
    addition->addWidget(usedTopics, 4);

    question->addWidget(simple);
    question->addWidget(basic);
    question->addWidget(high);

    end_test->addWidget(end);
    end_test->addWidget(endOfTest);
    end_test->addWidget(elaboration);

    addition_widget->addLayout(question, 1);
    addition_widget->addStretch(1);
    addition_widget->addLayout(end_test, 1);

    warp->addWidget(choice, 1);
    warp->addLayout(labels, 1);
    warp->addLayout(addition, 6);
    warp->addWidget(notification, 1);
    warp->addLayout(addition_widget, 2);
    warp->addStretch(1);
    warp->addWidget(next, 1);
    mainWidget->setLayout(warp);
    setCentralWidget(mainWidget);
}

void Test::Add()
{
    // добавление темы из не используемых в используемые
    if (allTopics->currentRow() >= 0) // если выделен элемент
    {
        QStringList nameList;
        QString tempName = allTopics->item(allTopics->currentRow())->text();
        nameList.append(tempName);
        usedTopics->addItems(nameList);
        if( QListWidgetItem* item = allTopics->takeItem(allTopics->currentRow()) )
        {
            delete item;
        }
    }
    ChekColor();
}

void Test::Remove()
{
    // удаление темы из используемых в тесте и возвращение её в левую сторону, не используемых
    if (usedTopics->currentRow() >= 0)
    {
        QStringList nameList;
        QString tempName = usedTopics->item(usedTopics->currentRow())->text();
        nameList.append(tempName);
        allTopics->addItems(nameList);
        if( QListWidgetItem* item = usedTopics->takeItem(usedTopics->currentRow()) )
        {
            delete item;
        }
    }
}

bool completeness = false;      // необходимо для достоверности, что все данные правильны и могут быть записанны в файл

void Test::Record()
{
    // функция для записи данных в файл настройки учебного тестирования

    QFile file("training settings.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream writen(&file);
    writen.setCodec("UTF8");

    // cначала записываем темы
    for (int i = 0; i != usedTopics->count(); i++)
    {
        writen << "#" + usedTopics->item(i)->text() + "\r\n";
    }

    // затем запишем количество вопросов в каждом уровне сложности
    writen << "?" + simple->text() + "\r\n";
    writen << "?" + basic->text() + "\r\n";
    writen << "?" + high->text() + "\r\n";

    // способ окончания
    QString temp;
    switch (endOfTest->currentIndex()) {
    case 0:
        temp = "all";
        break;
    case 1:
        temp = "time\r\n*" + elaboration->text();
        break;
    case 2:
        temp = "error\r\n*" + elaboration->text();
        break;
    case 3:
        temp = "portion";
        break;
    default:
        break;
    }
    writen << "!" + temp;
    file.close();
}

void Test::Go_On()
{
    // кнопка для перехода к началу тестирвоания
    int just = simple->text().toInt();
    int average = basic->text().toInt();
    int hard = basic->text().toInt();
    int temp;
    if ((just >= 0 && just <= 5) && (average >= 0 && average <= 5) && (hard >= 0 && hard <= 5))
    {
        if (endOfTest->currentIndex() == 0 || endOfTest->currentIndex() == 3) // если выбрано окончание теста при достижении всех правильных или доли
        {
            if (usedTopics->count() > 0)
               completeness = true;
        }
        else if (endOfTest->currentIndex() == 1)     // если выбрано окончание тестирование по времени, отобразить и считать поле для количества минут
        {
            elaboration->setPlaceholderText(QApplication::translate("Form", "Введите время в минутах", 0));
            elaboration->setVisible(true);
            temp = elaboration->text().toInt();
            if (temp >= 5 && usedTopics->count() > 0 && temp <= 90)
                completeness = true;
        }
        else    // если выбрано окончание после k ошибок, отобразить и считать поле для количества ошибок
        {
            elaboration->setPlaceholderText(QApplication::translate("Form", "Введите k", 0));
            elaboration->setVisible(true);
            temp = elaboration->text().toInt();
            if (temp >= 0 && usedTopics->count() > 0 && temp <= (just + average + hard))
                completeness = true;
        }

        if (completeness)       // если все данные правильные можно их записывать в файл и перейти к тестированию
        {
            Record();           // запишем данные для учебного тестирования
            Questions *window = new Questions(choose);
            window->show();
            this->close();
        }
    }

    ChekColor();
}

void Test::ChekColor()
{
    QPalette change = simple->palette();
    if (simple->text() == "" || simple->text().toInt() > 5)
    {
        // при отутствии символов внутренни текст с просьбой ввести количество простых вопросов становится красным
        change.setColor(QPalette::Text, Qt::red);
    }
    else
        change.setColor(QPalette::Text, Qt::black);      // а если что-то есть, чёрный (это нужно в случае если уже меняли цвет на красный)
    simple->setPalette(change);
    change = basic->palette();
    if (basic->text() == "" || basic->text().toInt() > 5)
    {
        // при отутствии символов текст с просьбой ввести количество базовых вопросов становится красным
        change.setColor(QPalette::Text, Qt::red);
    }
    else
        change.setColor(QPalette::Text, Qt::black);      // а если что-то есть, чёрный (это нужно в случае если уже меняли цвет на красный)
    basic->setPalette(change);
    change = high->palette();
    if (high->text() == "" || high->text().toInt() > 5)
    {
        // при отутствии символов текст с просьбой ввести количество сложных вопросов становится красным
        change.setColor(QPalette::Text, Qt::red);
    }
    else
        change.setColor(QPalette::Text, Qt::black);      // а если что-то есть, чёрный (это нужно в случае если уже меняли цвет на красный)
    high->setPalette(change);
    change = elaboration->palette();
    if (elaboration->text() == "")
    {
        // при отутствии символов текст с просьбой ввести количество минут или ошибок становится красным
        change.setColor(QPalette::Text, Qt::red);
    }
    else
        change.setColor(QPalette::Text, Qt::black);      // а если что-то есть, чёрный (это нужно в случае если уже меняли цвет на красный)
    elaboration->setPalette(change);
    // если нет темы, то всё поле становится красным, иначе - обычное, белое
    QPalette color = usedTopics->palette();
    if (usedTopics->count() > 0)
    {
        color.setColor(QPalette::Base, Qt::white);
    }
    else
        color.setColor(QPalette::Base, Qt::red);
    usedTopics->setPalette(color);
    notification->setText("<font size = 4><center>Должны быть заполненны все поля, при этом количество вопросов в каждом из вариантов сложности не может быть больше 5</font>");
    if (endOfTest->currentIndex() == 1 || endOfTest->currentIndex() == 2) // если выбрано окончание теста по времени или количеству ошибок
    {
        elaboration->setVisible(true);
        if (endOfTest->currentIndex() == 1)
        {
            elaboration->setPlaceholderText(QApplication::translate("Form", "Введите время в минутах", 0));
        }
        else
            elaboration->setPlaceholderText(QApplication::translate("Form", "Введите k", 0));
    }
}
