#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <QMenuBar>

namespace Ui {
class BaseWindow;
}

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaseWindow(QWidget *parent = 0);
    ~BaseWindow();
    void createMenus();
    QMenu *mnTheory;
    QMenu *mnDemo;
    QMenu *mnTest;
    QMenu *mnHelp;
    QAction *showTheory;
    QAction *refreshList;
    QAction *startDemo;
    QAction *startTrainTest;
    QAction *startControlTest;
    QAction *showHelp;


public slots:
    void actionShowTheory();
    void actionShowHelp();
    void actionStartDemo();
    void actionStartTrainTest();
    void actionStartControlTest();

};

#endif // BASEWINDOW_H
