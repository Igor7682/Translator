#ifndef TOK_H
#define TOK_H

#include <QApplication>



class tok
{
    QString val;
    QString type;
    int typeNum;
    bool isTerm;
    QString termType;
    std::vector<QString> termTypes = {"Left","Right"};
    std::vector<QString> types = {"Оператор if","Идентификатор","Оператор сравнения","Число",
                                  "Оператор then","Оператор присваивания","Оператор else",
                                  "Индикатор конца выражения","Комментарий"};
    //   012341537
    //   0123415361537
public:
    tok();
    tok(QString val1,QString type1);
    tok(QString val1,int type1);
    void setTokPar(QString val1,QString type1);
    void setTokPar(QString val1,int type1);
    void setTermType(bool isTerm1,int type1);
    void setTermType(bool isTerm);
    QString getVal();
    QString getType();
    int getTypeNum();
};

#endif // TOK_H
