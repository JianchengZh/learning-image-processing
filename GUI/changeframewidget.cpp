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


#include "changeframewidget.h"
#include "ui_changeframewidget.h"

ChangeFrameWidget::ChangeFrameWidget(QWidget * parent,
        MainController *                       controller,
        MainWindow *                           window):
    QWidget(parent),
    ui(new Ui::ChangeFrameWidget)
{
    ui -> setupUi(this);

    this -> mainController = controller;
    this -> mainwindow     = window;
}

ChangeFrameWidget::~ChangeFrameWidget()
{
    delete ui;
}

void ChangeFrameWidget::on_sliderFrame_valueChanged(int value)
{
    if (mainController -> isThereAnUploadedImage())
    {
        mainController -> changeFrame(value);
        ui -> labelNum -> setText(QString::number(value));
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

void ChangeFrameWidget::setMaxFrame(int value)
{
    ui -> sliderFrame -> setMaximum(value);
}


//~ Formatted by Jindent --- http://www.jindent.com
