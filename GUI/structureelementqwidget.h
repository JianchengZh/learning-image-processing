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

#ifndef STRUCTUREELEMENTQWIDGET_H
#define STRUCTUREELEMENTQWIDGET_H

#include <QWidget>
#include "GUI/mainwindow.h"

class MainWindow;

namespace Ui {
class StructureElementQwidget;
}

class StructureElementQwidget : public QWidget
{
    Q_OBJECT

public:
    explicit StructureElementQwidget(QWidget *parent, MainController *controller, MainWindow *window);
    ~StructureElementQwidget();

private slots:

    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg2);
    void on_pushButtonDilate_clicked();
    void on_pushButtonErosion_clicked();
    void on_pushButtonOpening_clicked();
    void on_pushButtonClosing_clicked();

private:
    Ui::StructureElementQwidget *ui;
    MainController *mainController;
    MainWindow *mainwindow;
    QLineEdit ***qLineEditMatrix;
    int heigthS,widthS;
    double widthLineEdit, heightLineEdit,widthTable,heightTable;
    int initialX, initialY;
    QFont font;

    void deleteTable();
};
#endif // STRUCTUREELEMENTQWIDGET_H
