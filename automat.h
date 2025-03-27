#ifndef AUTOMAT_H
#define AUTOMAT_H

#include "tok.h"
#include <stack>

class Automat
{
    int state;
    int tab;

    QString I1 = "qertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789/<=>.;-: ";
    QString I2 = "qertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM/<=>;: ";
    QString I3 = "qertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    QString O = "<=>";
    QString N1 = "1234567890";
    QString N2 = "1234567890.";
    QString N4 = "1234567890e";
    QString N5 = "1234567890";

    std::vector<int> gr1 = {0,1,2,3,4,1,5,3,7};
    std::vector<int> gr2 = {0,1,2,3,4,1,5,3,6,1,5,3,7};

public:
    Automat();
    std::stack<tok> analize(std::vector<tok> LexList);
    std::vector<tok> analize1(QString text);
    std::stack<tok> analize2(std::vector<tok> LexList);

    bool isId(QString text);
    bool isDig(QString text);
    std::vector<QString> div(QString text);
    std::vector<tok> getCom(QString text);
    std::vector<tok> termAn(std::vector<tok> LexList);
    QString removeCom(QString text);
    int getState();
    QString findStr(int start,QString text, QString sym);
    QString findStr(int start,QString text, QString sym1, QString sym2, QString sym3);

};

#endif // AUTOMAT_H
