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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt include
#include <QMainWindow>
#include <QFileDialog>
#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include <QInputDialog>
#include <QErrorMessage>
#include <QPoint>
#include <QDebug>


// Projec include
#include "CONTROLLER/maincontroller.h"
#include "GUI/dialogabout.h"
#include "GUI/resizeqwidget.h"
#include "GUI/colordepthqwidget.h"
#include "GUI/thresholdqwidget.h"
#include "GUI/windowlevelqwidget.h"
#include "GUI/convolutionqwidget.h"
#include "GUI/sobelqwidget.h"
#include "GUI/cannywidget.h"

class ResizeQwidget;
class ColorDepthQwidget;
class ThresholdQwidget;
class ConvolutionQwidget;
class WindowLevelQWidget;
class SobelQwidget;

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

    // Buttons Events
    void on_pButton_LoadImage_clicked();
//    void on_pButton__AdjustImageSize_clicked();
    void on_pButton__NormalSize_clicked();

    // MenuBar Events

    // File Menu
    void on_actionNew_Job_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();

    // Edit Menu
    void on_actionUndo_triggered();

    // Global Transformations Menu
    void on_actionResize_triggered();
    void on_actionChange_Color_Depth_triggered();
    void on_actionConver_to_GrayScale_triggered();
    void on_actionWeight_Average_triggered();
    void on_actionAdd_triggered();
    void on_actionSubstract_triggered();
    void on_actionMultiply_triggered();
    void on_actionDivide_triggered();

    // Histogram Menu
    void on_actionThreshold_triggered();
    void on_actionEqualization_triggered();

    //Filters Menu
    void on_actionMean_triggered();
    void on_actionConvolution_triggered();
    void on_actionGaussiana_triggered();
    void on_actionNoise_Cleaning_Line_triggered();
    void on_actionNoise_Cleaning_Pixel_triggered();

    // Contrast Menu
    void on_actionGamma_Correction_triggered();
    void on_actionStretching_triggered();

    // Edge Detection Menu
    void on_actionSobel_triggered();
    void on_actionCanny_triggered();

    // DICOM Menu
    void on_actionWindow_Level_triggered();

    // Help Menu
    void on_actionAbout_triggered();

    // Other Methods
    void on_label_Imagen_drawLine(const QPoint start, const QPoint end);
    void on_label_Imagen_eraseLine();
    void on_label_Imagen_mousePosition(const QPoint position);
    void on_horizontalSlider_zoom_sliderMoved(int factor);

private:

    Ui::MainWindow *ui;
    MainController * mainController;
    QImage *displayedImage, *histogramImage;
    QPixmap pixmapLabelImagen;
};

#endif // MAINWINDOW_H
