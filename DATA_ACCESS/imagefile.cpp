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

bool ImageFile::readFile()
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
    //Habia problemas con varios espacios entre los valores de ancho y alto ejemplo: 250    250, generan fallo de segmentacion
    QStringList lineSplit = lectura.at(1).split(QRegExp("\\s+"));
    this->width=lineSplit.at(0).toInt();
    this->height=lineSplit.at(1).toInt();
    this->colorDepth=lectura.at(2).toInt();
      QTextStream (stdout) <<"Lei el archivo "<< lineSplit.at(0) << "\n";
       QTextStream (stdout) <<"Lei el archivo "<< lineSplit.at(1) << "\n";

    if (id =="P2") {
        this->matrix = new int[width*height];
    } else {
        this->matrix = new int[3*width*height];
    }
    int i=0;
    for (int z = 3; z < lectura.length(); ++z) {
        lineSplit = lectura.at(z).split(" ");
        foreach (QString pixel, lineSplit) {
            if (!pixel.isEmpty()) {
                matrix[i]=(pixel+"     ").toInt();
                i++;
            }
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
    return this->colorDepth;
}
int* ImageFile::getMatrix(){
    return this->matrix;
}
