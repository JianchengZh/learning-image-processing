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

    Image *resizedImage=imagen->changeSize(density);
    resizedImage->exportar("temp");
    return new QImage("temp."+imagen->getImageType().toLower());

}

//QString MainController::changeColorDensity(int intensidad){

//    //    if(imagenPPM != 0){
//    //        ImagenPPM *imagenPPMTransformed=imagenPPM->reducirIntensidad(intensidad);
//    //        exportTempImage(imagenPPMTransformed, "tem.ppm~");  // Se guarda como Archivo
//    //        return "tem.ppm~";

//    //    }else{
//    //        ImagenPGM imagenPGMTransformed=imagenPGM->changeIntensity(intensidad);
//    //        exportTempImage(imagenPGMTransformed, "tem.pgm~");  // Se guarda como Archivo
//    //        return "tem.pgm~";
//    //    }

//}

//QString MainController::convertToGrayscale(){
//    //    ImagenPGM *imagenPGMTransformed=imagenPPM->convertirGris(1);
//    //    exportTempImage(imagenPGMTransformed, "tem.pgm~");  // Se guarda como Archivo
//    //    return "tem.pgm~";
//}



//// Other Methods


////void MainController::exportTempImage(Image *imagen, QString filename){
////    QFile temp(filename);
////    if(temp.open(QFile::WriteOnly)){
////        QTextStream fSalida(&temp);
////        imagen->exportar(fSalida);
////    }
////}

void MainController::newJob(){
    imagenPGM=0;
    imagenPPM=0;
    imagen=0;
}

// Getters

Image* MainController::getImage(){
    return imagen;
}

