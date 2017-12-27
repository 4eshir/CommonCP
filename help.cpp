#include "help.h"

Help::Help(QWidget *parent) :
    Theory(parent)
{
    setWindowTitle("Справка");
    pathToRead = "helpDocs";
    hierarchyOfTheory->clear();
    nameList.clear();
    this->resize(750, 450);
    hierarchyOfTheory->addItems(listFilesInDir("helpDocs"));
    this->menuBar()->close();
}

Help::~Help()
{
    delete ui;
}
