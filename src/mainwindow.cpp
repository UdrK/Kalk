#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "VariabileAleatoria.h"
#include "Controller.h"
#include "Poisson.h"
#include "Skellam.h"
#include "Ipergeometrica.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int ntipi=7;
    QString tipi[ntipi] = {"Bernoulli", "Binomiale", "Geometrica", "Pascal", "Poisson", "Skellam", "Ipergeometrica"};

    for(int i=0; i<ntipi;i++)
        ui->comboBox_tipo->addItem(tipi[i]);

    ui->pushButton_meno->setDisabled(true);
    ui->pushButton_per->setDisabled(true);
    ui->pushButton_diviso->setDisabled(true);


    connect(ui->pushButton_X, SIGNAL(released()), this, SLOT(write_pressed()));
    connect(ui->pushButton_Y, SIGNAL(released()), this, SLOT(write_pressed()));
    connect(ui->pushButton_aperta, SIGNAL(released()), this, SLOT(write_pressed()));
    connect(ui->pushButton_chiusa, SIGNAL(released()), this, SLOT(write_pressed()));
    connect(ui->pushButton_piu, SIGNAL(released()), this, SLOT(write_pressed()));
    connect(ui->pushButton_meno, SIGNAL(released()), this, SLOT(write_pressed()));
    connect(ui->pushButton_per, SIGNAL(released()), this, SLOT(write_pressed()));
    connect(ui->pushButton_diviso, SIGNAL(released()), this, SLOT(write_pressed()));
    connect(ui->pushButton_uguale, SIGNAL(released()), this, SLOT(uguale_pressed()));
    connect(ui->pushButton_me, SIGNAL(released()), this, SLOT(fun_pressed()));
    connect(ui->pushButton_mo, SIGNAL(released()), this, SLOT(fun_pressed()));
    connect(ui->pushButton_va, SIGNAL(released()), this, SLOT(fun_pressed()));
    connect(ui->pushButton_in, SIGNAL(released()), this, SLOT(fun_pressed()));
    connect(ui->pushButton_en, SIGNAL(released()), this, SLOT(fun_pressed()));
    connect(ui->pushButton_de, SIGNAL(released()), this, SLOT(fun_pressed()));
    connect(ui->pushButton_c, SIGNAL(released()), this, SLOT(canc_pressed()));
    connect(ui->comboBox_tipo, SIGNAL(currentIndexChanged(QString)), this, SLOT(tipo_changed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::signalException(CustomException e){
    ui->lineEdit_input->setText(e.getReason());
}

void MainWindow::write_pressed(){

    QPushButton* button = (QPushButton*)sender();

    QString t = ui->lineEdit_input->text();
    ui->lineEdit_input->setText(t+button->text());

}

void MainWindow::fun_pressed(){

    QPushButton* button = (QPushButton*)sender();
    if(button->objectName()=="pushButton_me"){
        QString t = ui->lineEdit_input->text();
        ui->lineEdit_input->setText("E("+t+")");
    }
    else if(button->objectName()=="pushButton_mo"){
        QString t = ui->lineEdit_input->text();
        ui->lineEdit_input->setText("M("+t+")");
    }
    else if(button->objectName()=="pushButton_va"){
        QString t = ui->lineEdit_input->text();
        ui->lineEdit_input->setText("V("+t+")");
    }
    else if(button->objectName()=="pushButton_en"){
        QString t = ui->lineEdit_input->text();
        ui->lineEdit_input->setText("e("+t+")");
    }
    else if(button->objectName()=="pushButton_de"){
        QString t = ui->lineEdit_input->text();
        ui->lineEdit_input->setText("D("+t+")");
    }
    else if(button->objectName()=="pushButton_in"){
        QString t = ui->lineEdit_input->text();
        ui->lineEdit_input->setText("I("+t+")");
    }
}

void MainWindow::canc_pressed(){

    ui->lineEdit_input->setText("");

}

void MainWindow::uguale_pressed(){

    QString t = ui->comboBox_tipo->currentText();
    QString e = ui->lineEdit_input->text();
    QString x = ui->lineEdit_x->text();
    QString y = ui->lineEdit_y->text();
    QString k = ui->lineEdit_k->text();

    if(e.isEmpty()) return;

    VariabileAleatoria* ax = NULL;
    VariabileAleatoria* ay = NULL;

    try{
        if(t=="Bernoulli"){
            if(!x.isEmpty()) ax= new Bernoulli(x);
            if(!y.isEmpty()) ay= new Bernoulli(y);
        }
        else if(t=="Binomiale"){
            if(!x.isEmpty()) ax= new Binomiale(x);
            if(!y.isEmpty()) ay= new Binomiale(y);
        }
        else if(t=="Geometrica"){
            if(!x.isEmpty()) ax= new Geometrica(x);
            if(!y.isEmpty()) ay= new Geometrica(y);
        }
        else if(t=="Pascal"){
            if(!x.isEmpty()) ax= new Pascal(x);
            if(!y.isEmpty()) ay= new Pascal(y);
        }
        else if(t=="Ipergeometrica"){
            if(!x.isEmpty()) ax= new Ipergeometrica(x);
            if(!y.isEmpty()) ay= new Ipergeometrica(y);
        }
        else if(t=="Poisson"){
            if(!x.isEmpty()) ax= new Poisson(x);
            if(!y.isEmpty()) ay= new Poisson(y);
        }
        else if(t=="Skellam"){
            if(!x.isEmpty()) ax= new Skellam(x);
            if(!y.isEmpty()) ay= new Skellam(y);
        }
    }catch(CustomException e){signalException(e);}

    if((e.contains('x')||e.contains('X')) && ax==NULL){
        signalException(CustomException("Input mancante o incorretto"));
        return;
    }
    if((e.contains('y')||e.contains('Y')) && ay==NULL){
        signalException(CustomException("Input mancante o incorretto"));
        return;
    }

    Controller* c = new Controller();
    QString monofun = "EVMDIe";
    QString auxE = e;
    QString output;
    bool mono = false;
    if(monofun.contains(e.at(0))){
        auxE=e.mid(2, e.length()-3);
        mono=true;
    }
    try{
        VariabileAleatoria* r = c->valuta(auxE, t, *ax, *ay);
        if(mono){
            try{
                output = c->monoperando(*r, QString(e.at(0)), k.toInt());
            }catch(CustomException e){signalException(e); return;}
        }
        else{
            output = r->toQString("r");
            if(t=="Bernoulli" && !dynamic_cast<Bernoulli*>(r)){
                ui->comboBox_tipo->setCurrentIndex(1);
            }
            else if(t=="Geometrica" && !dynamic_cast<Geometrica*>(r)){
                ui->comboBox_tipo->setCurrentIndex(3);
            }
        }
    }catch(CustomException e){signalException(e); return;}

    ui->lineEdit_input->setText(output);

}

void MainWindow::tipo_changed(){

    QString s = ui->comboBox_tipo->currentText();
    if(s=="Bernoulli"){
        ui->pushButton_en->setDisabled(false);
        ui->pushButton_in->setDisabled(false);
        ui->pushButton_meno->setDisabled(true);
        ui->pushButton_per->setDisabled(true);
        ui->pushButton_diviso->setDisabled(true);
    }
    else if(s=="Geometrica"){
        ui->pushButton_en->setDisabled(false);
        ui->pushButton_meno->setDisabled(true);
        ui->pushButton_per->setDisabled(true);
        ui->pushButton_diviso->setDisabled(true);
        ui->pushButton_in->setDisabled(true);
    }
    else if(s=="Binomiale"){
        ui->pushButton_meno->setDisabled(false);
        ui->pushButton_per->setDisabled(false);
        ui->pushButton_en->setDisabled(false);
        ui->pushButton_in->setDisabled(false);
        ui->pushButton_diviso->setDisabled(true);
    }
    else if(s=="Pascal"){
        ui->pushButton_meno->setDisabled(false);
        ui->pushButton_per->setDisabled(false);
        ui->pushButton_in->setDisabled(false);
        ui->pushButton_diviso->setDisabled(true);
        ui->pushButton_en->setDisabled(true);
    }
    else if(s=="Ipergeometrica"){
        ui->pushButton_meno->setDisabled(false);
        ui->pushButton_per->setDisabled(false);
        ui->pushButton_in->setDisabled(true);
        ui->pushButton_diviso->setDisabled(true);
        ui->pushButton_en->setDisabled(true);
    }
    else if(s=="Poisson"){
        ui->pushButton_meno->setDisabled(false);
        ui->pushButton_per->setDisabled(false);
        ui->pushButton_in->setDisabled(false);
        ui->pushButton_diviso->setDisabled(false);
        ui->pushButton_en->setDisabled(true);
    }
    else if(s=="Skellam"){
        ui->pushButton_meno->setDisabled(false);
        ui->pushButton_per->setDisabled(false);
        ui->pushButton_diviso->setDisabled(false);
        ui->pushButton_en->setDisabled(true);
        ui->pushButton_in->setDisabled(true);
    }

}
