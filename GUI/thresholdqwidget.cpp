//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: resizeqwidget.cpp
//
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

#include "thresholdqwidget.h"
#include "ui_thresholdqwidget.h"

ThresholdQwidget::ThresholdQwidget(QWidget *parent, MainController *controller, MainWindow *window):
    QWidget(parent),
    ui(new Ui::ThresholdQwidget)
{
    ui->setupUi(this);
    mainwindow=window;
    mainController=controller;
    ui->verticalSlider->setMaximum(mainController->getImage()->getColorDensity());
}

ThresholdQwidget::~ThresholdQwidget()
{
    delete ui;
}

void ThresholdQwidget::on_pushButton_clicked()
{
    int threshold = (int)ui->lcdNumber->value();
    if(mainController->bimodalSegmentaion(threshold)){
        mainwindow->displayResults(mainController->getQImage());
        mainwindow->ShowHistogram();
    }else{
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

void ThresholdQwidget::on_isodataSegmentation_clicked()
{
    if(mainController->isodataSegmentation()){
        mainwindow->displayResults(mainController->getQImage());
        mainwindow->ShowHistogram();
    }else{
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}
