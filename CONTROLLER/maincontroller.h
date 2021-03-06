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



#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

// Qt include

#include <QImage>

// #include <QString>
// Project include

#include "LOGIC/imagenpgm.h"
#include "LOGIC/imagenppm.h"
#include "LOGIC/imagendcm.h"
#include "LOGIC/image.h"
#include "LOGIC/histogram.h"
#include "DATA_ACCESS/imagefile.h"
#include "LOGIC/edgedetector.h"
#include "LOGIC/segmentation.h"
#include "LOGIC/globaltransformation.h"
#include "LOGIC/geometricoperation.h"
#include "LOGIC/filter.h"

class MainController
{
    private:
        Image * imagen, *oldImage;
        
    public:
        MainController();
        ~MainController();

        bool loadImage(QString filename);

        // Edit Menu:
        void changeColorDepth(int depth);
        void convertToGrayscale(int method);

        // Global Trasnformations
        bool weightedAverage(QString filename, double  alpha);
        bool add(QString filename);
        bool subtract(QString filename);
        bool multiply(QString filename);
        bool divide(QString filename);

        bool maxOperation(QString filename);
        bool minOperation(QString filename);

        bool andOperation(QString filename);
        bool xorOperation(QString filename);
        void notOperation();
        bool orOperation(QString filename);

        // geometric operations
        void sacaling(double factorX,
                      double factorY);
        void translation(double factorX,
                         double factorY);
        void rotation(double angle);
        void reflection(bool orientationX);    // true X false Y

        // histogram
        bool bimodalSegmentaion(int T);
        void equalizateHistogram();
        void otsuSegmentation();
        void isodataSegmentation();

        // contrast
        void gammaCorrection(double r);
        void contrastStretching();

        // Filter
        void meanFilter(int size);
        void convolutionFilter(int ** kernel,
                               int    size);
        void gaussianaFilter(int size);
        void noiseCleaningPixel(int delta);
        void noiseCleaningLine(double delta);

        // Edge Detection
        void edgeDetectionSobel(int position);
        void edgeDetectorCanny(int thresholdHigh,
                               int thresholdDown);

        // Morphological Operation
        void dilateOperation(int ** matrixStructuringElement,
                             int    origenX,
                             int    origenY,
                             int    heightS,
                             int    widthS);
        void erosionOperation(int ** matrixStructuringElement,
                              int    origenX,
                              int    origenY,
                              int    heightS,
                              int    widthS);
        void openingOperation(int ** matrixStructuringElement,
                              int    origenX,
                              int    origenY,
                              int    heightS,
                              int    widthS);
        void closingOperation(int ** matrixStructuringElement,
                              int    origenX,
                              int    origenY,
                              int    heightS,
                              int    widthS);

        // Segementation
        void segmentationK_Means(int cluster);
        void segmentationRemoveCap();
        int getCountFrameFirstImage();
        void segmentationWhiteTissue();
        void segmentationGrayTissue();

        // DICOM
        void applyWindowLevel(int window,int level);
        void changeFrame(int numFrame);
        QString getDataSet();
        void convertDICOMtoPGM();

        // GETTERS:
        Image * getImage();
        QImage * getQImage();
        QImage * getHistogramImage();

        // Others methods:
        bool undo();
        bool isThereAnUploadedImage();
        void saveImage(QString filename,
                       QString id);
};
#endif // MAINCONTROLLER_H


//~ Formatted by Jindent --- http://www.jindent.com
