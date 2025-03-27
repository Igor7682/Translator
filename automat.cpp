#include "automat.h"
#include "tok.h"
#include "ctype.h"
#include <stack>
#include "myex.h"
Automat::Automat()
{
    state = 0;
}


bool Automat::isId(QString text)
{
    int i = 0;
    while(i != text.length())
    {
        if(isalnum(text[i].toLatin1()) == false)
        {
            return false;
        }
        i++;
    }
    return true;
}

bool Automat::isDig(QString text)
{
    int i = 0;


    for(int i = 0;i<text.size();i++)
    {
        if(text[i].digitValue() == -1)
        {

            if((text[i] != "-" & text[i] != "e" & text[i] != "."))
            {
                return false;
            }else
            {
                if((text[i] == "-"))
                {
                    if(i == text.size() - 1)
                    {
                        return false;
                    }else
                    {
                        if((text[i + 1].digitValue() == -1))
                        {
                            return false;
                        }
                    }

                }

            }

        }

    }
    return true;
}


std::vector<tok> Automat::getCom(QString text)
{
    std::vector<tok> commList;
    QString commBuf;
    tok commTok;
    int j = 0;
    for(int i = 0;i<text.size();i++)
    {
        if(text[i]== "{" )
        {
            for( j = i;j<text.size();j++)
            {
                if(text[j]== "}" )
                {
                    commBuf = text.mid(i,j);
                    commBuf.remove("{");
                    commBuf.remove("}");
                    commTok.setTokPar(commBuf,"Comment");
                    commList.push_back(commTok);
                    break;
                }
                if(j == text.size())
                {
                    throw(std::exception());
                }

            }
            i = j;
        }

    }
    return commList;
}
QString Automat::removeCom(QString text)
{
    std::vector<QString> commList;
    QString commBuf = "";
    int j = 0;
    for(int i = 0;i<text.size();i++)
    {
        if(text[i]== "{" )
        {
            for( j = i;j<text.size();j++)
            {
                if(text[j]== "}" )
                {

                    text = text.remove(i,j);

                }

            }
            i = j;
        }

    }
    return text;
}

int Automat::getState()
{
    return state;
}


QString Automat::findStr(int start,QString text, QString sym)
{
    QString newText = "";

    for(int i = start;i<text.size();i++)
    {

        if(text[i] == sym | text[i] == ";" )
        {
            break;
        }
        newText += text[i];
    }
    if(newText.size() == 0)
    {
        newText =  ";";
    }

    return newText;
}

QString Automat::findStr(int start, QString text, QString sym1, QString sym2, QString sym3)
{
    QString newText = "";
    int i = start;

    for(int i = start;i<text.size();i++)
    {

        if(text[i] != sym1 & text[i] != sym2 & text[i] != sym3)
        {
            newText += text[i];

        }else
        {
            break;
        }
    }

    return newText;
}


std::vector<QString> Automat::div(QString text)
{
    std::vector<QString> textArr;
    QString buf = "";
    size_t prev = 0;
    size_t next;


    for(int i = 0; i < text.size(); i++)
    {
        if(i == text.size() - 1)
        {
            buf += text[i];
            textArr.push_back(buf);
            break;
        }
        if(text[i] == " ")
        {
            textArr.push_back(buf);
            buf = "";
        }
        else
        {
            buf += text[i];
        }
    }
    return textArr;
}


std::vector<tok> Automat::termAn(std::vector<tok> LexList)
{

    for(int i = 0;i<LexList.size();i++)
    {
        if(LexList[i].getType() == "Оператор if")
        {
            LexList[i].setTermType(true,1);
        }
        if(LexList[i].getType() == "Идентификатор")
        {
            LexList[i].setTermType(true,2);
        }
        if(LexList[i].getType() == "Оператор сравнения")
        {
            LexList[i].setTermType(false);
        }
        if(LexList[i].getType() == "Число")
        {
            LexList[i].setTermType(true,2);
        }
        if(LexList[i].getType() == "Оператор then")
        {
            LexList[i].setTermType(true,2);
        }
        if(LexList[i].getType() == "Оператор присваивания")
        {
            LexList[i].setTermType(true,2);
        }
        if(LexList[i].getType() == "Оператор else")
        {
            LexList[i].setTermType(true,2);
        }
        if(LexList[i].getType() == "Индикатор конца выражения")
        {
            LexList[i].setTermType(false);
        }
    }

    return LexList;
}


