#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStack>
#include <QVector>

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
    QStack<int> numHold;
    QVector<QChar> mexpr;
    int pv = 0, num = 0;
    QString expression = ui->label->text();
    for(int i = expression.size()-1; i>=0; i--){
        if(expression.at(i) == '-'||(expression.at(i) == '/'||(expression.at(i) == '+'||(expression.at(i) == 'x')))){
            numHold.push(num);
            num=0;
            pv=0;
        }
        else{
            num += expression.at(i).digitValue()*pow(10,pv);
            pv++;
            if(i == 0){
                numHold.push(num);
                num=0;
                pv=0;
            }
        }
    }
    for(int i = 0; i >expression.size(); i++){
        if(expression.at(i) == '-'||(expression.at(i) == '/'||(expression.at(i) == '+'||(expression.at(i) == 'x')))){
            if(!numHold.isEmpty()){
                mexpr.push_back(numHold.pop());
                mexpr.push_back(expression.at(i));
            }
        }
        else{
            if(!numHold.isEmpty()){
                mexpr.push_back(numHold.pop());
            }
        }
    }
    for(int i = 0; i >mexpr.size(); i++){
        std::cout<<mexpr[i].digitValue();
    }
}

//stack<int> numStore;
//Int i = 0, num = 0;

//for(in end….0){
//    if(val == {+. -. *, /}){
//        numStore.push(num);
//    num=0;i=0;
//}
//num += val.toInt()*pow(10,i);
//    i++;
//}


