#include "theory.h"

#include "basewindow.h"
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>

Theory::Theory(QWidget *parent) :
    BaseWindow(parent)
{
    setWindowTitle("Теория");
    pathToRead = "theoryFiles";
    resize(1024, 768);
    createWidgets();
    refreshList = new QAction("Обновить список глав", this);
    connect(refreshList, SIGNAL(triggered()), this, SLOT(actionRefreshList()));
    mnTheory->addAction(refreshList);
}

Theory::Theory(size_t numb)
{
    resize(1024, 768);
    createWidgets();
    refreshList = new QAction("Обновить список глав", this);
    connect(refreshList, SIGNAL(triggered()), this, SLOT(actionRefreshList()));
    mnTheory->addAction(refreshList);
    switch (numb)
    {
        case 1:
            setTextFromFile("4. Разбор задач - Поиск подстроки в строке");
            break;
        case 2:
            setTextFromFile("5. Разбор задач - Умножение матриц");
            break;
        case 3:
            setTextFromFile("6. Разбор задач - Задача о рюкзаке");
            break;
    }
}

Theory::~Theory()
{
    //dtor
}

void Theory::actionRefreshList()
{
    nameList.clear();
    hierarchyOfTheory->clear();
    hierarchyOfTheory->addItems(listFilesInDir("theoryFiles"));
}

void Theory::setTextFromFile(QString str)
{
    QFile tempFile("theoryFiles\\" + str + ".html");
    tempFile.open(QIODevice::ReadOnly);
    QString textFromFile = tempFile.readAll();
    tempFile.close();
    fieldOfText->setText(textFromFile);
}

void Theory::onListItemClicked(QListWidgetItem* item)
{
    QFile tempFile(pathToRead + "\\" + item->text() + ".html");
    tempFile.open(QIODevice::ReadOnly);
    QString textFromFile = tempFile.readAll();
    tempFile.close();
    fieldOfText->setText(textFromFile);
}

void Theory::anchorClickedAction(const QUrl & link)
{
    size_t i = 0;
    QString anchor = link.toString();
    while (anchor[i] != '#') ++i;
    anchor.remove(0, i + 1);
    QFile tempFile("theoryFiles\\Словарь.html");
    tempFile.open(QIODevice::ReadOnly);
    QString tempStrSearhcing = tempFile.readLine();

    do
    {
        tempStrSearhcing = tempFile.readLine();
        tempStrSearhcing.remove(tempStrSearhcing.size() - 2, tempStrSearhcing.size());
    }while (tempStrSearhcing != anchor && !tempFile.atEnd());
    tempFile.readLine();
    tempFile.readLine();
    QString term = "";
    while (tempStrSearhcing[0] != '<')
    {
        tempStrSearhcing = tempFile.readLine();
        if (tempStrSearhcing[0] != '<')
            term += tempStrSearhcing;
    }
    QMessageBox definition;
    definition.setWindowTitle(anchor);
    definition.setText(term);
    definition.exec();
}

void Theory::createWidgets()
{
    QWidget *mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    QVBoxLayout *mainField = new QVBoxLayout(this);

    QHBoxLayout *textAndTree = new QHBoxLayout(this);
    hierarchyOfTheory = new QListWidget(this);
    fieldOfText = new QTextBrowser(this);

    textAndTree->addWidget(hierarchyOfTheory, 1);
    textAndTree->addWidget(fieldOfText, 4);

    mainField->addLayout(textAndTree);
    mainWidget->setLayout(mainField);

    QSplitter *split = new QSplitter(this);
    split->addWidget(hierarchyOfTheory);
    split->addWidget(fieldOfText);
    split->setStretchFactor(0, 1);
    split->setStretchFactor(1, 4);

    textAndTree->addWidget(split);

    connect(hierarchyOfTheory, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onListItemClicked(QListWidgetItem*)));
    connect(fieldOfText, SIGNAL(anchorClicked(QUrl)), this, SLOT(anchorClickedAction(const QUrl&)));
    hierarchyOfTheory->addItems(listFilesInDir("theoryFiles"));
}

QStringList Theory::listFilesInDir(QString path)
{
    QDir dir(path);
    QString tempName;
    bool ok = dir.exists();
    if (ok)
    {
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Name);
        QFileInfoList list = dir.entryInfoList();

        for (size_t i = 0; i != list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            tempName = fileInfo.fileName();
            tempName.remove(tempName.size() - 5, tempName.size());
            if (tempName != "Словарь")
                nameList.append(tempName);
        }
    }
    return nameList;
}

