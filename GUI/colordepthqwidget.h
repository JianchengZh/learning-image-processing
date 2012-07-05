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

#ifndef COLORDEPTHQWIDGET_H
#define COLORDEPTHQWIDGET_H

#include <QWidget>
#include "GUI/mainwindow.h"

class   MainWindow;

namespace Ui {
class ColorDepthQwidget;
}

class ColorDepthQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ColorDepthQwidget(QWidget *parent, MainController *controller, MainWindow *window, int ColorDensity);
    ~ColorDepthQwidget();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::ColorDepthQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // COLORDEPTHQWIDGET_H
