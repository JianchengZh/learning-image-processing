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

#ifndef THRESHOLDQWIDGET_H
#define THRESHOLDQWIDGET_H

#include <QWidget>
#include "GUI/mainwindow.h"

class   MainWindow;

namespace Ui {
class ThresholdQwidget;
}

class ThresholdQwidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ThresholdQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~ThresholdQwidget();
    
private slots:
    void on_pushButton_clicked();

    void on_isodataSegmentation_clicked();

    void on_otsuSegmentation_clicked();

private:
    Ui::ThresholdQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
};

#endif // THRESHOLDQWIDGET_H
