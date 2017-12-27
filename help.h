#ifndef HELP_H
#define HELP_H

#include <QMainWindow>
#include "theory.h"

namespace Ui {
class Help;
}

class Help : public Theory
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = 0);
    ~Help();

private:
    Ui::Help *ui;
};

#endif // HELP_H
