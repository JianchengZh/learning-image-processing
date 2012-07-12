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

#ifndef SOBELQWIDGET_H
#define SOBELQWIDGET_H

#include <QWidget>
#include "GUI/mainwindow.h"

class   MainWindow;

namespace Ui {
class SobelQwidget;
}

class SobelQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SobelQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~SobelQwidget();
    
private slots:
    void on_sobelHorizontally_clicked();

    void on_sobelVertically_clicked();

    void on_sobelFilter_clicked();

private:
    Ui::SobelQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // SOBELQWIDGET_H
