#include "tok.h"



tok::tok() {}

tok::tok(QString val1,QString type1)
{
    val= val1;
    type = type1;
}
tok::tok(QString val1,int type1)
{
    val= val1;
    type = types[type1];
    typeNum = type1;
}
void tok::setTokPar(QString val1,QString type1)
{
    val= val1;
    type = type1;

}

void tok::setTokPar(QString val1,int type1)
{
    val= val1;
    type = types[type1];
    typeNum = type1;
}

QString tok::getVal()
{
    return val;
}

QString tok::getType()
{
    return type;
}
int tok::getTypeNum()
{
    return typeNum;
}
void tok::setTermType(bool isTerm1,int type1)
{
    isTerm= isTerm1;
    termType = termTypes[type1];
    typeNum = type1;

}
void tok::setTermType(bool isTerm1)
{
    isTerm= isTerm1;
}
