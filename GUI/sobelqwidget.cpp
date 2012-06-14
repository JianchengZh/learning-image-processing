// FECHA INICIACION: Marzo de 2012
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@hotmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@hotmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************
#include "sobelqwidget.h"
#include "ui_sobelqwidget.h"

SobelQwidget::SobelQwidget(QWidget *parent, MainController *controller, MainWindow *window) :
    QWidget(parent),
    ui(new Ui::SobelQwidget)
{
    ui->setupUi(this);
    mainwindow=window;
    mainController=controller;
  //  ui->verticalSlider->setMaximum(mainController->getImage()->getColorDepth());
}

SobelQwidget::~SobelQwidget()
{
    delete ui;
}

void SobelQwidget::on_sobelHorizontally_clicked()
{
    if(mainController->isThereAnUploadedImage()){
        mainController->edgeDetectionSobel(0);
        mainwindow->displayResults(mainController->getQImage());
        mainwindow->ShowHistogram();
    }else{
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

void SobelQwidget::on_sobelVertically_clicked()
{
    if(mainController->isThereAnUploadedImage()){
        mainController->edgeDetectionSobel(1);
        mainwindow->displayResults(mainController->getQImage());
        mainwindow->ShowHistogram();
    }else{
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

void SobelQwidget::on_sobelFilter_clicked()
{

}