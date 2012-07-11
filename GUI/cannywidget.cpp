//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: cannywidget.cpp
// 
// FECHA: 11.07.12
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



#include "cannywidget.h"
#include "ui_cannywidget.h"

CannyWidget::CannyWidget(QWidget *        parent,
                         MainController * controller,
                         MainWindow *     window):
    QWidget(parent),
    ui(new Ui::CannyWidget)
{
    ui -> setupUi(this);

    mainwindow     = window;
    mainController = controller;
}

CannyWidget::~CannyWidget()
{
    delete ui;
}

void CannyWidget::on_buttonEdgeCanny_clicked()
{
    if (mainController -> isThereAnUploadedImage())
    {
        int thresholdDown = ui -> spinBoxDown -> value();
        int thresholdHigh = ui -> spinBoxHigh -> value();

        mainController -> edgeDetectorCanny(thresholdHigh, thresholdDown);
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

void CannyWidget::on_spinBoxDown_valueChanged(int i)
{
    int thresholdHigh = ui -> spinBoxHigh -> value();

    if (thresholdHigh < i)
    {
        ui -> spinBoxHigh -> setValue(i);
    }
}

void CannyWidget::on_spinBoxHigh_valueChanged(int i)
{
    int thresholdDown = ui -> spinBoxDown -> value();

    if (thresholdDown > i)
    {
        ui -> spinBoxDown -> setValue(i);
    }
}


//~ Formatted by Jindent --- http://www.jindent.com
