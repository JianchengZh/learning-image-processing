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

#ifndef CONVOLUTIONQWIDGET_H
#define CONVOLUTIONQWIDGET_H

#include <QWidget>
#include "GUI/mainwindow.h"

class MainWindow;

namespace Ui {
class ConvolutionQwidget;
}

class ConvolutionQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConvolutionQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~ConvolutionQwidget();
    
private slots:

    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_clicked();

private:
    Ui::ConvolutionQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
    QLineEdit ***qLineEditMatrix;
    int kernelSize;

    void deleteTable();
};

#endif // CONVOLUTIONQWIDGET_H
