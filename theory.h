#ifndef THEORY_H
#define THEORY_H

#include "basewindow.h"
#include <QMainWindow>
#include <QListWidget>
#include <QTextBrowser>

namespace Ui {
class Theory;
}

class Theory : public BaseWindow
{
    Q_OBJECT

public:
    explicit Theory(QWidget *parent = 0);
    QStringList listFilesInDir(QString path);
    Theory(size_t numb);
    ~Theory();

    QString pathToRead;
    QStringList nameList;
    QListWidget *hierarchyOfTheory;
    QTextBrowser *fieldOfText;


public slots:
    void onListItemClicked(QListWidgetItem*);
    void anchorClickedAction(const QUrl&);
    void actionRefreshList();

private:
    void createWidgets();

    void setTextFromFile(QString str);
    //void keyPressEvent(QKeyEvent *event);

};

#endif // THEORY_H