std::stack<tok> Automat::analize(std::vector<tok> LexList)
{
    std::stack<int> stateStack;
    std::stack<tok> lexStack;
    std::stack<tok> lexStack1;
    std::stack<tok> lexStack3;
    state = 0;
    bool g1 = true;
    bool g2 = true;


    for(int i = LexList.size() - 1;i >= 0;i--)
    {

        lexStack.push(LexList[i]);
        stateStack.push(LexList[i].getTypeNum());
        //state = 1;
    }
    lexStack1 =lexStack;
    lexStack3 =lexStack;
    for(int i = 0;i < gr1.size();i++)
    {
        QTextStream(stdout) << lexStack.top().getTypeNum() << "  " << gr1[i] << Qt::endl;
        if(gr1[i]!=lexStack.top().getTypeNum())
        {
            g1 = false;
            break;
        }
        if(lexStack.empty())
        {
            g1 = false;
            break;
        }
        lexStack.pop();
    }
    if(!g1)
    {
        for(int i = 0;i < gr2.size();i++)
        {
            QTextStream(stdout) << lexStack1.top().getTypeNum() << "  " << gr2[i] << Qt::endl;
            if(gr2[i]!=lexStack1.top().getTypeNum())
            {
                g2 = false;
                break;
            }
            if(lexStack1.empty())
            {
                g2 = false;
                break;
            }
            lexStack1.pop();
        }
    }
    if((g1 | g2) == true )
    {
        return lexStack3;
    } else
    {
        throw(std::exception());
    }


}

std::stack<tok> Automat::analize2(std::vector<tok> LexList)
{
    std::stack<int> stateStack;
    std::stack<tok> lexStack;
    std::stack<tok> lexStack1;
    std::stack<tok> lexStack3;
    state = 0;
    bool g1 = true;
    bool g2 = true;


    for(int i = LexList.size() - 1; i != 0; i--)
    {
        switch(state)
        {
        case 0:
            if(LexList[i].getTypeNum() == 0)
            {
                state = 1;
            } else
            {

            }

            break;
        case 1:

            break;

        }
    }




    return  lexStack;
}


