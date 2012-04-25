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
}

ThresholdQwidget::~ThresholdQwidget()
{
    delete ui;
}
