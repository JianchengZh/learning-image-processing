//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: colordepthqwidget.h
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
    explicit ColorDepthQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~ColorDepthQwidget();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::ColorDepthQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // COLORDEPTHQWIDGET_H
