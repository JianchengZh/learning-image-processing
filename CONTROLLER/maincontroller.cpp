//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: maincontroller.cpp
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

#include "maincontroller.h"

MainController::MainController(){
    this->imagen=0;
    this->oldImage=0;
    this->displayedImage=0;
    this->oldDisplayedImage=0;
    this->histogram=0;
    this->oldHistogram=0;
}

MainController::~MainController(){
    delete imagen;
    imagen=0;

    delete oldImage;
    oldImage=0;

    delete oldDisplayedImage;
    oldDisplayedImage=0;

    delete histogram;
    histogram=0;
}

// LOAD IMAGE
bool MainController::loadImage(QString filename){

    if (filename.contains(".")) {
          QString imageType = filename.right(3).toUpper();

          if (imageType=="PPM") {
              ImageFile archivo(filename);
              archivo.readImageContents();
              imagen = new ImagenPPM(archivo.getImageContents());
              displayedImage=new QImage(filename);
              return true;

          } else if(imageType == "PGM"){
              ImageFile archivo(filename);
              archivo.readImageContents();
              imagen = new ImagenPGM(archivo.getImageContents());
              displayedImage=new QImage(filename);
              return true;

          } else{
              imagen = new ImagenDCM(filename.toStdString().c_str());
              return true;
          }

    } else {
         imagen = new ImagenDCM(filename.toStdString().c_str());
         return true;
    }
}

QImage* MainController::getHistogramImage(){

    histogram = new Histogram (static_cast<ImagenPGM*>(imagen));
    ImagenPGM *imageHistogram=histogram->getHistogram();
    imageHistogram->exportar("histogram");

    delete imageHistogram;
    imageHistogram=0;

    return new QImage("histogram.pgm");
}

// Image Transfomations
void MainController::changeSize(int density){

    delete oldImage;
    oldImage=0;
    oldImage=imagen;
    imagen=oldImage->changeSize(density);
    imagen->exportar("temp");
    oldDisplayedImage=displayedImage;
    displayedImage=new QImage("temp."+imagen->getImageType().toLower());
}

void MainController::changeColorDepth(int depth){

    delete oldImage;
    oldImage=0;
    oldImage=imagen;
    imagen=oldImage->changeColorDepth(depth);
    imagen->exportar("temp");
    oldDisplayedImage=displayedImage;
    displayedImage=new QImage("temp."+imagen->getImageType().toLower());

}

void MainController::convertToGrayscale(int method){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPPM*>(oldImage)->convertToGrayScale(method);
    imagen->exportar("temp");
    oldDisplayedImage=displayedImage;
    displayedImage=new QImage("temp."+imagen->getImageType().toLower());
}

bool MainController::add(QString filename, double alpha){

    ImageFile archivo(filename);
    archivo.readImageContents();
    ImagenPGM *image = new ImagenPGM(archivo.getImageContents());

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->add(image,alpha);
        imagen->exportar("temp");
        oldDisplayedImage=displayedImage;
        displayedImage=new QImage("temp."+imagen->getImageType().toLower());
        return true;
    } else {
        return false;
    }

}

bool MainController::equalizateHistogram(){
    if(imagen!=0){
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->histogramEqualization(histogram->calculateEqualization());
        imagen->exportar("temp");
        oldDisplayedImage=displayedImage;
        displayedImage=new QImage("temp."+imagen->getImageType().toLower());
        return true;
    }else{
        return false;
    }
}

bool MainController::bimodalSegmentaion(int T){
    if(imagen!=0){
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->bimodalSegmentaion(T);
        imagen->exportar("temp");
        oldDisplayedImage=displayedImage;
        displayedImage=new QImage("temp."+imagen->getImageType().toLower());
        return true;
    }else{
        return false;
    }
}

void MainController::isodataSegmentation(){
    histogram->ThresholdingByTwoPeaks();
    bimodalSegmentaion(histogram->ThresholdingByIsodata());
}

void MainController::otsuSegmentation(){
    histogram->ThresholdingByTwoPeaks();
    bimodalSegmentaion(histogram->ThresholdingByOtsu());
}

// Getters
Image* MainController::getImage(){
    return imagen;
}

QImage* MainController::getQImage(){
    return displayedImage;
}

// Other Methods
bool MainController::undo(){
    if (oldImage!=0) {
        imagen=oldImage;
        displayedImage=oldDisplayedImage;
        histogram=oldHistogram;
        oldImage=0;
        oldDisplayedImage=0;
        oldHistogram=0;
        return true;
    }else{
        return false;
    }
}

bool MainController::isThereAnUploadedImage(){
    if(imagen!=0){
        return true;
    }else{
        return false;
    }
}

