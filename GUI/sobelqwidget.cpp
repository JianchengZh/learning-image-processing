//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
//
// FECHA INICIACION: Marzo de 2012
//
// AUTORES:
// Gustavo Adolfo Rodriguez         0932979-3743
// gustalibreros@gmail.com
//
// Edwin Fernando Muñoz             0910398-3743
// edwinfernandomudelgado@gmail.com
//
// Yerminson Doney Gonzalez         0843846-3743
// yermigon@gmail.com
//
// Edgar Andrés Moncada             0832294-3743
// edgarandres29@gmail.com
//
// ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
// UNIVERSIDAD DEL VALLE
//**********************************************************


#include "sobelqwidget.h"
#include "ui_sobelqwidget.h"

SobelQwidget::SobelQwidget(QWidget *        parent,
                           MainController * controller,
                           MainWindow *     window):
    QWidget(parent),
    ui(new Ui::SobelQwidget)
{
    ui -> setupUi(this);

    mainwindow     = window;
    mainController = controller;

    // ui->verticalSlider->setMaximum(mainController->getImage()->getColorDepth());
}

SobelQwidget::~SobelQwidget()
{
    delete ui;
}

void SobelQwidget::on_sobelHorizontally_clicked()
{
    if (mainController -> isThereAnUploadedImage())
    {
        mainController -> edgeDetectionSobel(0);
        mainwindow -> displayResults(mainController -> getQImage());
        mainwindow -> ShowHistogram();
    }
    else
    {
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

void SobelQwidget::on_sobelVertically_clicked()
{
    if (mainController -> isThereAnUploadedImage())
    {
        mainController -> edgeDetectionSobel(1);
        mainwindow -> displayResults(mainController -> getQImage());
        mainwindow -> ShowHistogram();
    }
    else
    {
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}

void SobelQwidget::on_sobelFilter_clicked()
{
    if (mainController -> isThereAnUploadedImage())
    {
        mainController -> edgeDetectionSobel(2);
        mainwindow -> displayResults(mainController -> getQImage());
        mainwindow -> ShowHistogram();
    }
    else
    {
        QMessageBox msgBox2(this);
        msgBox2.setText("Sorry,Operation not valid");
        msgBox2.setWindowTitle("ERROR");
        msgBox2.exec();
    }
}


//~ Formatted by Jindent --- http://www.jindent.com
