//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: resizeqwidget.h
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

#ifndef RESIZEQWIDGET_H
#define RESIZEQWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "CONTROLLER/maincontroller.h"
#include "GUI/mainwindow.h"

class MainWindow;

namespace Ui {
class ResizeQwidget;
}

class ResizeQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ResizeQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~ResizeQwidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ResizeQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // RESIZEQWIDGET_H
