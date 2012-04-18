//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// PGM_PPM_IMAGE_PROCESSING_V2
//
// ARCHIVO: resultcontroller.cpp
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

#include "resultcontroller.h"

ResultController::ResultController(QString temImageFile)
{
    this->imageType=temImageFile.right(4).left(3).toLower();
    ImageFile archivo(temImageFile);        // Crear el objeto tipo Archivo

    if(archivo.readImageContents()){
        if(imageType == "ppm"){
            imagenPPM = new ImagenPPM(archivo.getImageContents());
        }else{
            imagenPGM = new ImagenPGM(archivo.getImageContents());
        }
    }
}

void ResultController::saveImage(QString fileNameDest){
    if(imageType == "ppm"){

        QFile temp(fileNameDest+"."+imageType);
        if(temp.open(QFile::WriteOnly)){
            QTextStream fSalida(&temp);
            imagenPPM->exportar(fSalida);
        }
    }else{
        QFile temp(fileNameDest+"."+imageType);
        if(temp.open(QFile::WriteOnly)){
            QTextStream fSalida(&temp);
            imagenPGM->exportar(fSalida);
        }
    }
}
