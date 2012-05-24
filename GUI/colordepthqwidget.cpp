//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: colordepthqwidget.cpp
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

#include "colordepthqwidget.h"
#include "ui_colordepthqwidget.h"

ColorDepthQwidget::ColorDepthQwidget(QWidget *parent, MainController *controller, MainWindow *window, int ColorDensity) :
    QWidget(parent),
    ui(new Ui::ColorDepthQwidget)
{
    ui->setupUi(this);
    mainController=controller;
    mainwindow=window;
    ui->verticalSlider->setValue(ColorDensity);
}

ColorDepthQwidget::~ColorDepthQwidget()
{
    delete ui;
}

void ColorDepthQwidget::on_pushButton_clicked()
{
    int depth = (int)ui->lcdNumber->value();
    if(mainController->isThereAnUploadedImage()){
        QTextStream (stdout) << "CAMBIANDO DE "<<(log2(mainController->getImage()->getColorDepth()+1))<<" A: "<<depth<<endl;
        mainController->changeColorDepth(depth);
        mainwindow->displayResults(mainController->getQImage());
        //        mainwindow->ShowHistogram();
    }else{
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}
