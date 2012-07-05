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
