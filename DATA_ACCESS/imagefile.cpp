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

bool ImageFile::read()
{
    if(supportedFormats.contains(fileName().section(".",-1))){

        if (this->open(QIODevice::ReadOnly)){

            QTextStream lector(this);
            while (!lector.atEnd())
            {
                QString line = lector.readLine();
                if(!line.startsWith("#")){
                    lectura<<line;
                }
            }
            readingProcess();
            return true; //ojo cambiar ahora
        }
        else{
            return false;
        }
    }else{
        return false;
    }
}

void ImageFile::readingProcess(){

    this->id=lectura.at(0);
    this->width=lectura.at(1).section(' ',0,0).toInt();
    this->height=lectura.at(1).section(' ',1,1).toInt();

    if (id =="P2") {
        this->matrix = new int[width*height];
    } else {
        this->matrix = new int[3*width*height];
    }
    int i=0;
    for (int z = 3; z < lectura.length(); ++z) {
        QStringList lineSplit = lectura.at(z).split(" ");
        foreach (QString pixel, lineSplit) {
            matrix[i]=pixel.toInt();
            i++;
        }
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
//GETTERS
QString ImageFile::getId(){
    return this->id;
}
int ImageFile::getWidth(){
    return this->width;
}
int ImageFile::getHeight(){
    return this->height;
}
int ImageFile::getColorDepth(){
    this->colorDepth;
}
int* ImageFile::getMatrix(){
    this->matrix;
}
