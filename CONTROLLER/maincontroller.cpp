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
    this->imagenPGM=0;
    this->imagenPPM=0;
    this->imagen=0;
    this->oldImage=0;
    this->oldImagePGM=0;
    this->oldImagePPM=0;
    this->displayedImage=0;
    this->oldDisplayedImage=0;
}

MainController::~MainController(){    
}

// LOAD IMAGE
bool MainController::loadImage(QString filename){

    ImageFile archivo(filename);
    if(archivo.readImageContents()){
        QString imageType = filename.right(3).toUpper();
        if(imageType == "PPM"){
            imagenPPM = new ImagenPPM(archivo.getImageContents());
            imagen=imagenPPM;
        }else{
            imagenPGM = new ImagenPGM(archivo.getImageContents());
            //            imagenPGM==dynamic_cast<ImagenPGM*>(imagen);
            imagen=imagenPGM;
        }
        displayedImage=new QImage(filename);
        return true;
    }else{
        return false;
    }
}

QImage* MainController::generateHistogram(){
    Histogram histogram (imagenPGM);
    ImagenPGM *imageHistogram=histogram.getHistogram();
    imageHistogram->exportar("histogram");
    return new QImage("histogram.pgm");

}

// Image Transfomations
QImage* MainController::changeSize(int density){
    oldImage=imagen;
    imagen=oldImage->changeSize(density);
    imagen->exportar("temp");
    oldDisplayedImage=displayedImage;
    displayedImage=new QImage("temp."+imagen->getImageType().toLower());
    return displayedImage;
}

QImage* MainController::changeColorDepth(int depth){
    oldImage=imagen;
    imagen=oldImage->changeColorDepth(depth);
    imagen->exportar("temp");
    oldDisplayedImage=displayedImage;
    displayedImage=new QImage("temp."+imagen->getImageType().toLower());
    return displayedImage;
}

QImage* MainController::convertToGrayscale(int method){

    if(imagenPPM!=0){
        oldImage=imagen;
        imagen=imagenPPM->convertToGrayScale(method);
        imagen->exportar("temp");
        oldDisplayedImage=displayedImage;
        displayedImage=new QImage("temp."+imagen->getImageType().toLower());
        return displayedImage;
    }else{
        return 0;
    }


}

// Getters
Image* MainController::getImage(){
    return imagen;
}
QImage* MainController::getQImage(){
    return displayedImage;
}

// Other Methods
void MainController::newJob(){
    imagenPGM=0;
    imagenPPM=0;
    imagen=0;
    oldImage=0;
    oldImagePGM=0;
    oldImagePPM=0;
    displayedImage=0;
    oldDisplayedImage=0;
}

QImage* MainController::undo(){
    imagen=oldImage;
    imagenPGM=oldImagePGM;
    imagenPPM=oldImagePPM;
    displayedImage=oldDisplayedImage;
    return displayedImage;
}

