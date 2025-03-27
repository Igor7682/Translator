#include "myex.h"

myex::myex(QString err1,int pos1)
{
    pos = pos1;
    err = err1;
}
myex::myex(int pos1)
{
    pos = pos1;

}
myex::myex()  {}

void myex::setPos(int pos1)
{
    pos = pos1;

}

int myex::getPos()
{
    return pos;
}
