#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tok.h"
#include "automat.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "myex.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void  MainWindow::analize()
{
    QString text = ui->textEdit->toPlainText();
    Automat a;
    std::vector<QString> txtList;
    txtList = a.div(text);
    text = text.simplified();
    //text.replace( " ", "" );
    //QMessageBox::warning(this, "Внимание",text);
    QString buf = "";
    std::vector<tok> tokList;
    std::vector<tok> commList;
    int numRows = 0;
    int numColumns = 2;
    int numCom = 0;
    std::stack<tok> lexStack;
    //
    try
    {
        //commList = a.getCom(text);
        //text = a.removeCom(text);
        tokList = a.analize1(text);

    }
    catch(myex & e)
    {
        QString errText = "Лексичечкая ошибка на позииции " + QString::number(e.getPos());
        QMessageBox::warning(this, "Внимание",errText);
        //QMessageBox::warning(this, "Внимание","Лексическаая ошибка");
    }
    catch(...)
    {
        QMessageBox::warning(this, "Внимание","Ошибка");
    }
    QTextStream(stdout) << text << Qt::endl;



    numRows = tokList.size();
    numCom = commList.size();
    ui->tokenTable->clear();
    ui->tokenTable->setRowCount(numRows);
    ui->tokenTable->setColumnCount(numColumns);



    for(int i = 0; i< numRows; i++)
    {
        ui->tokenTable->setItem( i, 0, new QTableWidgetItem(tokList[i].getType()));
        ui->tokenTable->setItem( i, 1, new QTableWidgetItem(tokList[i].getVal()));
    }


    for(int i = 0; i< numRows; i++)
    {
        QTextStream(stdout) << tokList[i].getVal() << Qt::endl;

    }
    int j = 0;
    if(commList.size() > 1)
    {
        for(int i = numRows - 1;j< numCom; i++)
        {


            ui->tokenTable->setItem( i + 1, 1, new QTableWidgetItem(commList[j].getType()));
            ui->tokenTable->setItem( i, 2, new QTableWidgetItem(commList[j].getVal()));

            j++;

        }
    }


    for(int i = 0;i< txtList.size(); i++)
    {

        //QTextStream(stdout) << txtList[i] << Qt::endl;
    }

    try
    {
        //lexStack = a.analize(tokList);
    }
    catch(std::exception & e)
    {
        QMessageBox::warning(this, "Внимание","Синтаксичекия ошибка");
    }
    catch(...)
    {
        QMessageBox::warning(this, "Внимание","Ошибка");
    }

    int k;
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *parentItem = model->invisibleRootItem();

    //QStandardItem *thenT = new QStandardItem(lexStack.top().getVal());
    //QStandardItem *elseT = new QStandardItem(lexStack.top().getVal());






}


void MainWindow::on_But1_clicked()
{
    analize();
}

