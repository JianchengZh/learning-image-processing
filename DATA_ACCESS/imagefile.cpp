//**********************************************************
// INTRODUCCION AL PROCESAMIENTO DIGITAL DE IMÁGENES
// LEARNING_IMAGE_PROCESSING
//
// ARCHIVO: imagefile.cpp
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

#include "imagefile.h"

ImageFile::ImageFile(QString filename) : QFile(filename)
{
    supportedFormats << "ppm" << "pgm";
}

bool ImageFile::readImageContents()
{
    if(supportedFormats.contains(fileName().right(3).toLower())){
        if (this->open(QIODevice::ReadOnly)){
            QTextStream lector(this);
            int i=0;
            while (!lector.atEnd())
            {
                lectura.insert(i, lector.readLine());
                i++;
            }
            return true;
        }
        else{
            return false;
        }
    }else{
        return false;
    }
}

void ImageFile::printImageContents()
{
    QTextStream cout(stdout);
    for(int i=0; i<lectura.size(); i++)
        cout<<lectura.at(i)<<endl;
}

QList<QString> ImageFile::getImageContents()
{
    return lectura;
}