std::vector<tok> Automat::analize1(QString text)
{
    int i = 0;
    tok t;
    QString buf;
    QString buf2;
    QString Commbuf;
    std::vector<QString> tokList;
    std::vector<tok> LexList;
    int pos = 0;
    QChar q = text[6];
    state =  0;
    int stateBuf = 0;
    int Ltype = 0;
    tokList = div(text);
    myex e;



    for(int i = 0;i<text.size();i++)
    {
        QTextStream(stdout) << i << Qt::endl;
        QTextStream(stdout) << buf << Qt::endl;
        QTextStream(stdout) << state << Qt::endl << Qt::endl;
        switch(state)
        {
            case 0:
            //QTextStream(stdout) << i << Qt::endl;
            if(I1.contains(text[i]))
            {
                if(I2.contains(text[i]))
                {
                    switch(text[i].unicode())
                    {
                    case 'i':
                        //QTextStream(stdout) << i << Qt::endl;
                        //QTextStream(stdout) << buf << Qt::endl;
                        buf += text[i];
                        state = 1;
                        break;
                    case 'e':
                        buf += text[i];
                        state = 2;
                        break;
                    case 't':
                        buf += text[i];
                        state = 5;
                        break;
                    case '<':
                        buf = text[i];
                        t.setTokPar(buf,2);
                        LexList.push_back(t);
                        buf = "";
                        state = 0;
                        break;
                    case '=':
                        buf = text[i];
                        t.setTokPar(buf,2);
                        LexList.push_back(t);
                        buf = "";
                        state = 0;
                        break;
                    case '>':
                        buf = text[i];
                        t.setTokPar(buf,2);
                        LexList.push_back(t);
                        buf = "";
                        state = 0;
                        break;
                    case ' ':
                        //buf = text[i];
                        //t.setTokPar(buf,2);
                        //LexList.push_back(t);
                        buf = "";
                        state = 0;
                        QTextStream(stdout) << i << Qt::endl;
                        QTextStream(stdout) << buf << Qt::endl;
                        break;
                    case ';':
                        buf = text[i];
                        t.setTokPar(buf,8);
                        LexList.push_back(t);
                        buf = "";
                        state = 0;
                        break;
                    case ':':
                        //buf = "";
                        //t.setTokPar(buf,1);
                        //LexList.push_back(t);
                        buf = text[i];
                        state = 15;
                        break;
                    case '/':
                        buf += text[i];
                        state = 23;
                        break;
                    case '-':
                        //t.setTokPar(buf,1);
                        //LexList.push_back(t);
                        buf += text[i];
                        state = 9;
                        break;
                    default:
                        buf += text[i];
                        state = 8;
                        //QTextStream(stdout) << i << Qt::endl;
                        //QTextStream(stdout) << buf << Qt::endl;
                        break;
                    }
                } else
                    {
                        buf += text[i];
                        state = 9;
                    }
            } else
                {
                    state = 22;
                }
            break;
            case 1:
                switch(text[i].unicode())
                {
                case 'f':
                    buf += text[i];
                    // t.setTokPar(buf,0);
                    // LexList.push_back(t);
                    // buf = "";
                    state = 16;
                    break;
                case ' ':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                default:
                    buf += text[i];
                    state = 8;
                    break;
                }
                break;
            case 2:
                switch(text[i].unicode())
                {
                case 'l':
                    buf += text[i];
                    state = 3;
                    break;
                case ' ':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                default:
                    buf += text[i];
                    state = 8;
                    break;
                }
                break;
            case 3:
                switch(text[i].unicode())
                {
                case 's':
                    buf += text[i];
                    state = 4;
                    break;
                case ' ':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                default:
                    buf += text[i];
                    state = 8;
                    break;
                }
                break;
            case 4:
                switch(text[i].unicode())
                {
                case 'e':
                    buf += text[i];
                    // t.setTokPar(buf,6);
                    // LexList.push_back(t);
                    // buf = "";
                    state = 16;
                    break;
                case ' ':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                default:
                    buf += text[i];
                    state = 8;
                    break;
                }
                break;
            case 5:
                switch(text[i].unicode())
                {
                case 'h':
                    buf += text[i];
                    state = 6;
                    break;
                case ' ':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                default:
                    buf += text[i];
                    state = 8;
                    break;
                }
                break;
            case 6:
                switch(text[i].unicode())
                {
                case 'e':
                    buf += text[i];
                    state = 7;
                    break;
                case ' ':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                default:
                    buf += text[i];
                    state = 8;
                    break;
                }

                break;
            case 7:
                switch(text[i].unicode())
                {
                case 'n':
                    buf += text[i];
                    // t.setTokPar(buf,4);
                    // LexList.push_back(t);
                    // buf = "";
                    state = 16;
                    break;
                case ' ':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                default:
                    buf += text[i];
                    state = 8;
                    break;
                }

                break;
            case 8:
                QTextStream(stdout) << i << Qt::endl;

                switch(text[i].unicode())
                {
                case '<':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    //QTextStream(stdout) << i << Qt::endl;
                    buf = "";
                    state = 0;
                    break;
                case '=':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case '>':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ' ':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ';':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,7);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ':':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    state = 15;
                    break;
                case '{':
                    buf += text[i];
                    state = 23;
                    break;
                default:
                    if(I3.contains(text[i]) | N1.contains(text[i]))
                    {
                        buf += text[i];
                        state = 8;
                    }
                    else
                    {
                        t.setTokPar(buf,3);
                        LexList.push_back(t);
                        //buf = text[i];
                        switch(text[i].unicode())
                        {
                        case 'i':
                            //QTextStream(stdout) << i << Qt::endl;
                            //QTextStream(stdout) << buf << Qt::endl;
                            buf = text[i];
                            state = 1;
                            break;
                        case 'e':
                            buf = text[i];
                            state = 2;
                            break;
                        case 't':
                            buf = text[i];
                            state = 6;
                            break;
                        default:
                            buf += text[i];
                            t.setTokPar(buf,1);
                            LexList.push_back(t);
                            break;
                        }

                    }
                }
                break;
            case 9:
                switch(text[i].unicode())
                {
                case '<':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case '=':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;

                case '>':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ' ':
                    t.setTokPar(buf,3);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ':':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    state = 15;
                    break;
                case ';':
                    t.setTokPar(buf,3);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,7);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case '/':
                    buf += text[i];
                    state = 23;
                    break;
                case '.':
                    buf += text[i];
                    state = 10;
                    break;
                case 'e':
                    buf2 = buf;
                    buf += text[i];
                    state = 12;
                    break;
                default:
                    if(N1.contains(text[i]))
                    {
                        buf += text[i];
                        state = 9;
                    }
                    else
                    {

                        //QTextStream(stdout) << buf << Qt::endl;
                        t.setTokPar(buf,3);
                        LexList.push_back(t);
                        //buf = text[i];
                        switch(text[i].unicode())
                        {
                        case 'i':
                            //QTextStream(stdout) << i << Qt::endl;
                            //QTextStream(stdout) << buf << Qt::endl;
                            buf = text[i];
                            state = 1;
                            break;
                        case 'e':
                            buf = text[i];
                            state = 2;
                            break;
                        case 't':
                            buf = text[i];
                            state = 5;
                            break;
                        default:
                            buf = text[i];
                            state = 22;
                            break;
                        }


                    }
                    break;
                }
                break;
            case 10:
                if(N1.contains(text[i]))
                {
                    buf += text[i];
                    state = 11;
                }
                else
                {
                    state = 22;
                }
                break;
            case 11:
                switch(text[i].unicode())
                {
                case '<':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case '-':
                    state = 22;
                    break;
                case '=':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ' ':
                    t.setTokPar(buf,3);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case '>':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ';':
                    t.setTokPar(buf,3);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,7);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ':':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    state = 15;
                    break;
                case '.':
                    state = 22;
                    break;
                case 'e':

                    buf += text[i];
                    state = 12;
                    break;
                default:
                    if(N1.contains(text[i]))
                    {
                        buf += text[i];
                        state = 11;
                    }
                    else
                    {
                        t.setTokPar(buf,3);
                        LexList.push_back(t);
                        //buf = text[i];
                        switch(text[i].unicode())
                        {
                        case 'i':
                            //QTextStream(stdout) << i << Qt::endl;
                            //QTextStream(stdout) << buf << Qt::endl;
                            buf = text[i];
                            state = 1;
                            break;
                        case 'e':
                            buf = text[i];
                            state = 2;
                            break;
                        case 't':
                            buf = text[i];
                            state = 6;
                            break;
                        default:

                            break;
                        }
                    }
                    break;
                }
                break;
            case 12:
                if(text[i] == '-' | N1.contains(text[i]))
                {
                    buf += text[i];
                    state = 13;
                }else if(text[i] == 'l')
                {
                    t.setTokPar(buf2,7);
                    LexList.push_back(t);
                    buf = "el";
                    state = 3;
                }else
                {
                    state = 22;
                }
                break;
            case 13:
                if(N1.contains(text[i]))
                {
                    buf += text[i];
                    state = 14;
                }
                else
                {
                    state = 22;
                }
                break;
            case 14:
                switch(text[i].unicode())
                {
                case '<':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case '=':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ':':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    state = 15;
                    break;
                case '>':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,2);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ' ':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case ';':
                    t.setTokPar(buf,1);
                    LexList.push_back(t);
                    buf = text[i];
                    t.setTokPar(buf,7);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                    break;
                case '/':
                    buf += text[i];
                    state = 23;
                    break;
                case '.':
                    state = 22;
                    break;
                default:
                    if(N1.contains(text[i]))
                    {
                        buf += text[i];
                        state = 14;
                    }
                    else
                    {
                        t.setTokPar(buf,3);
                        LexList.push_back(t);
                        //buf = text[i];
                        switch(text[i].unicode())
                        {
                        case 'i':
                            //QTextStream(stdout) << i << Qt::endl;
                            //QTextStream(stdout) << buf << Qt::endl;
                            buf = text[i];
                            state = 1;
                            break;
                        case 'e':
                            buf = text[i];
                            state = 2;
                            break;
                        case 't':
                            buf = text[i];
                            state = 6;
                            break;
                        }
                    }
                }
                break;
            case 15:
                if(text[i] == '=')
                {
                    buf += text[i];
                    t.setTokPar(buf,5);
                    LexList.push_back(t);
                    buf = "";
                    state = 0;
                }
                else
                {
                    state = 22;
                }
                break;
            case 16:
                if(text[i] == " ")
                {
                    if(buf == "if")
                    {
                        t.setTokPar(buf,0);
                        LexList.push_back(t);
                        buf = "";
                        state = 0;
                    } else
                    {
                        if(buf == "then")
                        {
                            t.setTokPar(buf,4);
                            LexList.push_back(t);
                            buf = "";
                            state = 0;
                        }
                        else
                        {
                            if(buf == "else")
                            {
                                t.setTokPar(buf,6);
                                LexList.push_back(t);
                                buf = "";
                                state = 0;
                            } else
                            {
                                t.setTokPar(buf,1);
                                LexList.push_back(t);
                                buf = "";
                                state = 0;
                            }
                        }

                    }

                } else
                {
                    buf += text[i];
                    state = 8;
                }

                break;
            case 17:

                break;
            case 18:

                break;
            case 19:

                break;
            case 20:

                break;
            case 21:

                break;
            case 22:
                e.setPos(i - 1);
                throw(e);
                break;
            case 23:
                //QTextStream(stdout) << i << Qt::endl;
                switch(text[i].unicode())
                {
                case '/':

                    state = 24;
                    break;
                default:
                    state = 22;
                    break;

                }
                break;
            case 24:
                if(i == text.size() - 1)
                {
                    Commbuf += text[i];
                    Ltype  = 8;
                    t.setTokPar(Commbuf,Ltype);
                    LexList.push_back(t);
                    Commbuf = "";
                    state = 0;
                } else
                {
                    Commbuf += text[i];
                }
                break;
        }

    }

    return LexList;
}
