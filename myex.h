#ifndef MYEX_H
#define MYEX_H
 #include <QException>


class myex : public QException
{
public:

    QString err;
    int pos;
    myex(QString err1,int  pos1);
    myex(int pos1);
    myex();
    void setPos(int pos1);
    int getPos();
};

#endif // MYEX_H
