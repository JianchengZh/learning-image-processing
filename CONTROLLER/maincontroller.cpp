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

}

MainController::~MainController(){
    delete imagen;
    imagen=0;

    delete oldImage;
    oldImage=0;

}

// LOAD IMAGE
bool MainController::loadImage(QString filename){

    QString fileExtension = filename.section(".",-1);

    if (fileExtension.toUpper() == "PGM") {
        imagen = new ImagenPGM(filename);
        if (imagen->getStatus()) {
            return true;
        }

    } else if (fileExtension.toUpper() == "PPM"){
        imagen = new ImagenPPM(filename);
        if (imagen->getStatus()) {
            return true;
        }
    }

    else{
        imagen = new ImagenDCM(filename.toStdString().c_str());
        if (imagen->getStatus()) {
            return true;
        }
    }
    return false;
}

QImage* MainController::getHistogramImage(){
    return imagen->getHistogramImage();
}

// Image Transfomations
void MainController::changeSize(int density){

    delete oldImage;
    oldImage=0;
    oldImage=imagen;
    imagen=oldImage->changeSize(density);
}

void MainController::changeColorDepth(int depth){
    QTextStream cout (stdout);

    cout<<"A. Inicio del metodo changeColorDepth en el controlador"<<endl;
    delete oldImage;
    oldImage=0;
    oldImage=imagen;
    cout<<"B. Justo Antes de llamar al metodo changeColorDepth de la clase Imagen"<<endl;
    imagen=oldImage->changeColorDepth(depth);
    imagen->saveImage("temp");
    cout<<"H. Dentro de changeColorDepth - en controlador, despues de exportar "<<endl;
}

void MainController::convertToGrayscale(int method){
    delete oldImage;
    oldImage=imagen;
    imagen=static_cast<ImagenPPM*>(oldImage)->convertToGrayScale(method);
}

bool MainController::average(QString filename, double alpha){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->average(image,alpha);
        return true;
    } else {
        return false;
    }

}

bool MainController::add(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->add(image);
        return true;
    } else {
        return false;
    }
}

bool MainController::subtract(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->subtract(image);
        return true;
    } else {
        return false;
    }
}

bool MainController::multiply(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->multiply(image);
        return true;
    } else {
        return false;
    }

}

bool MainController::divide(QString filename){

    ImagenPGM *image = new ImagenPGM(filename);

    if (imagen->getHeight()==image->getHeight() && imagen->getWidth()==image->getWidth()) {
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->divide(image);
        imagen->saveImage("temp");
        return true;
    } else {
        return false;
    }
}

void MainController::equalizateHistogram(){
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->histogramEqualization(oldImage->getHistogram()->calculateEqualization());
}

bool MainController::bimodalSegmentaion(int T){
    if(imagen!=0){
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->bimodalSegmentaion(T);
        return true;
    }else{
        return false;
    }
}

void MainController::isodataSegmentation(){
    imagen->getHistogram()->ThresholdingByTwoPeaks();
    bimodalSegmentaion(imagen->getHistogram()->ThresholdingByIsodata());
}

void MainController::otsuSegmentation(){
    imagen->getHistogram()->ThresholdingByTwoPeaks();
    bimodalSegmentaion(imagen->getHistogram()->ThresholdingByOtsu());
}

//Filter
void MainController::meanFilter(int size){
        delete oldImage;
        oldImage=imagen;
        imagen=static_cast<ImagenPGM*>(oldImage)->meanFilter(size);
}

void MainController::convolutionFilter(int **kernel, int size){
    delete oldImage;
    oldImage=imagen;
    QTextStream (stdout)<<"Entre al controlador"<<endl;
    imagen=static_cast<ImagenPGM*>(oldImage)->convolutionFilter(kernel,size);
}

// DICOM
void MainController::applyWindowLevel(int window, int level){

    static_cast<ImagenDCM*>(imagen)->applyWindowLevel(window,level);
}


// Getters
Image* MainController::getImage(){
    return imagen;
}

QImage* MainController::getQImage(){
    return imagen->getQImage();
}

// Other Methods
bool MainController::undo(){
    if (oldImage!=0) {
        imagen=oldImage;
        oldImage=0;
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

void MainController::saveImage(QString filename){
    imagen->saveImage(filename);
}
