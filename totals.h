#ifndef TOTALS_H
#define TOTALS_H

#include <QVector>
#include <QString>

class Totals
{
public:
    Totals();
    ~Totals();
    void Total(int quant, bool training, QVector < QVector <QString> > task, QVector <QString> reply);
    void Output(bool training, QVector <QString> reply);
    float points;
    float maxpoints;
private:
    bool Substring(int value, int number, QVector <QString> reply);
};

#endif // TOTALS_H
