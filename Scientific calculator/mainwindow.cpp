#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStack>
#include <QTextStream>
#include <QVector>

QTextStream out(stdout);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->p1, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->p2, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->p3, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->p4, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->p5, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->p6, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->p7, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->p8, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->p9, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->p0, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->openB, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->closeB, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->back, SIGNAL(released()), this, SLOT(handleBack()));
    connect(ui->subtract, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->mult, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->divide, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->add, SIGNAL(released()), this, SLOT(handlePush()));
    connect(ui->result, SIGNAL(released()), this, SLOT(handleResult()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int prec(QChar sym)
{
    if(sym == 'x' || sym == '/')
    {
        return 2;
    }
    else if(sym =='+' || sym == '-')
    {
        return 1;
    }
    else return 0;
}

void MainWindow::handlePush(){
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
     if (pButton) // this is the type we expect
     {
         QString buttonText = pButton->text();
         // recognize buttonText here
         ui->label->setText((ui->label->text()+buttonText));
     }
}

void MainWindow::handleBack(){
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
     if (pButton) // this is the type we expect
     {
         QString buttonText = ui->label->text();
         // recognize buttonText here
         buttonText.chop(1);
         ui->label->setText(buttonText);
     }
}

void MainWindow::handleResult(){
    std::cout<<"Pressed";
    QStack<QChar> symHold;
    QVector<int> numbers;
    QVector<QChar> symbols;
    QVector<int> postExp;
    QVector<QChar> postSym;
    QStack<int> numHold;
    int pv = 0, num = 0, j=0;
    QString expression = ui->label->text();

    for(int i = expression.size()-1; i>=0; i--)
    {
        if(expression.at(i) == '-'||(expression.at(i) == '/'||(expression.at(i) == '+'||(expression.at(i) == 'x'))))
        {
            numbers.push_back(num);
            numbers.push_back(' ');
            symbols.push_back(expression.at(i));
            num=0;
            pv=0;
        }
        else
        {
            num += expression.at(i).digitValue()*pow(10,pv);
            pv++;
            if(i == 0)
            {
                numbers.push_back(num);
                num=0;
                pv=0;
            }
        }
    }

    j = symbols.size()-1;

    for(int i=numbers.size()-1; i>=0; i--){
        if((char)numbers[i]==' ')
        {
            if(symbols.at(j)!=')' && symbols.at(j)!='(')
            {
                while(!symHold.isEmpty() && (prec(symbols.at(j))<=prec(symHold.top())))
                {
                    postSym.push_back(symHold.pop());
                    postExp.push_back(' ');
                }
                symHold.push(symbols.at(j));
                j--;
            }
            else
            {
                if(symbols.at(j)==')')
                {
                    while(!symHold.isEmpty() && symHold.top()=='(')
                    {
                        postSym.push_back(symHold.pop());
                        postExp.push_back(' ');
                    }
                    symHold.pop();
                    j--;
                }
                else
                {
                    symHold.push(symbols.at(j));
                    j--;
                }
            }
        }
        else
        {
            postExp.push_back(numbers[i]);
        }
    }

    while(!symHold.isEmpty())
    {
        postSym.push_back(symHold.pop());
        postExp.push_back(' ');
    }

    numbers.clear();
    symbols.clear();
    j = 0;
    //postExp now has the postfix expression in parsed form
    //Along with this postSym has the symbols in the expression in parsed form

    for (int i = 0; i < postExp.size(); ++i)
    {
        if((char)postExp[i] != ' ')
        {
            numHold.push(postExp[i]);
        }
        else
        {
            int val1 = numHold.pop();
            int val2 = numHold.pop();
            switch (postSym.at(j).unicode())
            {
                case '+':   numHold.push(val2+val1);break;
                case '-':   numHold.push(val2-val1);break;
                case 'x':   numHold.push(val2*val1);break;
                case '/':   numHold.push(val2/val1);break;
            }
        }
    }

    ui->label->setText(QString::number(numHold.pop()));
}


/*

What do i have ?????????

String representing the expression -- expression

Array of ints (stack or something)

what i expect to do ---
    create a vector containing the ints and the symbols {+.-.x,/} basically the expression

    convert this to postfix expression

    for example -   4 - (1 + 2) + (2 + 3) this expression evalutes to below in postfix -
    4,1,2.+.-.2,3,+.+   store as two arrays
    [4,1,2,' ',' ',2,3,' ',' '] where ' ' means a symbol, which can be traced in  another operator array
    [+.-.+,+]

    evaluate the expression using a stack

    push into the stack, when encounter a symbol then trace the symbol array.

    Algorithm to convert individual digits in the expression string to individual numbers

    stack<int> numStore;
    Int i = 0, num = 0;

    for(in end….0){
        if(val == {+. -. *, /}){
            numStore.push(num);
        num=0;i=0;
    }
    num += val.toInt()*pow(10,i);
    i++;
    }

*/
