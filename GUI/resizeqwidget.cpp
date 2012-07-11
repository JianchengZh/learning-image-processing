//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: resizeqwidget.cpp
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



#include "resizeqwidget.h"
#include "ui_resizeqwidget.h"

ResizeQwidget::ResizeQwidget(QWidget *        parent,
                             MainController * controller,
                             MainWindow *     window):
    QWidget(parent),
    ui(new Ui::ResizeQwidget)
{
    ui -> setupUi(this);

    mainController = controller;
    mainwindow     = window;
}

ResizeQwidget::~ResizeQwidget()
{
    delete ui;
}

void ResizeQwidget::on_pushButton_clicked()
{
    int density = (int) ui -> lcdNumber -> value();

    if (mainController -> isThereAnUploadedImage())
    {
        mainController -> changeSize(density);
        mainwindow -> displayResults(mainController -> getQImage());
        mainwindow -> ShowHistogram();
        ui -> verticalSlider -> setValue(0);
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
