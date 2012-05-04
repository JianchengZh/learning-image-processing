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

    ImageFile archivo(filename);
    if(archivo.readImageContents()){
        QString imageType = filename.right(3).toUpper();

        if(imageType == "PPM"){
            imagen = new ImagenPPM(archivo.getImageContents());
        }else{
            imagen = new ImagenPGM(archivo.getImageContents());
        }
        displayedImage=new QImage(filename);
        return true;
    }else{
        return false;
    }
}

QImage* MainController::generateHistogram(){

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

        oldImage=imagen;
        imagen=oldImage->changeColorDepth(depth);
        imagen->exportar("temp");
        oldDisplayedImage=displayedImage;
        displayedImage=new QImage("temp."+imagen->getImageType().toLower());

}

void MainController::convertToGrayscale(int method){

    oldImage=imagen;
    imagen=static_cast<ImagenPPM*>(oldImage)->convertToGrayScale(method);
    imagen->exportar("temp");
    oldDisplayedImage=displayedImage;
    displayedImage=new QImage("temp."+imagen->getImageType().toLower());
}

void MainController::bimodalSegmentaion(int T){

        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->bimodalSegmentaion(T);
        imagen->exportar("temp");
        oldDisplayedImage=displayedImage;
        displayedImage=new QImage("temp."+imagen->getImageType().toLower());

}


void MainController::isodataSegmentation(){
    histogram->calculateLocalMaximux();
    bimodalSegmentaion(histogram->calculateThresholdIsodata());
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
        oldImage=0;
        oldDisplayedImage=0;
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

