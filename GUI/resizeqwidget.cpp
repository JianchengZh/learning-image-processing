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

#include "resizeqwidget.h"
#include "ui_resizeqwidget.h"

ResizeQwidget::ResizeQwidget(QWidget *parent, MainController *controller, MainWindow *window) :
    QWidget(parent),
    ui(new Ui::ResizeQwidget)
{
    ui->setupUi(this);
    mainController=controller;
    mainwindow=window;
}

ResizeQwidget::~ResizeQwidget()
{
    delete ui;
}

void ResizeQwidget::on_pushButton_clicked()
{
        int density = (int)ui->lcdNumber->value();
        mainwindow->displayResults(mainController->changeSize(density));
        mainwindow->ShowHistogram();

}
