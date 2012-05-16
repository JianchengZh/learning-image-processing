//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt include
#include <QMainWindow>
#include <QFileDialog>
#include <QApplication>
#include <QPixmap>
#include <QMessageBox>
#include <QInputDialog>
#include <QErrorMessage>

// Projec include
#include "CONTROLLER/maincontroller.h"
#include "GUI/dialogabout.h"
#include "GUI/resizeqwidget.h"
#include "GUI/colordepthqwidget.h"
#include "GUI/thresholdqwidget.h"

class ResizeQwidget;
class ColorDepthQwidget;
class ThresholdQwidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();

    void displayResults(QImage *result);
    void ShowHistogram();

private slots:

    // Load Image
    void on_pButton_LoadImage_clicked();

    // Events for changing the image size on the main screen
    void on_pButton__AdjustImageSize_clicked();
    void on_pButton__NormalSize_clicked();

    // MenuBar Events

    // File Menu
    void on_actionNew_Job_triggered();
    void on_actionExit_triggered();

    // Edit Menu
    void on_actionUndo_triggered();

    // Global Transformations
    void on_actionResize_triggered();
    void on_actionChange_Color_Depth_triggered();
    void on_actionConver_to_GrayScale_triggered();

    void on_actionAdd_triggered();
    void on_actionSubstract_triggered();
    void on_actionMultiply_triggered();
    void on_actionDivide_triggered();

    // Histogram Menu
    void on_actionThreshold_triggered();
    void on_actionEqualization_triggered();

    // Tomography Menu

    // Help Menu
    void on_actionAbout_triggered();

private:

    Ui::MainWindow *ui;
    MainController * mainController;
    QImage *displayedImage, *histogramImage;
};

#endif // MAINWINDOW_H
